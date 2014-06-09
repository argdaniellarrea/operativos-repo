/*
 * cliente.c
 *
 *  Created on: 05/06/2014
 *      Author: utnso
 */

#include "cliente.h"

#define	ARRAY_DE_INTS 5
#define	RECIBIS_UN_STRING 1
#define	RECIBIS_UN_ALUMNO 2
#define ARRAY_DE_ALUMNOS 3
#define INT 4


int main()
{
	int socket = conectar("127.0.0.1", "5000");
	int16_t a[256];
	for(int b= 0; b <10; b++)
	{
		a[b]=b;
	}

	while(1)
	{
		printf("%d\n", sizeof(a));
		char b[1];
		scanf("%s",b);
		enviar(ARRAY_DE_INTS, 252, (char*)a, socket);

	}

	return 0;
}
