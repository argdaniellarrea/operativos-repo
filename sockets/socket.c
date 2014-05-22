#include "socket.h"//Esto va entre comillas porque está en la misma carpeta que el .c (o algo así)
/*funciones de lectura/escritura sockets*/

#define size_header  sizeof(uint16_t) * 2

/* funcion lectura: lee datos del socket, se le pasa un buffer con hueco suficiente para datos
 * devuelve el numero de bytes leidos, 0 si cierra el archivo; -1 si hay error
 */
int Lee_Socket_deprecated (int fd, char*Datos, int Longitud)
{
	int Leido = 0;
	int Aux = 0;
	char buffer[256];

	/* comprueba qe los parametros sean correctos */

	if ((fd == -1)||(Datos == NULL)||(Longitud <1))
	{
		return -1;
	}

	while (Leido < Longitud)
	{
		Aux =recv(fd,buffer, sizeof(buffer),0); //DANI: recomiendo usar un recv
		if (Aux>0)
		{
			Leido= Leido + Aux;
			/* si puede leer datos, incrementa la variable de datos leidos hasta el momento*/
		}
		else
		{
			if (Aux == 0)
				return Leido;
			/* si read devuelve 0 es porqe se ha cerrado el socket y devolvemos giladas leidas hasta el momento */
			//Dani: comento algo, vos lees una única vez, y te pasa TODO lo que recibio, ojo con eso, lo ideal es cerrar el socket

			if (Aux ==-1)
			{
				switch (errno)
				{
				case EINTR:
				case EAGAIN:
					usleep (100);
					break;
				default:
					return -1;

			/* en caso de error, errno nos indica el tipo de error;
			 * EINTR = se produce si hubo alguna interrupcion del sistema antes de leer
			 * ccqq dato
			 * EAGAIN = significa qe el socket no ta disponible y qe lo volvamos a intentar
			 * se espera 100 microsegundos y se vuelve a intentar
			 * el resto de posibles errores provoca que salgamos de la funcion con error
			 */
				}
			}
		}
	}
	/* se devuelve el total de caracteres leidos
	 * DANI: retorna la cantidad de bytes leidos
	 */
	return Leido;//todo: retornar listas
}
/*la papa a hacer, si no me equivoco, y me funciono es:
 * Leer una vez
 * si hubo error (ergo el retorno es <= 0)solucionarlo
 * si no hubo error: devolver la cantidad de bytes leidos
 * PD: LO MEJOR, es definir un protocolo: ergo, decir "los primeros 2 bytes de los paquetes son un
 * uint16_t que definen el tipo de paquete, los segundos 2 bytes son otro uint16_t que define el tamaño
 * (yo hice eso por si recibo MAS de un paquete a la vez)" y lo restante es el dato en sí.
 */

/* funcion escritura : escribe datos en el socket cliente.
 Devuelve nro de bytes escritos o -1 si hay error*/

basic_functions basic;

void setListFunctions(basic_functions someBasic)
{
	basic = someBasic;
	setListPacketFunctions(someBasic);
	if (test())
	{
		perror("Error en el test de las funciones de listas");
	}
}

int test()
{
	printf("Inicializando lista \n");
	void* aList = basic.instantiate_list_function();

	if(!basic.list_is_empty(aList))
	{
		printf("Error, se esperaba que la lista este vacia\n");
		return 1;
	}

	printf("Creando paquete\n");
	char a= 'a';
	t_paquete unPaquete = armarPaquete(1,sizeof(char),&a);

	printf("Agregando paquete a la lista \n");
	basic.add_element_function(&unPaquete, aList);

	if(basic.list_is_empty(aList))
	{
		printf("Error al agregar elemento \n");
		return 1;
	}

	printf("Removiendo el primer elemento de la lista\n");
	unPaquete = *(t_paquete*)basic.remove_first(aList);
	if(!basic.list_is_empty(aList))
	{
		printf("Se esperaba que la lista este vacia \n");
		return 1;
	}
	else if(*unPaquete.datos != 'a' )
	{
		printf("Error de integridad de datos, el paquet eno es el mismo\n");
		return 1;
	}

	if(basic.size_of_list(aList)!=0)
	{
		printf("Error en el calculo del tamanio de la lista \n");
		return 1;
	}
	//TODO: agregar multiples elementos y removerlos todos

	return 0;
}


int Escribe_Socket_deprecated (int fd, char* Datos, int Longitud)
{
	int Escrito = 0;
	int Aux = 0;

	if ((fd == -1)|| (Datos == NULL) || (Longitud < -1))
		return -1;
	while (Escrito < Longitud)
	/* leemos hasta escribir todos los caracteres qe nos indicaron */
	{
		Aux = write (fd, Datos + Escrito, Longitud - Escrito); //DANI: recominedo usar send
		if (Aux > 0)
		{
			Escrito = Escrito + Aux;
		}
		else
		{
			if (Aux == 0)
				return Escrito;
			else
				return -1;
		}
	}

	return Escrito;
	/* devuelve el total de caracteres escritos*/
}

void* recibir(int fd)
{
	void * packetList = basic.instantiate_list_function();
	char* buffer = malloc (sizeof(char)*256);
	char* bufferPivot = buffer;
	int a= recv(fd,buffer, sizeof(buffer),0);
	//analizar que paso con el recv
	if(a>0)
	{
		//todo: sobrecarga de buffer
		int errorNumber= desacoplador(bufferPivot, a, packetList);
		while(errorNumber != 0&& a >0)
		{
			char* aux= bufferPivot;
			bufferPivot = malloc(sizeof(char)*256 + errno);
			memcpy(bufferPivot, aux+ errno, sizeof(aux)- errno);
			a = recv(fd, bufferPivot + (sizeof(aux)- errno), sizeof(bufferPivot) - (sizeof(aux)- errno),0 );
			errorNumber = desacoplador(bufferPivot, a,packetList);
			free(aux);
		}
	}

	if(a==0)
	{
	//	destruir(packetList);//TODO
		return NULL; //el proceso que use esto, deberia tomar las acciones necesarias para desconectarse del otro proceso (avisar, limpiar listas, etc)

	}
	else
	{
		//error
		return (void*)1;
	}
	return packetList;

}

int enviar(int codOp, int tamanioDatos, char* datos, int fd )
{
	t_paquete paqueteAEnviar = armarPaquete(codOp, tamanioDatos, datos);
	char* bloque = acoplador(&paqueteAEnviar);
	int a = send(fd, bloque,tamanioDePaquete(paqueteAEnviar),0);
	free(bloque);

	return a;
}

int conectar(char* direccion, char* puerto){

	struct sockaddr_in socketStruct;
	socketStruct.sin_family = AF_INET;
	socketStruct.sin_addr.s_addr = inet_addr(direccion);
	socketStruct.sin_port = htons(atoi(puerto));
	memset(&(socketStruct.sin_zero), '\0', 8);

	int socketEmisor;
	// Crear un socket:
	// AF_INET: Socket de internet IPv4
	// SOCK_STREAM: Orientado a la conexion, TCP
	// 0: Usar protocolo por deft_paqueteecto para AF_INET-SOCK_STREAM: Protocolo TCP/IPv4
		if ((socketEmisor = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			perror("Error al crear socket");
			return EXIT_FAILURE;//todo modificar errores
		}
		// Conectar el socket con la direccion 'socketInfo'.
		if (connect(socketEmisor, (struct sockaddr*) &socketStruct, sizeof(socketStruct))	!= 0) {
			perror("Error al conectar socket");//todo modificar errores
			return EXIT_FAILURE;
		}
		return socketEmisor;/*tiene que devolver una estr*/
}

int crear_socket_escucha(char* direccion, char* puerto)
{
	int socketEscucha;
	struct sockaddr_in socketInfo;
	int optval = 1;

	if ((socketEscucha = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		return EXIT_FAILURE;
	}

	setsockopt(socketEscucha, SOL_SOCKET, SO_REUSEADDR, &optval,sizeof(optval));

	socketInfo.sin_family = AF_INET;
	socketInfo.sin_addr.s_addr = INADDR_ANY;
	socketInfo.sin_port = htons(atoi(puerto));


	//  fijarse si hay que poner lo de memset(); PARA QUE: sockaddr_in SEA COMPATIBLE CON sockaddr
	memset(&(socketInfo.sin_zero), '\0', 8); //poner a cero el resto de la estructura

	if (bind(socketEscucha, (struct sockaddr*) &socketInfo, sizeof(socketInfo)) != 0) {

		perror("Error al bindear socket escucha\n");
		return EXIT_FAILURE;
	}

	if (listen(socketEscucha, 100) != 0) {

		perror("Error al poner a escuchar socket\n");
		return EXIT_FAILURE;

	}

	return socketEscucha;
}
