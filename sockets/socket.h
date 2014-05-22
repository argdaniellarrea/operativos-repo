/*
 * Socket.h
 *
 *  Created on: 27/04/2014
 *      Author: utnso
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <inttypes.h>
#include <stdbool.h>
#include <sys/unistd.h>
#include "paquete.h"



// Poner los prototipos de las funciones aca, me permite que otro proyecto las use:
int Lee_Socket (int fd, char*Datos, int Longitud);
int Escribe_Socket (int fd, char* Datos, int Longitud);
void* recibir(int fd);
int enviar(int codOp, int tamanioDatos, char* datos, int fd );
int conectar(char* direccion, char* puerto);
int crear_socket_escucha(char* direccion, char* puerto);
int test();

#endif /* SOCKET_H_ */
