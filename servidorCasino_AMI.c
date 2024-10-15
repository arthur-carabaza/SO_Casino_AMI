#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql/mysql.h>

//Definimos estructuras i funciones para trabajar con la lista de conectados
typedef struct {
	chat nombre[20];
	int socket;
} Conectado;

typedef struct {
	Conectado conectados[100];
	int num;
} ListaConectados;

int PonConectado(ListaConectados *lista, char nombre[20], int socket) {
	//Añade nuevo conectado a una lista de conectados
	//Devuelva -1 si la llista esta llena, 0 si se ha hecho correctamente
	if (lista->num == 100)
		return -1;
	else {
		strcpy(lista->conectados[lista->num].nombre, nombre);
		lista->conectados[lista->num].socket = socket;
		lista->num++;
		return 0;

	}
}
int DamePosicion(ListaConectados *lista, char nombre[20]) {
	//Devuelve posicon en la lista o -1 si  no está en la lista de conectado
	int i = 0;
	int encontrado = 0;
	while ((i < lista->num) && !encontrado)
	{
		if (strcmp(lista->conectados[i].nombre, nombre) == 0)
			encontrado = 1;
		else if (!encontrado)
			i = i + 1;
	}
	if (encontrado)
		return i;
	else
		return -1;
}

int EliminaConectado(ListaConectados *lista, char nombre[20]) {
	//Retorna 0 si elimina y -1 si ese usuario no esta en la lista
	//Primero con el algoritmo de busqueda buscamos la posicion del nombre
	int pos = DamePosicion(lista, nombre);
	if (pos == -1)
		return -1;
	else {
		int i;
		for (i = pos; i < lista->num - 1; i++)
		{
			strcpy(lista->conectados[i].nombre, lista->conectados[i + 1].nombre);
			lista->conectados[i].socket = lista->conectados[i + 1].socket;
		}
		lista->num--;
		return 0;
	}
}

void DameConectados(ListaConectados* lista, char conectados[300]) {
	//Escribe en la char de conectados los nombre de todos los coenctados separados por /
	//Primero Pone el numero de conectados: 3/Pedro/Maria/Juan
	sprintf(conectados, "%d", lista->num);
	int i;
	for (i = 0; i < lista->num; i++)
		sprintf(conectados, "%s/%s", conectados, lista->conectados[i].nombre);

}


int main(int argc, char *argv[])
{
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;

	//Chars para trabajar con Peticion/Respuesta entre servidor y cleinte
	char peticion[512];
	char respuesta[512];

	//Variables para comprobar que la persona tenga la session inicaida para hacer peticiones
	int session_iniciada = 0;
	char usuario_logueado [100];

	//Lista de conectados que se inicializa con 0 conectados
	ListaConectados miLista;
	miLista.num = 0;

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int err;

	// Conexión a la base de datos MySQL
	conn = mysql_init(NULL);
	if (conn == NULL) 
	{
		printf("Error al crear la conexión MySQL: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}

	if (mysql_real_connect(conn, "localhost", "root", "mysql", "JuegoPoker", 0, NULL, 0) == NULL) 
	{
		printf("Error al inicializar la conexión con la base de datos: %u %s\n", mysql_errno(conn), mysql_error(conn));
		mysql_close(conn);
		exit(1);
	}


	// INICIALITZACIONS
	// Obrim el socket
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error creant socket");

	// Fem el bind al port
	memset(&serv_adr, 0, sizeof(serv_adr));// inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;
	// asocia el socket a cualquiera de las IP de la m?quina. 
	//htonl formatea el numero que recibe al formato necesario
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	// escucharemos en el port 50000
	serv_adr.sin_port = htons(50000);

	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	//La cola de peticiones pendientes no podr? ser superior a 4
	if (listen(sock_listen, 4) < 0)
		printf("Error en el Listen");

	int i;
	//bucle infinito
	for (;;) 
	{
		printf ("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("He recibido conexi?n\n");
		//sock_conn es el socket que usaremos para este cliente

		//Bucle de atencion al clinete
		int terminar = 0;
		while (terminar == 0)
		{ 
	
			// Ahora recibimos su peticion
			ret=read(sock_conn,peticion, sizeof(peticion));
			printf ("Recibida una petición\n");
			// Tenemos que a?adirle la marca de fin de string 
			// para que no escriba lo que hay despues en el buffer
			peticion[ret]='\0';
		
			//Escribimos la peticion en la consola
		
			printf ("La petición es: %s\n",peticion);

			char *p = strtok(peticion, "/");
			int codigo =  atoi (p);
			//Ya tenemos codigo de peticion
			char nombre[20];
			char password[20];

			if (codigo !=0)
			{ 

				p = strtok( NULL, "/");
				strcpy (nombre, p);
				printf ("Codigo: %d, Nombre: %s\n", codigo, nombre);

			}
		
			if (codigo == 0)
				terminar = 1;
			
			else if (codigo ==1) //piden iniciar session
			{
				p = strtok(NULL, "/");
				strcpy(password, p);

				// Consulta para verificar si el usuario existe y coincide la contraseña
				char query[256];
				sprintf(query, "SELECT password FROM Jugadores WHERE usuario='%s'", nombre);

				err = mysql_query(conn, query);
				if (err != 0) 
				{
					printf("Error al consultar la base de datos: %s\n", mysql_error(conn));
					sprintf(respuesta, "Error en la base de datos");
				}
				else 
				{
					res = mysql_store_result(conn);
					row = mysql_fetch_row(res);
					if (row == NULL) 
					{
						sprintf(respuesta, "El usuario no existe");
					}
					else 
					{
						if (strcmp(row[0], password) == 0) 
						{
							sprintf(respuesta, "Inicio de sesión correcto");
							strcpy(usuario_logueado, nombre);
							session_iniciada = 1;
						}
						else 
						{
							sprintf(respuesta, "Contraseña incorrecta");
						}
					}
					mysql_free_result(res);	
				}
			}

			else if (codigo ==2) //Quieren registrarse 
			{
				p = strtok(NULL, "/");
				strcpy(password, p);

				// Consulta para insertar el nuevo jugador
				char query[256];
				sprintf(query, "INSERT INTO Jugadores (usuario, password) VALUES ('%s', '%s')", nombre, password);

				err = mysql_query(conn, query);
				if (err != 0) {
					if (mysql_errno(conn) == 1062) {  // Código de error para duplicados
						sprintf(respuesta, "El nombre de usuario ya existe");
					}
					else {
						printf("Error al insertar en la base de datos: %s\n", mysql_error(conn));
						sprintf(respuesta, "Error al registrarse");
					}
				}
				else 
				{
					sprintf(respuesta, "Registro exitoso");
				}
			}
			

			else if (codigo ==3) //quiere saber cuanto dinero tiene
			{
				char query[256];
				sprintf(query, "SELECT dinero FROM Jugadores WHERE usuario='%s'", usuario_logueado);

				err = mysql_query(conn, query);
				if (err != 0)
				{
					printf("Error al consultar la base de datos: %s\n", mysql_error(conn));
					sprintf(respuesta, "Error en la base de datos");
				}
				else
				{
					res = mysql_store_result(conn);
					row = mysql_fetch_row(res);
					if (row == NULL)
					{
						sprintf(respuesta, "El usuario no existe");
					}
					else
					{
						sprintf(respuesta, "Dinero disponible: %.2f", atof(row[0]));
					}
					mysql_free_result(res);
				}
			}

			else if (codigo == 4) //quiere saber cuantas partidas ha ganado
			{
				char query[256];
				sprintf(query, "SELECT victorias FROM Jugadores WHERE usuario='%s'", usuario_logueado);

				err = mysql_query(conn, query);
				if (err != 0)
				{
					printf("Error al consultar la base de datos: %s\n", mysql_error(conn));
					sprintf(respuesta, "Error en la base de datos");
				}
				else
				{
					res = mysql_store_result(conn);
					row = mysql_fetch_row(res);
					if (row == NULL)
					{
						sprintf(respuesta, "El usuario no existe");
					}
					else
					{
						sprintf(respuesta, "Partidas ganadas: %d", atoi(row[0]));
					}
					mysql_free_result(res);
				}
			}
				

			else if (codigo ==5) //quiere saber que cartas tiene
			{
				char query[256];
				sprintf(query, "SELECT cartas FROM Jugadores WHERE usuario='%s'", usuario_logueado);

				err = mysql_query(conn, query);
				if (err != 0)
				{
					printf("Error al consultar la base de datos: %s\n", mysql_error(conn));
					sprintf(respuesta, "Error en la base de datos");
				}
				else
				{
					res = mysql_store_result(conn);
					row = mysql_fetch_row(res);
					if (row == NULL)
					{
						sprintf(respuesta, "El usuario no existe");
					}
					else
					{
						if (row[0] == NULL || strcmp(row[0], "") == 0)
						{
							sprintf(respuesta, "No tienes cartas");
						}
						else
						{
							sprintf(respuesta, "Tus cartas: %s", row[0]);
						}
					}
					mysql_free_result(res);
				}
			
			}


			if (codigo !=0)
			{ 
				printf("Respuesta: %s\n", respuesta);
					// Enviamos la respuesta
				write (sock_conn,respuesta, strlen(respuesta));
			}
		}
			
		// Se acabo el servicio para este cliente
		close(sock_conn); 
	}

	mysql_close(conn);
	return 0;

}
