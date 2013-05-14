typedef struct request_connexion request_connexion;
	struct request_connexion{
		short type;
		char filename[255];
		char mode[6];
	};

int start_connexion(char *, char *, char *, int, struct sockaddr_in *);

int send_data(int, const void *, struct sockaddr_in *);
char *recv_data(int, char *, size_t, int, struct sockaddr_in *);

int read_data_connexion(request_connexion *, char *);
int send_data_with_ACK(char *, short, int, struct sockaddr_in *);
int read_data_with_ACK(char *, int, struct sockaddr_in *);
int wait_ACK(short, int, struct sockaddr_in *);
int send_ACK(short, int, struct sockaddr_in *);
