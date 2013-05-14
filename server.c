#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "header.h"

#define PORT_TFTP 69 //Port TFTP 69

int main(int argc, char *argv[]){

	int port = PORT_TFTP; //Définition fixe du port
	int sockfd,  n;
	struct sockaddr_in *serv_addr = malloc(sizeof(struct sockaddr_in));	
	char *buffer = calloc(sizeof(char), 512); //Buffer de dialogue de taille 512
	char *read_buffer = calloc(sizeof(char), 512);
	char *write_buffer = calloc(sizeof(char), 516); 
	
	//Initialisation des paramètres du serveur
	serv_addr->sin_family = PF_INET;
	serv_addr->sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr->sin_port = htons(port);

	//Ouverture de la socket de dialogue du serveur
	if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
		perror("Socket error ");
		exit(1);
	}

	//Ouverture du port d'écoute
	if(bind(sockfd, (struct sockaddr *) serv_addr, sizeof(*serv_addr)) < 0){
		perror("Bind error ");
		exit(1);
	}

	//Boucle d'écoute de clients, le serveur est monoclient
	while(1){
		request_connexion *data_co = malloc(sizeof(request_connexion)); //Structure des informations de connexions
		recv_data(sockfd, buffer, 511, 0, serv_addr); //Attente des informations de connexion du client

		read_data_connexion(data_co, buffer); //Lecture des informations reçues du client dans data_co
		printf("A client is now connected\n");

		if(data_co->type == 1){ //RRQ operation
			FILE *file = fopen(data_co->filename, "r");
			int size;
			short ACK_cpt = 0;

			while((size = fread(read_buffer, sizeof(char), 512, file)) != 0){
				read_buffer[size] = '\0';
				send_data_with_ACK(read_buffer, ACK_cpt, sockfd, serv_addr);
				while(wait_ACK(ACK_cpt, sockfd, serv_addr) != 0){
					send_data_with_ACK(read_buffer, ACK_cpt, sockfd, serv_addr);
				}
				ACK_cpt++;
			}
			fclose(file);
		}else if(data_co->type == 2){ //WRQ operation
			send_ACK(0, sockfd, serv_addr);
			FILE *write_file = fopen(data_co->filename, "w");
			fclose(write_file);
			while(1){
				FILE *write_file = fopen(data_co->filename, "a");
				read_data_with_ACK(write_buffer, sockfd, serv_addr);
				//printf("%d\n%s\n", strlen(write_buffer), write_buffer);
				if(strlen(write_buffer) == 511){
					//fprintf(write_file, "%s", write_buffer);
					fwrite(write_buffer, sizeof(char), strlen(write_buffer), write_file);
				}else{
					//fprintf(write_file, "%s", write_buffer);
					fwrite(write_buffer, sizeof(char), strlen(write_buffer), write_file);
				}
				fclose(write_file);
			}
		}else{
			printf("Client error\n"); //On peut ajouter un message urgent à envoyer au client pour signaler l'éventuelle erreur
		}
		free(data_co);
	}
	close(sockfd);
	free(serv_addr);
	free(buffer);
	free(write_buffer);
	return 0;
}
