#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(void) {
	struct sockaddr_in direccionServidor;
	direccionServidor.sin_family = AF_INET;
	direccionServidor.sin_addr.s_addr = INADDR_ANY;
	direccionServidor.sin_port = htons(8080);

	int servidor = socket(AF_INET, SOCK_STREAM, 0);

	int activado = 1;
	setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR, &activado, sizeof(activado));

	if (bind(servidor, (void*) &direccionServidor, sizeof(direccionServidor)) != 0) {
		perror("Falló el bind");
		return 1;
	}

	printf("Estoy escuchando\n");
	listen(servidor, 100);

	//------------------------------

	struct sockaddr_in direccionCliente;
	unsigned int tamaDireccion;
	int cliente = accept(servidor, (void*) &direccionCliente, &tamaDireccion);

	printf("Recibí una conexión en %d!!\n", cliente);
	/*send(cliente, "Hola NetCat!", 13, 0);
	  send(cliente, ":)\n", 4, 0);
	*/

	//------------------------------

	char* buffer = malloc(1000);

	int a=0;
	while (a!=-1) {
		
		printf("Ingrese 1 para enviar un mensaje /n");
		printf("Ingrese 2 para recibir un mensaje /n");
		scanf("%i",&a);
		
		if(a==1){
		
		char mensaje[1000];
		scanf("%s", mensaje);

		send(cliente,mensaje, strlen(mensaje), 0);

		}else{
		if(a==2) {
		int bytesRecibidos = recv(cliente, buffer, 1000, 0);
		if (bytesRecibidos <= 0) {
			perror("El chabón se desconectó o bla.");
			return 1;
		}

		buffer[bytesRecibidos] = '\0';
		printf("Me llegaron %d bytes con %s\n", bytesRecibidos, buffer);

		}
	}
	}

	free(buffer);

	return 0;
}
