#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql.h>
#include <mysql/mysql.h>



// Función para insertar un usuario en la base de datos
void insertar_usuario(const char* usuario, const char* contraseña) {
	MYSQL* conn;
	char query[256];

	// Inicializar la conexión
	conn = mysql_init(NULL);


	// Crear la consulta SQL para insertar un nuevo usuario
	snprintf(query, sizeof(query), "INSERT INTO Jugadores (usuario, password) VALUES ('%s', '%s')", usuario, contraseña);

	// Ejecutar la consulta
	if (mysql_query(conn, query)) {
		fprintf(stderr, "Error al insertar usuario: %s\n", mysql_error(conn));
	}
	else {
		printf("Usuario '%s' insertado correctamente.\n", usuario);
	}

	// Cerrar la conexión
	mysql_close(conn);
	printf("Conexión cerrada.\n");
}

void verificar_usuario(const char* usuario, const char* contraseña) {
	MYSQL* conn;
	MYSQL_RES* res;


	// Inicializar la conexión
	conn = mysql_init(NULL);

	// Conectar a MySQL
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "Error de conexión: %s\n", mysql_error(conn));
		exit(1);
	}

	printf("Conexión abierta exitosamente.\n");

	// Crear la consulta SQL para verificar la contraseña del usuario
	char query[256];
	snprintf(query, sizeof(query), "SELECT password FROM jugadores WHERE usuario='%s'", usuario);
	
	// Ejecutar la consulta
	if (mysql_query(conn, query)) {
		fprintf(stderr, "Error en la consulta: %s\n", mysql_error(conn));
		mysql_close(conn);
		return;
	}

	// Obtener los resultados de la consulta
	res = mysql_store_result(conn);

	// Comprobar si se encontró el usuario con la contraseña correcta
	if (strcmp(res,contraseña) == 0) {
		printf("La contraseña es correcta para el usuario '%s'.\n", usuario);
		return 0;
	}
	else {
		printf("La contraseña es incorrecta para el usuario '%s'.\n", usuario);
		return -1;
	}

	// Liberar el resultado y cerrar la conexión
	mysql_free_result(res);
	mysql_close(conn);
	printf("Conexión cerrada.\n");
}

char obtener_dinero(const char* usuario) {

	MYSQL* conn;
	MYSQL_RES* res;
	MYSQL_ROW row;

	// Conectar a la base de datos
	conn = mysql_init(NULL);

	char query[MAX_BUFFER];
	snprintf(query, sizeof(query), "SELECT dinero FROM usuarios WHERE usuario='%s'", usuario);
	mysql_query(conn, query);


	res = mysql_store_result(conn);
	if ((row = mysql_fetch_row(res)) != NULL) {
		double dinero = atof(row[0]);
		printf("El dinero del usuario '%s' es: %.2f\n", usuario, dinero);
	}
	else {
		printf("No se encontró el usuario '%s'.\n", usuario);
	}
	
	return res;
	// Limpiar
	mysql_free_result(res);
	mysql_close(conn);



}

char obtener_victorias(const char* usuario) {

	MYSQL* conn;
	MYSQL_RES* res;
	MYSQL_ROW row;

	// Conectar a la base de datos
	conn = mysql_init(NULL);

	char query[MAX_BUFFER];
	snprintf(query, sizeof(query), "SELECT victorias FROM usuarios WHERE usuario='%s'", usuario);
	mysql_query(conn, query);


	res = mysql_store_result(conn);
	if ((row = mysql_fetch_row(res)) != NULL) {
		double dinero = atof(row[0]);
		printf("Las victorias del usuario '%s' es: %.2f\n", usuario, dinero);
	}
	else {
		printf("No se encontró el usuario '%s'.\n", usuario);
	}
	return res;
	// Limpiar
	mysql_free_result(res);
	mysql_close(conn);



}




int main(int argc, char *argv[])
{	
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char peticion[512];
	char respuesta[512];

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
	// escucharemos en el port 9050
	serv_adr.sin_port = htons(9050);

	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	//La cola de peticiones pendientes no podr? ser superior a 4
	if (listen(sock_listen, 4) < 0)
		printf("Error en el Listen");

	int i;
	//bucle infinito
	for (;;) {
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
			char contraseña[20];

			if (codigo !=0)
			{ 

				p = strtok( NULL, "/");
				strcpy (nombre, p);
				printf ("Codigo: %d, Nombre: %s\n", codigo, nombre);

			}
		
			if (codigo == 0)
				terminar = 1;
			
			else if (codigo == 1) //registar el usuario dentro de la base de datos
			{

				MYSQL* conn;
				MYSQL_RES* res;
				MYSQL_ROW row;
				int err;


				p = strtok(NULL, "/");
				strcpy(nombre, p);

				P = strtok(NULL, "/");
				strcpy(contraseña, p);

				insertar_usuario(nombre, contraseña);
				return 0;
				
			}


		}

			else if (codigo ==2) //Quieren saber si el nombre es bonito 
			{ 
		
				if((nombre[0]=='M') || (nombre[0]=='S')) 
					strcpy (respuesta,"SI");
			
				else
					strcpy (respuesta,"NO");
			}

			else if (codigo ==3) //decir dinero
			{
				p = strtok(NULL, "/");
				
				strcpy(respuesta, obtener_dinero(p));

			}

			else if (codigo == 4) //decir si es palindromo
			{
				p = strtok(NULL, "/");
				strcpy(respuesta, obtener_victorias(p));
				
			}

			else if (codigo ==5)
			{
				for (i = 0; nombre[i] != '\0'; i++) 
				{
					//Comprobamos que los caracteres entres dentro de a-z
					if (nombre[i] >= 'a' && nombre[i] <= 'z') {
						respuesta[i] = nombre[i] - 32; // Restar 32 convierte una letra minúscula en mayúscula
					}
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
}
