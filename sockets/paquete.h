/*
 * paquete.h
 *
 *  Created on: 01/05/2014
 *      Author: utnso
 */

#ifndef PAQUETE_H_
#define PAQUETE_H_

#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
	void* (*add_element_function) (void*, void*); 	//tested
	void* (*get_element_function) (void*,int);		//notTested
	void* (*instantiate_list_function) (void);		//tested
	void (*destroy_and_clean_list) (void*);			//notTested
	void (*element_destroyer) (void*);				//notTested
	bool (*list_is_empty) (void*);					//tested
	void* (*remove_element) (void*, int);			//tested
	int (*size_of_list) (void*);					//tested
}basic_functions;

typedef struct
{
	uint16_t codOp;
	uint16_t tamanioDatos;
	char* datos;//todo rellenar con algo mas

} __attribute__((__packed__)) t_paquete ;

int desacoplador(char* buffer,int sizeBuffer, void* packetList);
char* acoplador(t_paquete* packet);
int tamanioDePaquete(t_paquete packet);
t_paquete armarPaquete(int codOp, int tamanioDatos, char* datos);
void setListPacketFunctions(basic_functions someBasic);

#endif /* PAQUETE_H_ */
