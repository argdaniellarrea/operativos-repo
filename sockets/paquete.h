/*
 * paquete.h
 *
 *  Created on: 01/05/2014
 *      Author: utnso
 */

#ifndef PAQUETE_H_
#define PAQUETE_H_

typedef struct
{
	void* (*add_element_function) (void*, void*);
	void* (*remove_element_function) (void*);
	void* (*instantiate_list_function) (void);
	void (*destroy_and_clean_list) (void*);
	void (*element_destroyer) (void*);
	void (*list_is_empty) (void*);
	void (*remove_first) (void*); // por si las moscas
	void (*size_of_list) (void*);
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
