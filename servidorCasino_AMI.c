#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include <pthread.h>

#define MAX_CLIENTES 100
#define MAX_SALAS 10

//Estructura necesaria para el acceso excluyente
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//DEFINICION DE ESTRUCURAS Conectado, LConectados, Salas, LSalas
typedef struct {
	char nombre[20];
	int socket;
} Conectado;

typedef struct {
	Conectado conectados[100];
	int num;
} ListaConectados;

typedef struct {
	char mensaje[512];
	char usuario[20];
}Mensaje;

typedef struct {
	int numSockets;
	int sockets[MAX_CLIENTES]; //Sockets de los clientes de la sala

}Sala;

typedef struct {
	int num;
	Sala salas[MAX_SALAS];
}ListaSala;


//INICIALIZAMOS LISTAS DE CONECTADOS I SALAS
ListaConectados ListaContectados;
ListaSala ListaSalas;
char conectados[300];
int i = 0;
int sockets[100];
Mensaje chatMensajes[100];
int chatIndex = 0; //Indice del mensaje actual 
int idSalaActual = -1;

//METODOS GENERALES PARA EL CODIGO Poner,Quitar,Dar Conectados, buscar sockets etc...
int BuscarSalaPorSocket(ListaSala *listaSalas, int socket) {
	//Devuelve el indice de la sala en la que se encuentra el usuario cuyo socket se pasa como parametro
	//Devuelve -1 si no encuentra la sala
	for (int i = 0; i < listaSalas->num; i++) {
		for (int j = 0; j < listaSalas->salas[i].numSockets; j++) {
			if (listaSalas->salas[i].sockets[j] == socket) {
				return i; // Devuelve el indice de la sala en la lista
			}
		}
	}
	return -1; // No se encontr la sala
}

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

int PonSala(ListaSala *lista, Sala nuevaSala) {
	// Añade una nueva sala a la lista de salas
	// Devuelve -1 si la lista estÃ¡ llena, 0 si se ha hecho correctamente
	if (lista->num == MAX_SALAS)
		return -1;
	else {
		lista->salas[lista->num] = nuevaSala;
		lista->num++;
		int num = lista->num;
		printf("Estas creando una sala de id %d",num);
		return num;
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
int BuscaSocketPorNombre(ListaConectados *miLista,char *nombre) {
	// Con esta funcion entregamos el nombre de un usuario y nos devuelve su socket directamente por como esta definida el objeto de conectados
    for (int i = 0; i < miLista->num; i++) 
	{
		//Comparamos el nombre dado con la lista de cada nombre
        if (strcmp(miLista->conectados[i].nombre, nombre) == 0) 
		{
            return miLista->conectados[i].socket;
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


//FUNCION ATENDER CLIENTES
void* AtenderClientes(void* socket) 
{
	int sock_conn;
	int* s;
	s = (int*)socket;
	sock_conn = *s;

	// Chars para trabajar con Peticion / Respuesta entre servidor y cleinte
	char peticion[512];
	char respuesta[1024];
	char respuestaINV[512];
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
	
	if (mysql_real_connect(conn, "localhost", "root", "mysql", "JuegoChat", 0, NULL, 0) == NULL) 
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
		
		strcpy(respuesta,"");

		ret = read(sock_conn, peticion, sizeof(peticion));
		printf("Recibida una petición\n");
		// Tenemos que a?adirle la marca de fin de string 
		// para que no escriba lo que hay despues en el buffer
		peticion[ret] = '\0';

		//Escribimos la peticion en la consola

		printf("La petición es: %s\n", peticion);

		//Obtenemos el codigo de peticion
		char* p = strtok(peticion, "/");
		int codigo = atoi(p);

		//Variable para guardar el codigo del servidor
		int numForms;
		
		char nombre[20];
		char password[20];
		char nombreInvitado[20];

		//LAS PETICIONES 0,6 y 12 NO NECESTAN EL NOMBRE PARA FUNCIONAR
		if ((codigo != 0)&&(codigo !=6)&&(codigo !=12))
		{
			//Obtenemos el IDsala
			p = strtok(NULL, "/");
			numForms = atoi(p);

			//Obtenemos el nombre 
			p = strtok(NULL, "/");
			strcpy(nombre, p);
			printf("Codigo: %d, Nombre: %s\n", codigo, nombre);
		}
		if (codigo == 0)
			terminar = 1;

		//USUARIO INICIA SESSION 1/0/nombre/contraseña
		else if (codigo == 1) 
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
					sprintf(respuesta, "1/usuario no existe");
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
						if (PonConectado(&ListaContectados, nombre, sock_conn) == -1)
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

		//USUARIO SE REGISTRA 2/numForms/nombre/contraseña
		else if (codigo == 2)  
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

		//QUERIS DE SQL 
		else if (codigo == 3 || codigo == 4 || codigo == 5)
		{
			if (session_iniciada == 0) {
				sprintf(respuesta, "9/Debes iniciar primero");
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
							sprintf(respuesta, "3/Dinero disponible: %.2f/%s", atof(row[0]),usuario_logueado);
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
			}
		}
		
		//INVITACION A PARTIDAS 7/ y acceptar/rechazar partidas 8/
		else if (codigo ==7 || codigo ==8)
		{
			if (session_iniciada == 0) 
			{
				sprintf(respuesta, "9/Debes iniciar session primero");
			}
			else 
			{
				if (codigo == 7) 
				{ // Peticion de invitacion
				
					pthread_mutex_lock(&mutex);
					int socketInvitado = BuscaSocketPorNombre(&ListaContectados, nombre);
					pthread_mutex_unlock(&mutex);

					if (socketInvitado != -1) {
						sprintf(respuesta, "9/Invitación enviada a %s", nombre);
						write(sock_conn, respuesta, strlen(respuesta));

						if (idSalaActual == -1) { // Crear sala si no existe
							Sala nuevaSala;
							nuevaSala.numSockets = 0;
							nuevaSala.sockets[nuevaSala.numSockets++] = sock_conn;
							idSalaActual = PonSala(&ListaSalas, nuevaSala);
						}

						pthread_mutex_lock(&mutex);
						Sala* salaActual = &ListaSalas.salas[idSalaActual];
						salaActual->sockets[salaActual->numSockets++] = socketInvitado;
						pthread_mutex_unlock(&mutex);

						sprintf(respuestaINV, "7/%s", usuario_logueado);
						write(socketInvitado, respuestaINV, strlen(respuestaINV));
					}
					else {
						sprintf(respuesta, "9/Usuario %s no encontrado", nombre);
						write(sock_conn, respuesta, strlen(respuesta));
					}
				}
				
				else if (codigo == 8) { // El cliente responde a la invitacion 
					pthread_mutex_lock(&mutex); 
					int socketInvitador = BuscaSocketPorNombre(&ListaContectados, nombre); // Buscar socket del cliente invitador 
					pthread_mutex_unlock(&mutex); 
					
					if (socketInvitador != -1) { 
						char respuestaBool[20]; 
						p = strtok(NULL, "/"); 

						
						
						if (strcmp(p, "SI") == 0) {
							Sala* salaActual = &ListaSalas.salas[idSalaActual-1];
							if (salaActual->numSockets < MAX_CLIENTES) {
								salaActual->sockets[salaActual->numSockets] = sock_conn;
								salaActual->numSockets++;
								sprintf(respuestaBool, "8/%s/%d", p, idSalaActual);
								write(socketInvitador, respuestaBool, strlen(respuestaBool));
								write(sock_conn, respuestaBool, strlen(respuestaBool));
							}
							else {
								sprintf(respuesta, "9/Sala llena");
							}
						}
						else if (strcmp(respuestaBool, "8/NO") == 0) { 
							sprintf(respuesta, "9/Invitacion rechazada"); 
							p = strtok(NULL, "/"); 
							sprintf(respuestaBool, "8/%s", p); 
							printf("Respuesta: %s\n", respuestaBool); 
						
							write(socketInvitador, respuestaBool, strlen(respuestaBool)); 
						} 
					} 
					else { 
						sprintf(respuesta, "9/No se encuentra al usuario invitador"); 
					} 
				}
			}
		}
		
		else if (codigo == 10) { 
			if (session_iniciada == 0) 
			{
				sprintf(respuesta, "10/%d/Debes iniciar sesión primero",numForms);
			}
			else 
			{
				// Obtener el mensaje del cliente
				p = strtok(NULL, "/");
				char mensaje[512];
				strcpy(mensaje, p);

				

				// Buscar la sala en la que está el usuario
				int indiceSala = BuscarSalaPorSocket(&ListaSalas, sock_conn);
				printf("%d\n",sock_conn);
				printf("%d\n",numForms);
				// Formatear el mensaje para enviar a todos los clientes de la sala
				sprintf(respuesta, "10/%d/%s: %s",numForms, usuario_logueado, mensaje);
				if (numForms-1 != -1) {
					// Enviar el mensaje a todos los clientes de la sala correspondiente
					Sala* sala = &ListaSalas.salas[numForms-1];
					for (int i = 0; i < sala->numSockets; i++) 
					{
						printf("%d",sala->sockets[i]);
						if (sala->sockets[i] != sock_conn) 
						{
							printf("Enviando mensaje a socket %d: %s\n", sala->sockets[i], respuesta);
							write(sala->sockets[i], respuesta, strlen(respuesta));
						}
					}
				}
				else 
				{
					printf("Error: No se encontró la sala para el socket %d\n", sock_conn);
					sprintf(respuesta, "10/%d/Error al enviar el mensaje: sala no encontrada",numForms);
					write(sock_conn, respuesta, strlen(respuesta));
				}
			}
		}

		else if (codigo == 12) { // Iniciar sala manualmente

			
			//Obtenemos el IDsala
			p = strtok(NULL, "/");
			int idSala = atoi(p); // ID de la sala
			printf("%d\n", idSala);

			// Buscar la sala en la lista
			if (idSala != -1) 
			{
				Sala* sala = &ListaSalas.salas[idSala-1];
				printf("estoy entrando aqui\n");
				printf("%d\n",sala->numSockets);
				idSalaActual =-1;

				// Notificar a todos los clientes de la sala
				for (int i = 0; i < sala->numSockets; i++) 
				{
					sprintf(respuesta, "12/%d/Iniciar", idSala);
					printf("Respuesta: %s\n", respuesta);
					write(sala->sockets[i], respuesta, strlen(respuesta));
				}
			}
			else 
			{
				sprintf(respuesta, "12/Error al iniciar la sala");
				printf("Respuesta: %s\n", respuesta);
				write(sock_conn, respuesta, strlen(respuesta));
			}
		}

		// USUARIO SE DA DE BAJA 13/nombre
		else if (codigo == 13)
		{
		
			// Consulta para eliminar al jugador
			char query[256];
			sprintf(query, "DELETE FROM Jugadores WHERE usuario='%s'", nombre);

			err = mysql_query(conn, query);
			if (err != 0) {
				if (mysql_errno(conn) == 0) { // Si no hay error específico pero no se eliminó
					sprintf(respuesta, "13/El usuario no existe");
				}
				else {
					printf("Error al eliminar de la base de datos: %s\\n", mysql_error(conn));
					sprintf(respuesta, "13/Error al darse de baja");
				}
			}
			else
			{
				sprintf(respuesta, "13/Baja exitosa");
			}
		}

		if (codigo != 0 && codigo!= 7 && codigo!= 8 && codigo !=10 && codigo!=12)
		{
			printf("Respuesta: %s\n", respuesta);
			// Enviamos la respuesta
			write(sock_conn, respuesta, strlen(respuesta));
		}
		
		if (codigo == 1 || codigo == 0)
		{
			//Notificamos a los clientes
			char notificacion[20];
			DameConectados(&ListaContectados, conectados);
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
		if (EliminaConectado(&ListaContectados, usuario_logueado) == -1)
		{
			printf("No se encontró al cliente %s en la lista de conectados\n", usuario_logueado);
		}
		else
		{
			printf("El cliente %s ha sido eliminado de la lista de conectados\n", usuario_logueado);
			//Notificamos a los clientes
			char notificacion[20];
			DameConectados(&ListaContectados, conectados);
			sprintf(notificacion, "6/%s", conectados);
			int j;
			for (j = 0; j < i; j++)
				write(sockets[j], notificacion, strlen(notificacion));

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

	ListaContectados.num = 0;
	ListaSalas.num = 0; //Inicializamos el numero de sockets en la sala
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
