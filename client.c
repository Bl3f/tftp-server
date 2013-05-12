#include     <stdio.h>
#include     <sys/types.h>
#include     <sys/socket.h>
#include     <netinet/in.h>
#include     <sys/un.h>
#include     <arpa/inet.h>
#include     <sys/uio.h>
#include     <time.h>
#include     <sys/timeb.h>
#include     <netdb.h>
#include     <stdlib.h>
#include     <strings.h>

#include     "header.h"

#define PORT_TFTP 69

int main(int argc, char *argv[]){

	if(argc != 5){
		printf("Bad usage of the function : <exec> <server address> <operation code> <filename> <mode>\n");
		exit(1);
	}

	if(strcmp(argv[4], "octet") != 0){
		printf("%s mode is not implemented yet\n", argv[4]);
		exit(1);
	}

	if(strcmp(argv[2], "RRQ") != 0 && strcmp(argv[2], "WRQ") != 0){
		printf("%s operation is not implemented yet\n", argv[2]);
		exit(1);
	}

	int sockfd, n;
	struct sockaddr_in *serv_addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
	char buffer[1500];
	socklen_t len = sizeof(serv_addr);	

//	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	serv_addr->sin_family = PF_INET;
	serv_addr->sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr->sin_port = htons(PORT_TFTP);

	if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
		perror("Socket error : ");
		exit(1);
	}

	start_connexion(argv[2], argv[3], argv[4], sockfd, serv_addr);

	return;
	/*
	if((n = sendto(sockfd, filename, strlen(filename), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) != strlen(filename)){
		perror("Sendto error : ");
		exit(1);
	}

	if(strcmp(mode,"RRQ\0") == 0){
		char write_buffer[512] = "";
		int ack_cpt = 0;		

		while(1){
			FILE *write_file = fopen(filename, "a+");
			if((n = recvfrom(sockfd, write_buffer, sizeof(write_buffer)-1, 0, (struct sockaddr *) &serv_addr, &len)) < 0){
				perror("Recv error : ");
				exit(1);
			}
			write_buffer[n] = '\0';
		
			fprintf(write_file, "%s", write_buffer);
			ack_cpt++;
			
			sprintf(buffer, "%d\0", ack_cpt);

			if((n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) < 0){
				perror("Sendto error : ");
				exit(1);
			}
			fclose(write_file);
		}
		
	}
	
	close(sockfd);*/
	return 0;
}
