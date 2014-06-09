/*
 * servidor.c
 *
 *  Created on: 04/06/2014
 *      Author: utnso
 */

#include "servidor.h"
#define	ARRAY_DE_INTS 5
#define	RECIBIS_UN_STRING 1
#define	RECIBIS_UN_ALUMNO 2
#define ARRAY_DE_ALUMNOS 3
#define INT 4


int main()
{
	basic_functions basics;
	basics.list_is_empty= (void*)list_is_empty;
	basics.size_of_list = (void*)list_size;
	basics.add_element_function= (void*) list_add;
	basics.instantiate_list_function = (void*) list_create;
	basics.remove_element = (void*) list_remove;
	basics.get_element_function = (void*) list_get;

	setListFunctions(basics);

	int socketEscucha = crear_socket_escucha("5000");
	printf("Socket %d creado \n", socketEscucha);
	printf("esperando a un proceso \n");
	int socket= aceptar(socketEscucha);
	printf("se conecto el socket %d \n", socket);
	while(1)
	{
		t_list* listaDePaquetes = recibir(socket);
		printf("llegaron nuevos paquetes \n");
		ejecutarPaquetes(listaDePaquetes);
		list_destroy(listaDePaquetes);
		sleep(5);
	}

	close(socket);

	return 0;
}

void ejecutarPaquetes(t_list* listaDePaquetes)
{
	while(!list_is_empty(listaDePaquetes))
	{
		printf("ejecutando paquetes\n");

		t_paquete* unPaquete = list_remove(listaDePaquetes,0);
		switch(unPaquete->codOp)
		{
			case ARRAY_DE_INTS:
			{
				int a=0;
				int16_t * b= (int16_t*)unPaquete->datos;
				printf("El array de ints contiene:\n");
				while(a< unPaquete->tamanioDatos/ sizeof(int16_t))
				{
					printf("%d\n", b[a]);
					a++;
				}
				break;
			}
			case INT:
			{
				printf("recibi %d", (int)*unPaquete->datos);
				break;
			}
			default:
			{
				break;
			}
		}
		free(unPaquete->datos);
		free(unPaquete);
	}
}
