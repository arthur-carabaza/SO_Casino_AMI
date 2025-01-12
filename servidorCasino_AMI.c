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

//_________________________________________________________________________________

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

//_________________________________________________________________________________

//INICIALIZAMOS LISTAS DE CONECTADOS I SALAS
ListaConectados ListaContectados;
ListaSala ListaSalas;
char conectados[300];
int i = 0;
int sockets[100];
Mensaje chatMensajes[100];
int chatIndex = 0; //Indice del mensaje actual 
int idSalaActual = -1;
int session_iniciada = 1;


////_________________________________________________________________________________

//METODOS GENERALES PARA EL CODIGO Poner,Quitar,Dar Conectados, buscar sockets etc...

void BorrarTablas(MYSQL *conn) {
	const char *queries[] = {
		"SET FOREIGN_KEY_CHECKS = 0;",
			"TRUNCATE TABLE Participantes;",
			"TRUNCATE TABLE Mensajes;",
			"TRUNCATE TABLE Salas;",
			"SET FOREIGN_KEY_CHECKS = 1;"
	};
	
	for (int i = 0; i < 5; i++) {
		if (mysql_query(conn, queries[i])) {
			printf("Error ejecutando query: %s\n", mysql_error(conn));
		}
	}
	printf("Contenido de las tablas borrado (excepto Jugadores).\n");
}


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
	return -1; // No se encontro la sala
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

int QuitaSala(ListaSala *lista, int idSala){
	//Le pasamos el idSala y nos quita la sala cuyo idS hemos introducido de la lista de salas
	
	pthread_mutex_lock(&mutex);
	for(int i =idSala-1; i<lista->num-1;i++){
		lista->salas[i]=lista->salas[i+1];
	} 
	lista->num--;
	pthread_mutex_unlock(&mutex);
	return 0;
}

int PonSalaDB(MYSQL* conn, Sala* nuevaSala, ListaConectados* listaConectados, int* jugadores, int numJugadores) {
	// Insertar la sala en la tabla Salas
	char query[256];
	sprintf(query, "INSERT INTO Salas () VALUES ()"); //La fecha se crea automaticameumnte
	if (mysql_query(conn, query)) {
		printf("Error al insertar sala en la base de datos: %s\n", mysql_error(conn));
		return -1;
	}

	// Obtener el ID de la sala recién creada
	int idSala = mysql_insert_id(conn);

	// Insertar los participantes en la tabla Participantes
	for (int i = 0; i < numJugadores; i++) {
		char nombre[20];
		strcpy(nombre, listaConectados->conectados[jugadores[i]].nombre);

		sprintf(query, "INSERT INTO Participantes (sala_id, usuario_id) "
			"SELECT %d, id FROM Jugadores WHERE usuario='%s'", idSala, nombre);

		if (mysql_query(conn, query)) {
			printf("Error al insertar participante en la base de datos: %s\n", mysql_error(conn));
			return -1;
		}
	}

	return idSala;
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

char* BuscaNombrePorSocket(ListaConectados* miLista, int socket) {
	//Con esta funcion entregamos un socket y nos da el su nombre buscando en la lista de conectaddos
	// Recorremos la lista de conectados para buscar el socket
	for (int i = 0; i < miLista->num; i++) {
		// Comparamos el socket dado con los sockets almacenados
		if (miLista->conectados[i].socket == socket) {
			return miLista->conectados[i].nombre; // Devolvemos el nombre asociado al socket
		}
	}
	return NULL; // Retornamos NULL si no se encontró
}


void DameConectados(ListaConectados* lista, char conectados[300]) {
	//Escribe en la char de conectados los nombre de todos los coenctados separados por /
	//Primero Pone el numero de conectados: 3/Pedro/Maria/Juan
	sprintf(conectados, "%d", lista->num);
	int i;
	for (i = 0; i < lista->num; i++)
		sprintf(conectados, "%s:%s", conectados, lista->conectados[i].nombre);

}

//_________________________________________________________________________________

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
		if ((codigo != 0)&&(codigo !=6)&&(codigo !=12)&&(codigo!=14))
		{
			//Obtenemos el numforms
			p = strtok(NULL, "/");
			numForms = atoi(p);

			//Obtenemos el nombre 
			p = strtok(NULL, "/");
			strcpy(nombre, p);
			printf("Codigo: %d, Nombre: %s\n", codigo, nombre);
		}
		if (codigo == 0)
			terminar = 1;

		//_________________________________________________________________________________

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
					sprintf(respuesta, "1/NO/usuario no existe");
				}
				else
				{
					if (strcmp(row[0], password) == 0)
					{
						sprintf(respuesta, "1/SI/Inicio de session correcto");
						strcpy(usuario_logueado, nombre);

						// Ahora añadimos al cliente a la lista de conectados
						pthread_mutex_lock(&mutex); //No me interrumpas ahora el proceso de este thread
						if (PonConectado(&ListaContectados, nombre, sock_conn) == -1)
						{
							printf("La lista de conectados esta llena\n");
						}
						else
						{
							printf("El cliente %s se ha anadido a la lista de conectados\n", nombre);
						}
						pthread_mutex_unlock(&mutex); //Ya puedes interrumpir el proceso de este thread
					}
					else
					{
						sprintf(respuesta, "1/NO/Contrasenya incorrecta");
					}
				}
				mysql_free_result(res);

			}
		}

		//_________________________________________________________________________________

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

		//_________________________________________________________________________________

		//QUERIS DE SQL 
		else if (codigo == 3 || codigo == 4 || codigo == 5)
		{
			//QUERRY CODIGO 3 CON QUIEN HE ESTADO EN SALA 3/0/nombre
			if (codigo == 3)
			{
				char query[256];
				sprintf(query, "SELECT DISTINCT J.usuario "
						"FROM Jugadores J "
						"JOIN Participantes P ON J.id = P.usuario_id "
						"JOIN Salas S ON P.sala_id = S.id "
						"WHERE S.id IN ("
						"    SELECT sala_id "
						"    FROM Participantes "
						"    WHERE usuario_id = ("
						"        SELECT id FROM Jugadores WHERE usuario = '%s'"
						"    )"
						"    AND S.idS = ("
						"        SELECT idS FROM Salas JOIN Participantes ON Salas.id = Participantes.sala_id "
						"        WHERE usuario_id = (SELECT id FROM Jugadores WHERE usuario = '%s')"
						"        LIMIT 1"
						"    )"
						") AND J.usuario != '%s';", nombre, nombre, nombre);
				
				
				//CONTROL DE ERROR POR SI DA ERROR LA QUERY
				err = mysql_query(conn, query);
				if (err != 0) {
					printf("Error al consultar la base de datos: %s\n", mysql_error(conn));
					sprintf(respuesta, "3/Error en la base de datos");
				}
				else {
					//SI NO DA ERROR CONSTRUIMOS LA RESPUESTA
					//LA RESPUESTA SERA DEL ESTILO 3/Juan,Miguel,Carlos

					MYSQL_RES* res = mysql_store_result(conn);
					MYSQL_ROW row;
					char coincidencias[1024] = "";

					while ((row = mysql_fetch_row(res))) {
						if (strlen(coincidencias) > 0) {
							strcat(coincidencias, ",");
						}
						strcat(coincidencias, row[0]); // Agregamos cada nombre a la lista
					}
					mysql_free_result(res);

					if (strlen(coincidencias) == 0) {
						sprintf(respuesta, "3/No has coincidido con nadie aun");
					}
					else {
						sprintf(respuesta, "3/Has estado en sala con: %s", coincidencias);
					}
				}
			}
			
			//QUERY DE CUANTOS MENSAJES HE ENVIADO A UN DETERMINADO DESTINATARIO 4/0/nombre/destinatarip
			else if (codigo == 4) { 
				//Obtenemos el nombre del destinatario
				p = strtok(NULL, "/");
				char destinatario[20];
				strcpy(destinatario, p);

				//Querry para enviar mensajes enviados
				char query[512];
				sprintf(query,
					"SELECT COUNT(m.id) "
					"FROM Mensajes m "
					"JOIN Participantes p1 ON m.usuario_id = p1.usuario_id "
					"JOIN Participantes p2 ON p1.sala_id = p2.sala_id AND p1.usuario_id != p2.usuario_id "
					"JOIN Jugadores j2 ON p2.usuario_id = j2.id "
					"WHERE m.usuario_id = (SELECT id FROM Jugadores WHERE usuario = '%s') "
					"AND j2.usuario = '%s'",
					nombre, destinatario);

				//CONTROL DE ERROR POR SI DA ERROR LA QUERY
				err = mysql_query(conn, query);
				if (err != 0) {
					printf("Error al consultar la base de datos: %s\n", mysql_error(conn));
					sprintf(respuesta, "4/Error en la base de datos");
				}
				else {
					//SI NO DA ERROR MONTAMOS EL MENSAJE DE RESPUESTA
					// 4/Le has enviado 30 mensajes a Miguel

					MYSQL_RES* res = mysql_store_result(conn);
					MYSQL_ROW row = mysql_fetch_row(res);

					if (row && row[0]) {
						int num_mensajes = atoi(row[0]);
						sprintf(respuesta, "4/Le has enviado %d mensajes a %s", num_mensajes, destinatario);
					}
					else {
						sprintf(respuesta, "4/No le has enviado mensajes a %s", destinatario);
					}
					mysql_free_result(res);
				}
			}

			//QUERRY DE QUE SALAS HA HABIDO EN UN DETERMINADO TIEMPO 5/0/nombre/fehca inicio/fecha fin. Las fechas se introducen asi: 2025-01-01 00:00:00/2025-01-11 23:59:59
			else if (codigo == 5) { 
				// Obtener las fechas desde el cliente
				p = strtok(NULL, "/");
				char fecha_inicio[20];
				strcpy(fecha_inicio, p);

				p = strtok(NULL, "/");
				char fecha_fin[20];
				strcpy(fecha_fin, p);

				// Query para obtener las salas y sus participantes
					char query[512];
				sprintf(query,
					"SELECT s.id AS sala_id, GROUP_CONCAT(j.usuario) AS participantes "
					"FROM Salas s "
					"JOIN Participantes p ON s.id = p.sala_id "
					"JOIN Jugadores j ON p.usuario_id = j.id "
					"WHERE s.fecha_creacion BETWEEN '%s' AND '%s' "
					"GROUP BY s.id",
					fecha_inicio, fecha_fin);

				//CONTROL DE ERROR POR SI LA QUERY DA ERROR
				err = mysql_query(conn, query);
				if (err != 0) {
					printf("Error al consultar la base de datos: %s\n", mysql_error(conn));
					sprintf(respuesta, "5/Error al consultar las salas");
				}
				//SI NO DA ERROR MONTAMOS EL MENSAJE DE RESPUESTA
				else {
					MYSQL_RES* res = mysql_store_result(conn);
					MYSQL_ROW row;
					char resultado[1024] = "5/";

					while ((row = mysql_fetch_row(res))) {
						char linea[256];
						sprintf(linea, "Sala %s: %s | ", row[0], row[1]); // ID de sala y participantes
						strcat(resultado, linea);

						//EN EL CASO DE ENCONTRAR SALA DARA UN RESULTADO DEL SIGUENTE ESTILO:
						// 5/ Sala 1: Juan, Miguel | Sala 2 : Miguel, Carlos |

					}
					mysql_free_result(res);

					if (strcmp(resultado, "5/") == 0) {
						strcat(resultado, "No hay salas en el intervalo especificado");
					}
					strcpy(respuesta, resultado);
				}
			}
		}

		//_________________________________________________________________________________
		
		//MECANISMO DE INVITACION / ACEPTAR o RECHAZAR RESPUESTA
		else if (codigo ==7 || codigo ==8)
		{
			//EL CLIENTE INVITADOR QUIERE INVITAR A ALGUIEN 7/0/nombreInvitado
			if (codigo == 7) 
			{
			
				pthread_mutex_lock(&mutex);
				int socketInvitado = BuscaSocketPorNombre(&ListaContectados, nombre);
				pthread_mutex_unlock(&mutex);

				if (socketInvitado != -1) {
					sprintf(respuesta, "9/Invitacion enviada a %s", nombre);
					write(sock_conn, respuesta, strlen(respuesta));

					if (idSalaActual == -1) { // Crear sala si no existe
						Sala nuevaSala;
						nuevaSala.numSockets = 0;
						nuevaSala.sockets[nuevaSala.numSockets++] = sock_conn;
						idSalaActual = PonSala(&ListaSalas, nuevaSala);

				

						//Añadimos la sala a la base de datos:
						char query[256];
						sprintf(query, "INSERT INTO Salas (idS) VALUES (%d)", idSalaActual); // La fecha se genera automáticamente
						if (mysql_query(conn, query)) {
							printf("Error al insertar sala en la base de datos: %s\n", mysql_error(conn));
						}

						//Añadimos el primer jugador a la base de datos
						sprintf(query, "INSERT INTO Participantes (sala_id, usuario_id) SELECT %d, id FROM Jugadores WHERE usuario='%s'", idSalaActual, usuario_logueado);
						if (mysql_query(conn, query)) {
							printf("Error al insertar participante en la base de datos: %s\n", mysql_error(conn));
						}
					}

					pthread_mutex_lock(&mutex);
					Sala* salaActual = &ListaSalas.salas[idSalaActual];
					salaActual->sockets[salaActual->numSockets++] = socketInvitado;
					pthread_mutex_unlock(&mutex);

					//SE ENVIA AL CLIENTE INVITADO UNA RESPUESTA 7/nombreInvitador
					sprintf(respuestaINV, "7/%s", usuario_logueado);
					write(socketInvitado, respuestaINV, strlen(respuestaINV));

				}
				else {
					sprintf(respuesta, "9/Usuario %s no encontrado", nombre);
					write(sock_conn, respuesta, strlen(respuesta));
				}
			}
				
			//EL CLIENTE HA RECIBIDO UNA PETICION 7/ Y A CONTESTADO A LA INVITACION GENERANDO UNA PETICION
			// 8/0/nomInvitador/SI o NO ; SI ES SI SE LE ANADE A LA SALA 
			// SE GENERA UNA RESPUESTA 8/SI o NO/idSala SI ES UNA SIMPLE NOTIFICACION, SI ES NO SE LE PREGUNTA AL INVITADOR POR EL FUTURO DE LA SALA
			else if (codigo == 8) { 
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
							printf("Respuesta: %s\n", respuestaBool); 
							write(socketInvitador, respuestaBool, strlen(respuestaBool));
							
							char query[256];
							//Añadimos el siguiente jugador a la base de datos
							sprintf(query, "INSERT INTO Participantes (sala_id, usuario_id) SELECT %d, id FROM Jugadores WHERE usuario='%s'", idSalaActual, usuario_logueado);
							if (mysql_query(conn, query)) {
								printf("Error al insertar sala en la base de datos: %s\n", mysql_error(conn));
							}
						}
						else {
							sprintf(respuesta, "9/Sala llena");
						}
					}
					else if (strcmp(p, "NO") == 0) { 
						
						sprintf(respuestaBool, "8/%s/%d",p,idSalaActual); 
						printf("Respuesta: %s\n", respuestaBool); 
					
						write(socketInvitador, respuestaBool, strlen(respuestaBool)); 
					} 
				} 
				else { 
					sprintf(respuesta, "9/No se encuentra al usuario invitador"); 
				} 
			}
			
		}

		//_________________________________________________________________________________
		
		//PETICION 10 PARA ENVIAR MENSAJES 10/idS/nombre/mensaje
		else if (codigo == 10) { 
			
			// Obtener el mensaje del cliente
			p = strtok(NULL, "/");
			char mensaje[512];
			strcpy(mensaje, p);

			//POR RAZONES LOGISTICAS EN ESTE METODO EL idS, es decir el numero id de la sala de chat se le llama numForms
			//POR TANTO SOLO Y SOLO EN ESTE METODO numForms = idS

			//Comprovacion con prints del sock_con i el numForms
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
				
				sprintf(respuestaINV, "9/Mensaje enviado correctamente");
				printf("Respuesta: %s\n", respuestaINV);
				// Enviamos la respuesta
				write(sock_conn, respuestaINV, strlen(respuestaINV	));
				
				

				// Guardar el mensaje en la base de datos
				char query[512];
				sprintf(query,
					"INSERT INTO Mensajes (sala_id, usuario_id, mensaje) "
					"VALUES (%d, (SELECT id FROM Jugadores WHERE usuario='%s'), '%s')",
					numForms, nombre, mensaje);

				if (mysql_query(conn, query)) {
					printf("Error al registrar el mensaje en la base de datos: %s\n", mysql_error(conn));
					sprintf(respuesta, "9/Error al registrar el mensaje");
					
					printf("Respuesta: %s\n", respuesta);
					// Enviamos la respuesta
					write(sock_conn, respuesta, strlen(respuesta));
					
				}
				else {
					sprintf(respuesta, "9/Mensaje enviado correctamente");
				}
			}
			else 
			{
				printf("Error: No se encontro la sala para el socket %d\n", sock_conn);
				sprintf(respuesta, "10/%d/Error al enviar el mensaje: sala no encontrada",numForms);
				write(sock_conn, respuesta, strlen(respuesta));
			}
			
		}

		//_________________________________________________________________________________

		//PETICION DE INICIAR LA SALA, UNA VEZ DE SE HA INVITADO A LA LOS JUGADORES 12/idS
		else if (codigo == 12) { // Iniciar sala manualmente

			
			//Obtenemos el IDsala
			p = strtok(NULL, "/");
			int idSala = atoi(p); // ID de la sala
			printf("%d\n", idSala);

			// Buscar la sala en la lista
			if (idSala != -1) 
			{
				Sala* sala = &ListaSalas.salas[idSala-1];
				
				char JugadoresDeSala[200]="";
				for(int i =0; i<sala->numSockets;i++)
				{
					char *nombresAUX = BuscaNombrePorSocket(&ListaContectados,sala->sockets[i]);
					printf("%s\n",nombresAUX);
					sprintf(JugadoresDeSala, "%s,%s",JugadoresDeSala,nombresAUX);
				}
				
				printf("%s\n",JugadoresDeSala);
				printf("%d\n",sala->numSockets);
				idSalaActual =-1;

				// Notificar a todos los clientes de la sala
				for (int i = 0; i < sala->numSockets; i++) 
				{
					sprintf(respuesta, "12/%d/%s", idSala,JugadoresDeSala);
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

		//_________________________________________________________________________________

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
		
		//_________________________________________________________________________________
		
		else if (codigo == 14) { // Eliminar sala manualmente
			
			
			//Obtenemos el IDsala
			p = strtok(NULL, "/");
			
			int idSala = atoi(p); // ID de la sala
			int i = QuitaSala(&ListaSalas,idSala);
			printf("Se ha eliminado la sala");
			sprintf(respuesta, "9/Se ha eliminado la sala, ya puede volver a invitar a los jugadores");
		}

		//_________________________________________________________________________________

		//EXCEPCION PARA CASOS DE RESPUESTAS POCO HABITALES
		//LA MAYORIA DE LAS PETICIONES LA RESPIESTA SE REENVIA AL sock_conn POR ESO SE RECOGEN AQUI EXEPTO CASOS PARITCULARES
		if (codigo != 0 && codigo!= 7 && codigo!= 8 && codigo !=10 && codigo!=12)
		{
			printf("Respuesta: %s\n", respuesta);
			// Enviamos la respuesta
			write(sock_conn, respuesta, strlen(respuesta));
		}
		
		//CONDIFICON DE CONEXION/DESCONEXION PARA ACTUALIZAR LA LISTA DE CONECTADOS
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
	
	//_________________________________________________________________________________
	//CONDICION PARA TRATAR LA DESCONEXION

	if (session_iniciada)
	{
		pthread_mutex_lock(&mutex); //No interrumpir el thread 
		// Elimina el cliente de la lista de conectados
		if (EliminaConectado(&ListaContectados, usuario_logueado) == -1)
		{
			printf("No se encontro al cliente %s en la lista de conectados\n", usuario_logueado);
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

//_________________________________________________________________________________
//MAIN DEL SERVIDOR
	
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
	serv_adr.sin_port = htons(50005);

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
		printf ("He recibido conexion\n");

		sockets[i] = sock_conn;
		//sock_conn es el socket que usaremos para este cliente

		//Crear thread y decirle que tiene que hacer
		pthread_create(&thread, NULL, AtenderClientes, &sockets[i]);
		i++;
	}
		
	return 0;
}
