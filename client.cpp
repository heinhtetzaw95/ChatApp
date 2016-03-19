#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <pthread.h>

using namespace std;

struct connection{
	int theSocket;
	char reply[512];
	char  buffer[512];
	bool working;
};


void *sendtoserver(void* input){
	struct connection *client = (connection*) input;

//	while (true){
		if (cin.getline(client->buffer, 512)){
	//		cout << client->buffer << endl;
			send (client->theSocket, client->buffer, sizeof(client->buffer), 0); 
			cout << "Send!" << endl;
					//clear the buffer after sending
			strcpy(client->buffer, "");
			}
//		}
//			pthread_exit(NULL);
			return 0;	
/*		recv(client->theSocket, client->reply, 512, 0);

	
		if (strcmp(client->reply, "exit==true") == 0){
			close(client->theSocket);
			cout << "Connection Terminated!" << endl;
			client->working = false;
			
			return 0;
		}

		else {
			cout << client->reply;
		}*/
//	}
}


void *recievefromserver(void* input){
	struct connection *client = (connection*) input;
//	int count = 0;
//	while (true){
//		recv(client->theSocket, client->reply, 512, 0);

		if (strcmp(client->reply, "exit==true") == 0){
			close(client->theSocket);
			cout << "Connection Terminated!" << endl;
			client->working = false;
			
			return 0;
		}

		else cout << client->reply;
//		cout << count << endl;
//		count++;
//		pthread_exit(NULL);
//		return 0;
		//cout << client->reply;
///	}
}


int main(int argc, char* argv[]){
	struct sockaddr_in socketInfo;
	char address[20];
	struct hostent *theHost;
//	int theSocket;
	int port;
	char *serverAddress = &address[0];
	connection theClient;

//	if (argc < 3){
//		cout << "Syntax Error!\nSyntax: <AppName> <ServerAddress> <PortNumber>" << endl;
//		return 0;
//	}

//	strcpy(address, argv[1]);
	strcpy(address, "localhost");							//temporary
	cout << "Server address: " << address[0] << endl;

//	port = atoi(argv[2]);
	port = 1500;
	cout << "Port: " << port << endl;						//temporary ends

	bzero (&socketInfo, sizeof(sockaddr_in));

		//get system info
	theHost = gethostbyname(serverAddress);
	cout << theHost << " at IP: " << serverAddress << endl;
	if (theHost == NULL){
		perror ("Host error");
		return -1;
	}
	else cout << "Host OK!" << endl;

		//create socket
	theClient.theSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (theClient.theSocket < 0){
		perror ("Socket error");
		close (theClient.theSocket);
		return -1;
	}
	else cout << "Socket OK!" << endl;

		//load system info to socket
	memcpy((char *) &socketInfo.sin_addr, theHost->h_addr, theHost->h_length);
	socketInfo.sin_family = AF_INET;
	socketInfo.sin_port = htons((ushort)port);

	if(connect(theClient.theSocket, (struct sockaddr *) &socketInfo, sizeof (sockaddr_in))<0){
		perror ("Connection error");
		close (theClient.theSocket);
		return -1;
	}
	else {
		cout << "Connection established!" << endl;
		theClient.working = true;
	
	

	pthread_t sendThread, recieveThread;
	int thread1, thread2;

	while(theClient.working){
//		if (cin.getline(theClient.buffer, 512)){
//			send (theClient.theSocket, theClient.buffer, 512, 0); 
//			cout << "Send! String: " << theClient.buffer << endl;
//		}
//		cin.getline(theClient.buffer, 512);
		thread1 = pthread_create(&sendThread, NULL, &sendtoserver, &theClient);
	
	if (recv(theClient.theSocket, theClient.reply, 512, 0)){
		if (strcmp(theClient.reply, "exit==true") == 0){
			close(theClient.theSocket);
			cout << "Connection Terminated!" << endl;
			return 0;
		}

		else cout << theClient.reply;
	}
//		thread2 = pthread_create(&recieveThread, NULL, &recievefromserver, &theClient);

//	cout << thread1 << thread2 << endl;

}
	return 0;
	/**************************************************************
	while (true){
		cin.getline(theClient.buffer, 512);
		send (theClient.theSocket, theClient.buffer, sizeof(theClient.buffer), 0); 
		recv(theClient.theSocket, theClient.reply, 512, 0);

	
		if (strcmp(theClient.reply, "exit==true") == 0){
			close(theClient.theSocket);
			cout << "Connection Terminated!" << endl;
			return 0;
		}

		else cout << theClient.reply;
	}
	****************************************************************/
	}
	
}