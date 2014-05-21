/*

 * paquete.c

 *
 *  Created on: 01/05/2014
 *      Author: utnso
 */
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "paquete.h"

#define size_header  sizeof(uint16_t) * 2


basic_functions basic;

void setListPacketFunctions(basic_functions someBasic)
{
	basic = someBasic;
}

char* acoplador(t_paquete* paquete) /*transforma una estructura de tipo t_paquete en un stream*/
{
	char* paqueteSalida =  (char*)malloc(size_header + paquete->tamanioDatos);
	if(paqueteSalida)
	{
		memcpy(paqueteSalida, paquete, size_header);
		memcpy(paqueteSalida + size_header, paquete->datos, paquete->tamanioDatos);
	}
	return paqueteSalida;
}

int desacoplador(char* buffer,int sizeBuffer, void* packetList)/*transforma multiples streams en estructuras de t_paquete y los agrega a una lista*/
{
	int desacoplado = 0;
	t_paquete* paquete;
	while (sizeBuffer!= desacoplado)
	{//todo: ojo con malloc, analizar como funciona sobrecarga de buffer

		if((sizeBuffer - desacoplado)>= size_header)
		{
			paquete= malloc(sizeof(t_paquete));
			paquete->codOp= (uint16_t)*(buffer + desacoplado);
			paquete->tamanioDatos= (uint16_t)* (buffer + sizeof(uint16_t) + desacoplado);
			if(sizeBuffer- desacoplado - size_header > paquete->tamanioDatos)
			{
				paquete->datos= malloc(paquete->tamanioDatos);
				memcpy(paquete->datos, buffer + desacoplado + size_header, paquete->tamanioDatos);
				basic.add_element_function(packetList, (void*)paquete);
				desacoplado += (size_header + paquete->tamanioDatos);
			}
			else
			{
				free(paquete);
				return desacoplado;
			}
		}
		else
		{
			return desacoplado;
		}
	}
	return 0;
}

int tamanioDePaquete(t_paquete unPaquete)
{
	return unPaquete.tamanioDatos + size_header;
}

t_paquete armarPaquete(int codOp, int tamanioDatos, char* datos)
{
	t_paquete unPaquete;
	unPaquete.codOp = codOp;
	unPaquete.tamanioDatos = tamanioDatos;
	unPaquete.datos = datos;
	return unPaquete;
}



/* armado de paquete manual
t_paquete unPaquete;
unPaquete.codOp= 5;
unPaquete.tamaño= sizeof(unReg);
unPaquete.datos = &unReg
*/

/* derivando en una funcion
 * armar(5,sizeof(unReg),&unReg)
 */

/* enviar
 * enviar(5,sizeof(unReg),&unReg, socket)
 */
