#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "header.h"

#define PORT_TFTP 69

int main(int argc, char *argv[]){

	int port = PORT_TFTP;
	int sockfd,  n;
	struct sockaddr_in *serv_addr = malloc(sizeof(struct sockaddr_in));	
	char *buffer = calloc(sizeof(char), 512);
	request_connexion *data_co = malloc(sizeof(request_connexion));

	serv_addr->sin_family = PF_INET;
	serv_addr->sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr->sin_port = htons(port);

	if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
		perror("Socket error ");
		exit(1);
	}

	if(bind(sockfd, (struct sockaddr *) serv_addr, sizeof(*serv_addr)) < 0){
		perror("Bind error ");
		exit(1);
	}


	while(1){
		//send_data(sockfd, buffer, sizeof(buffer)-1, 0, (struct sockaddr *) &serv_addr, &len);	

		recv_data(sockfd, buffer, sizeof(*buffer)-1, 0, serv_addr);

		read_data_connexion(data_co, buffer);
		printf("A client is now connected\n");

		/*char *welcome = (char *) "Welcome on the TFTP server. You can read (RRQ) or write (WRQ) a file on this server. What do you do ? [RRQ/WRQ]";
		if((n = sendto(sockfd, welcome, strlen(welcome), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) < 0){
			perror("Sendto error : ");
			exit(1);
		}


		if((n = recvfrom(sockfd, buffer, sizeof(buffer)-1, 0, (struct sockaddr *) &serv_addr, &len)) < 0){
			perror("Recv error : ");
			exit(1);
		}

		buffer[n] = '\0'; 
		char *filename_msg = calloc(sizeof(char),255);
		if(strcmp(buffer, "RRQ\0") == 0){
			sprintf(filename_msg, "You want to read a file. Give filename :");
			if((n = sendto(sockfd, filename_msg, strlen(filename_msg), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) < 0){
				perror("Sendto error : ");
				exit(1);
			}

			
			if((n = recvfrom(sockfd, buffer, sizeof(buffer)-1, 0, (struct sockaddr *) &serv_addr, &len)) < 0){
				perror("Recv error : ");
				exit(1);
			}
			buffer[n] = '\0';

			char *path = calloc(sizeof(char), 255);
			strcpy(path, (const char*) buffer);
			FILE *read_file = fopen(path, "r");
			char *read_buffer = calloc(sizeof(char), 512);
			int size, ack_cpt = 0;


			while((size = fread(read_buffer, sizeof(char), 512, read_file)) != 0){
				if((size_t) 512 == size){
					ack_cpt++;
					if((n = sendto(sockfd, read_buffer, strlen(read_buffer), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) < 0){
						perror("Sendto error : ");
						exit(1);
					}

					if((n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &serv_addr, &len)) < 0){
						perror("Recv error : ");
						exit(1);
					}
					buffer[n] = '\0';
					if(atoi(buffer) == ack_cpt){
						continue;
					}else{
						printf("ACK error n°%d\n", ack_cpt);
					}
				}else{
					
				}
			}		

			fclose(read_file);
		}else if(strcmp(buffer, "WRQ\0") == 0){
			sprintf(filename_msg, "You want to write a file. Give filename :");
			if((n = sendto(sockfd, filename_msg, strlen(filename_msg), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) < 0){
				perror("Sendto error : ");
				exit(1);
			}
		}else{
			char *error_msg = calloc(sizeof(char), 255);
			sprintf(error_msg, "%s is not possible yet. Try to reconnect.", buffer);
			if((n = sendto(sockfd, error_msg, strlen(error_msg), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) < 0){
				perror("Sendto error : ");
				exit(1);
			}
		}
	}*/
	}
	close(sockfd);
}
