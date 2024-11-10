#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
	char nombre[20];
	int socket;
} Conectado;

typedef struct {
	Conectado conectados[100];
	int num;
} ListaConectados;

ListaConectados miLista;
char conectados[300];
int contador = 0;
int i = 0;
int sockets[100];

int PonConectado(ListaConectados *lista, char nombre[20], int socket) {
	if (lista->num == 100)
		return -1;
	strcpy(lista->conectados[lista->num].nombre, nombre);
	lista->conectados[lista->num].socket = socket;
	lista->num++;
	return 0;
}

int DamePosicion(ListaConectados *lista, char nombre[20]) {
	int i = 0;
	while (i < lista->num) {
		if (strcmp(lista->conectados[i].nombre, nombre) == 0)
			return i;
		i++;
	}
	return -1;
}

int EliminaConectado(ListaConectados *lista, char nombre[20]) {
	int pos = DamePosicion(lista, nombre);
	if (pos == -1)
		return -1;
	
	for (int i = pos; i < lista->num - 1; i++) {
		strcpy(lista->conectados[i].nombre, lista->conectados[i + 1].nombre);
		lista->conectados[i].socket = lista->conectados[i + 1].socket;
	}
	lista->num--;
	return 0;
}

void DameConectados(ListaConectados* lista, char conectados[300]) {
	sprintf(conectados, "%d", lista->num);
	for (int i = 0; i < lista->num; i++) {
		sprintf(conectados, "%s/%s", conectados, lista->conectados[i].nombre);
	}
}

void* AtenderClientes(void* socket) {
	int sock_conn = *(int*)socket;
	char peticion[512];
	char respuesta[512];
	int ret;
	int terminar = 0;
	
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int err;
	
	conn = mysql_init(NULL);
	if (conn == NULL) {
		printf("Error al crear la conexión MySQL: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	if (mysql_real_connect(conn, "shiva2.upc.es", "root", "mysql", "M1_JuegoPoker", 0, NULL, 0) == NULL) {
		printf("Error al inicializar la conexión con la base de datos: %u %s\n", mysql_errno(conn), mysql_error(conn));
		mysql_close(conn);
		exit(1);
	}
	
	int session_iniciada = 0;
	char usuario_logueado[100] = "";
	
	while (!terminar) {
		ret = read(sock_conn, peticion, sizeof(peticion));
		peticion[ret] = '\0';
		
		printf("Petición recibida: %s\n", peticion);
		
		char* p = strtok(peticion, "/");
		int codigo = atoi(p);
		char nombre[20];
		char password[20];
		
		if (codigo > 0 && codigo != 6) {
			p = strtok(NULL, "/");
			strcpy(nombre, p);
			printf("Código: %d, Nombre: %s\n", codigo, nombre);
		}
		if (codigo == 0) {
			terminar = 1;
		} else if (codigo == 1) {
			p = strtok(NULL, "/");
			strcpy(password, p);
			
			char query[256];
			sprintf(query, "SELECT password FROM Jugadores WHERE usuario='%s'", nombre);
			err = mysql_query(conn, query);
			
			if (err != 0) {
				printf("Error al consultar la base de datos: %s\n", mysql_error(conn));
				sprintf(respuesta, "1/Error en la base de datos");
			} else {
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				
				if (row == NULL) {
					sprintf(respuesta, "1/El usuario no existe");
				} else if (strcmp(row[0], password) == 0) {
					sprintf(respuesta, "1/Inicio de sesión correcto");
					strcpy(usuario_logueado, nombre);
					session_iniciada = 1;
					
					pthread_mutex_lock(&mutex);
					if (PonConectado(&miLista, nombre, sock_conn) == -1) {
						printf("La lista de conectados está llena\n");
					} else {
						printf("El cliente %s se ha añadido a la lista de conectados\n", nombre);
					}
					pthread_mutex_unlock(&mutex);
				} else {
					sprintf(respuesta, "1/Contraseña incorrecta");
				}
				mysql_free_result(res);
			}
		}
		
		if (codigo != 0) {
			printf("Respuesta: %s\n", respuesta);
			write(sock_conn, respuesta, strlen(respuesta));
		}
		
		if (codigo == 0 || codigo == 1) {
			pthread_mutex_lock(&mutex);
			contador++;
			pthread_mutex_unlock(&mutex);
			
			char notificacion[20];
			DameConectados(&miLista, conectados);
			sprintf(notificacion, "6/%s", conectados);
			
			for (int j = 0; j < i; j++) {
				write(sockets[j], notificacion, strlen(notificacion));
			}
		}
	}
	
	if (session_iniciada) {
		pthread_mutex_lock(&mutex);
		if (EliminaConectado(&miLista, usuario_logueado) == -1) {
			printf("No se encontró al cliente %s en la lista de conectados\n", usuario_logueado);
		} else {
			printf("El cliente %s ha sido eliminado de la lista de conectados\n", usuario_logueado);
		}
		pthread_mutex_unlock(&mutex);
	}
	
	mysql_close(conn);
	close(sock_conn);
	return NULL;
}

int main(int argc, char *argv[]) {
	int sock_conn, sock_listen;
	struct sockaddr_in serv_adr;
	
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Error creando socket\n");
		return 1;
	}
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(50003);
	
	if (bind(sock_listen, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) < 0) {
		printf("Error en el bind\n");
		return 1;
	}
	
	if (listen(sock_listen, 4) < 0) {
		printf("Error en el listen\n");
		return 1;
	}
	
	miLista.num = 0;
	
	pthread_t thread;
	while (1) {
		printf("Escuchando\n");
		sock_conn = accept(sock_listen, NULL, NULL);
		printf("Conexión recibida\n");
		
		sockets[i] = sock_conn;
		pthread_create(&thread, NULL, AtenderClientes, &sockets[i]);
		i++;
	}
	return 0;
}
