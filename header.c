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
#include     <string.h>

#include "header.h"

int start_connexion(char *access_type, char *filename, char *mode, int sockfd, struct sockaddr_in *serv_addr){
	char *connexion_msg = calloc(sizeof(char), 264);
	int end = 0;
	short type = 0;
	
	if(strcmp(access_type, "WRQ") == 0) type++; type++;

	strcpy(connexion_msg, "");
	sprintf(connexion_msg,  "%s%d", connexion_msg, type);
	strcat(connexion_msg, filename);
	sprintf(connexion_msg, "%s%d", connexion_msg, end);
	strcat(connexion_msg, mode);

	send_data(sockfd, connexion_msg, serv_addr);
	
	return 0;
	free(connexion_msg);
}

int send_data(int sockfd, const void *buffer, struct sockaddr_in *serv_addr){
	int n;
	if(( n = sendto(sockfd, (char *) buffer, strlen(buffer)+1, 0, (struct sockaddr *) serv_addr, (socklen_t) sizeof(*serv_addr))) < 0 ){
		perror("Sendto error ");
		exit(1);
	}
}

char *recv_data(int sockfd, char *buffer, size_t len, int flags, struct sockaddr_in *serv_addr){
	int n;	
	socklen_t len_addr = sizeof(*serv_addr);

	if((n = recvfrom(sockfd, buffer, len, 0, (struct sockaddr *) serv_addr, &len_addr)) < 0){
		perror("Recv error ");
		exit(1);
	}
	buffer[n] = '\0';

}

int read_data_connexion(request_connexion *data_co, char *buffer){
	int end_index = strrchr(buffer, '0') - buffer;	
	
	data_co->type = ((char) buffer[0])-'0';
	strcpy(data_co->mode, buffer+end_index+1);
	buffer[strlen(buffer)-6] = '\0';
	strcpy(data_co->filename, buffer+1);
}

int send_data_with_ACK(char *buffer, short num_ACK, int sockfd, struct sockaddr_in *serv_addr){
	char *real_data = calloc(sizeof(char), 516);
	sprintf(real_data, "%2d%2d%s", 3, num_ACK, buffer);
	send_data(sockfd, real_data, serv_addr);

	return 0;
	free(real_data);
}

int wait_ACK(short num_ACK_waited, int sockfd, struct sockaddr_in *serv_addr){
	char *num_ACK_received = calloc(sizeof(char), 3);
	recv_data(sockfd, num_ACK_received, 2, 0, serv_addr);

	if(atoi(num_ACK_received) == num_ACK_waited){
		printf("Youpi\n");
		return 0;
		free(num_ACK_received);
	}else{
		return 1;
		free(num_ACK_received);
	}
}

int read_data_with_ACK(char *buffer, int sockfd, struct sockaddr_in *serv_addr){
	char *num_ACK_s = calloc(sizeof(char), 3);
	strcpy(buffer, "");
	recv_data(sockfd, buffer, 515, 0, serv_addr);
	strncpy(num_ACK_s, buffer+2, 2);
	num_ACK_s[2] = '\0';
	send_ACK(atoi(num_ACK_s), sockfd, serv_addr);
	strcpy(buffer, buffer + 4);

	free(num_ACK_s);
	return 0;
}

int send_ACK(short num_ACK, int sockfd, struct sockaddr_in *serv_addr){
	char *num_ACK_s = calloc(sizeof(char), 3);
	sprintf(num_ACK_s, "%d", num_ACK);	
	send_data(sockfd, num_ACK_s, serv_addr);
	
	return 0;
	free(num_ACK_s);
}
