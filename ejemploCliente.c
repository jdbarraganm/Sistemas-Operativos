#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(void) {
	struct sockaddr_in direccionServidor;
	direccionServidor.sin_family = AF_INET;
	direccionServidor.sin_addr.s_addr = inet_addr("127.0.0.1");
	direccionServidor.sin_port = htons(8080);

	int cliente = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(cliente, (void*) &direccionServidor, sizeof(direccionServidor)) != 0) {
		perror("No se pudo conectar");
		return 1;
	}
	
	char* buffer = malloc(1000);
	int a=0;
	while (a!=-1) {
		
		printf("Ingrese 1 para enviar un mensaje /n");
		printf("Ingrese 2 para recibir un mensaje /n");
		scanf("%i",&a);
		
		if(a==1){
		
		char mensaje[1000];
		scanf("%s", mensaje);

		send(cliente, mensaje, strlen(mensaje), 0);
		}else{
		if(a==2) {
		int bytesRecibidos = recv(cliente, buffer, 1000, 0);
		if (bytesRecibidos <= 0) {
			perror("El chabón se desconectó o bla.");
			return 1;
		}
		buffer[bytesRecibidos] = '\0';
		printf("Me llegaron %d bytes con %s\n desde el servidor", bytesRecibidos, buffer);
		}

		}

	}

	return 0;
}
