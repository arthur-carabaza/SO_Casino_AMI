#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include <pthread.h>

//Estructura necesaria para el acceso excluyente
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//Definimos estructuras i funciones para trabajar con la lista de conectados
typedef struct {
	char nombre[20];
	int socket;
} Conectado;

typedef struct {
	Conectado conectados[100];
	int num;
} ListaConectados;


//Lista de conectados que se inicializa con 0 conectados
ListaConectados miLista;
char conectados[300];
int i = 0;
int sockets[100];


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
int BuscaSocketPorNombre(char nombre) {
	// Con esta funcion entregamos el nombre de un usuario y nos devuelve su socket directamente por como esta definida el objeto de conectados
    for (int i = 0; i < miLista.num; i++) {
        if (strcmp(miLista.conectados[i].nombre, nombre) == 0) {
            return miLista.conectados[i].socket;
        }
    }
    return -1; // No encontrado
}
void DameConectados(ListaConectados* lista, char conectados[300]) {
	//Escribe en la char de conectados los nombre de todos los coenctados separados por /
	//Primero Pone el numero de conectados: 3/Pedro/Maria/Juan
	sprintf(conectados, "%d", lista->num);
	int i;
	for (i = 0; i < lista->num; i++)
		sprintf(conectados, "%s:%s", conectados, lista->conectados[i].nombre);

}

void* AtenderClientes(void* socket) {
	int sock_conn;
	int* s;
	s = (int*)socket;
	sock_conn = *s;

	// Chars para trabajar con Peticion / Respuesta entre servidor y cleinte
	char peticion[512];
	char respuesta[512];
	int ret;

	int terminar = 0;
	
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
	
	if (mysql_real_connect(conn, "shiva2.upc.es", "root", "mysql", "M1_JuegoPoker", 0, NULL, 0) == NULL) 
	{
		printf("Error al inicializar la conexión con la base de datos: %u %s\n", mysql_errno(conn), mysql_error(conn));
		mysql_close(conn);
		exit(1);
	}

	//Variables para comprobar que la persona tenga la session inciada para hacer peticiones
	int session_iniciada = 0;
	char usuario_logueado[100];
	
	// Entramos en un bucle para atender todas las peticiones de este cliente hasta que se desconecte
	while (terminar == 0) {

		ret = read(sock_conn, peticion, sizeof(peticion));
		printf("Recibida una petición\n");
		// Tenemos que a?adirle la marca de fin de string 
		// para que no escriba lo que hay despues en el buffer
		peticion[ret] = '\0';

		//Escribimos la peticion en la consola

		printf("La petición es: %s\n", peticion);

		char* p = strtok(peticion, "/");
		int codigo = atoi(p);
		//Ya tenemos codigo de peticion
		char nombre[20];
		char password[20];

		if ((codigo != 0)&&(codigo !=6))
		{
			p = strtok(NULL, "/");
			strcpy(nombre, p);
			printf("Codigo: %d, Nombre: %s\n", codigo, nombre);
		}
		if (codigo == 0)
			terminar = 1;

		else if (codigo == 1) //piden iniciar session
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
				sprintf(respuesta, "1/Error en la base de datos");
			}
			else
			{
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				if (row == NULL)
				{
					sprintf(respuesta, "1/El usuario no existe");
				}
				else
				{
					if (strcmp(row[0], password) == 0)
					{
						sprintf(respuesta, "1/Inicio de sesión correcto");
						strcpy(usuario_logueado, nombre);
						session_iniciada = 1;

						// Ahora añadimos al cliente a la lista de conectados
						pthread_mutex_lock(&mutex); //No me interrumpas ahora el proceso de este thread
						if (PonConectado(&miLista, nombre, sock_conn) == -1)
						{
							printf("La lista de conectados está llena\n");
						}
						else
						{
							printf("El cliente %s se ha añadido a la lista de conectados\n", nombre);
						}
						pthread_mutex_unlock(&mutex); //Ya puedes interrumpir el proceso de este thread
					}
					else
					{
						sprintf(respuesta, "1/Contraseña incorrecta");
					}
				}
				mysql_free_result(res);

			}
		}

		else if (codigo == 2) //Quieren registrarse 
		{
			p = strtok(NULL, "/");
			strcpy(password, p);

			// Consulta para insertar el nuevo jugador
			char query[256];
			sprintf(query, "INSERT INTO Jugadores (usuario, password) VALUES ('%s', '%s')", nombre, password);

			err = mysql_query(conn, query);
			if (err != 0) {
				if (mysql_errno(conn) == 1062) {  // Código de error para duplicados
					sprintf(respuesta, "2/El nombre de usuario ya existe");
				}
				else {
					printf("Error al insertar en la base de datos: %s\n", mysql_error(conn));
					sprintf(respuesta, "2/Error al registrarse");
				}
			}
			else
			{
				sprintf(respuesta, "2/Registro exitoso");
			}
		}

		else if ((codigo == 3 || codigo == 4 || codigo == 5|| codigo==7 || codigo == 8))
		{
			if (session_iniciada == 0) {
				sprintf(respuesta, "Debes iniciar primero");
			}

			else {
				if (codigo == 3) { //Codigo 3 Quiery de dinero
					char query[256];
					sprintf(query, "SELECT dinero FROM Jugadores WHERE usuario='%s'", usuario_logueado);

					err = mysql_query(conn, query);
					if (err != 0)
					{
						printf("Error al consultar la base de datos: %s\n", mysql_error(conn));
						sprintf(respuesta, "3/Error en la base de datos");
					}
					else
					{
						res = mysql_store_result(conn);
						row = mysql_fetch_row(res);
						if (row == NULL)
						{
							sprintf(respuesta, "3/El usuario no existe");
						}
						else
						{
							sprintf(respuesta, "3/Dinero disponible: %.2f", atof(row[0]));
						}
						mysql_free_result(res);
					}
				}

				else if (codigo == 4) { //Codigo 4 querry de victoriaas
					char query[256];
					sprintf(query, "SELECT victorias FROM Jugadores WHERE usuario='%s'", usuario_logueado);

					err = mysql_query(conn, query);
					if (err != 0)
					{
						printf("Error al consultar la base de datos: %s\n", mysql_error(conn));
						sprintf(respuesta, "4/Error en la base de datos");
					}
					else
					{
						res = mysql_store_result(conn);
						row = mysql_fetch_row(res);
						if (row == NULL)
						{
							sprintf(respuesta, "4/El usuario no existe");
						}
						else
						{
							sprintf(respuesta, "4/Partidas ganadas: %d", atoi(row[0]));
						}
						mysql_free_result(res);
					}
				}

				else if (codigo == 5) { //Que cartas tengo
					char query[256];
					sprintf(query, "SELECT cartas FROM Jugadores WHERE usuario='%s'", usuario_logueado);

					err = mysql_query(conn, query);
					if (err != 0)
					{
						printf("Error al consultar la base de datos: %s\n", mysql_error(conn));
						sprintf(respuesta, "5/Error en la base de datos");
					}
					else
					{
						res = mysql_store_result(conn);
						row = mysql_fetch_row(res);
						if (row == NULL)
						{
							sprintf(respuesta, "5/El usuario no existe");
						}
						else
						{
							if (row[0] == NULL || strcmp(row[0], "") == 0)
							{
								sprintf(respuesta, "5/No tienes cartas");
							}
							else
							{
								sprintf(respuesta, "5/Tus cartas: %s", row[0]);
							}
						}
						mysql_free_result(res);
					}
				}
				else if(codigo == 7){ // Peticion de invitacion
					char inv = strtok(NULL, "/");
					pthread_mutex_lock(&mutex);
					int socketInvitado = BuscaSocketPorNombre(inv); // Buscar socket del cliente
					pthread_mutex_unlock(&mutex);
					sprintf(Invitacion,"7/%s",nombre);
					send(socketInvitado,Invitacion,strlen(Invitacion),0);
					
				}
				else if (codigo == 8) //Respuesta de la invitacion 
				{
					p = strtok(NULL, "/");
					char aux;
					strcpy(aux,p);
					p = strtok(NULL, "/");
					pthread_mutex_lock(&mutex);
					int socketInvitador = BuscaSocketPorNombre(p); // Buscar socket del cliente
					pthread_mutex_unlock(&mutex);
					sprintf(RespuestaInv, "8/%s", aux);
					send(socketInvitador,RespuestaInv,strlen(RespuestaInv),0);

				}
					
			}
		}
		if (codigo != 0)
		{
			printf("Respuesta: %s\n", respuesta);
			// Enviamos la respuesta
			write(sock_conn, respuesta, strlen(respuesta));
		}
		
		if (codigo == 1)
		{
			//Notificamos a los clientes
			char notificacion[20];
			DameConectados(&miLista, conectados);
			sprintf(notificacion, "6/%s", conectados);
			int j;
			for (j = 0; j < i; j++)
				write(sockets[j], notificacion, strlen(notificacion));
		}
	}

	if (session_iniciada)
	{
		pthread_mutex_lock(&mutex); //No interrumpir el thread 
		// Elimina el cliente de la lista de conectados
		if (EliminaConectado(&miLista, usuario_logueado) == -1)
		{
			printf("No se encontró al cliente %s en la lista de conectados\n", usuario_logueado);
			
			//Notificamos a los clientes
			char notificacion[20];
			DameConectados(&miLista, conectados);
			sprintf(notificacion, "6/%s", conectados);
			int j;
			for (j = 0; j < i; j++)
				write(sockets[j], notificacion, strlen(notificacion));
		}
		else
		{
			printf("El cliente %s ha sido eliminado de la lista de conectados\n", usuario_logueado);

		}
		pthread_mutex_unlock(&mutex); //Ya puedes interrumpir el thread
	}

	// Se acabo el servicio para este cliente
	mysql_close(conn);
	close(sock_conn);
}
	
int main(int argc, char *argv[])
{
	
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;

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
	serv_adr.sin_port = htons(50001);

	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	//La cola de peticiones pendientes no podr? ser superior a 4
	if (listen(sock_listen, 4) < 0)
		printf("Error en el Listen");

	miLista.num = 0;
	pthread_t thread;

	//bucle infinito
	for (;;) 
	{
		printf ("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("He recibido conexi?n\n");

		sockets[i] = sock_conn;
		//sock_conn es el socket que usaremos para este cliente

		//Crear thread y decirle que tiene que hacer
		pthread_create(&thread, NULL, AtenderClientes, &sockets[i]);
		i++;
	}
	return 0;
}
