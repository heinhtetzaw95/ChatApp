#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
//#include <thread>

#define max_size 512

using namespace std;

struct children{

	int connection;
	int receive;
	char buffer[max_size], reply[max_size], name[20];
	bool active;
};

void sendReply(children *child){
	send (child->connection, "Sample Reply!", sizeof("Sample Reply!"), 0);
}

void *ReadWrite(void* input){
	struct children *child;
	child = (children*) input;
//	for (;;){
		//cout << "Running " << child->name << endl;
//	}
	/*****************************************************************************************************************************
	bool loop = true;
				while (loop){
					strcpy(child[childCount].reply, "Simple Reply!\n");
					child[childCount].receive = recv(child[childCount].connection, child[childCount].buffer, 512, 0);

			//		cout << "Message: " << child[childCount].buffer << endl;
			//		return 0;
					
					if (strcmp(child[childCount].buffer, "leave-chat") == 0) {
						loop = false;
			//			cout << "Client left!" << endl;

						send (child[childCount].connection, "exit==true", sizeof("exit==true"), 0);
					}

					else send (child[childCount].connection, child[childCount].reply, sizeof(child[childCount].reply), 0);
				}
	********************************************************************************************************************************/
	bool loop = true;
				while (loop){
					strcpy(child->reply, "Simple Reply!\n\nYou: ");
					child->receive = recv(child->connection, child->buffer, max_size, 0);
				//	send (child->connection, child->reply, sizeof(child->reply), 0);
					
					cout << "Message: " << child->name << " says - " << child->buffer << endl;
			//		sendReply(child);

					
						for (int i=0; i<(rand()%10); i++){
						send (child->connection, "Push test!\n", max_size, 0);
						}

		//			return 0;
					
					if (strcmp(child->buffer, "--leave") == 0) {
						loop = false;
						cout << "\n" <<child->name << " has left!\n" << endl;
						send (child->connection, "sample 1\n", max_size, 0);
						send (child->connection, "sample 2\n", max_size, 0);
						send (child->connection, "sample 3\n", max_size, 0);
						send (child->connection, "sample 4\n", max_size, 0);
						send (child->connection, "sample 5\n", max_size, 0);

						send (child->connection, "exit==true", max_size, 0);
					}

					else send (child->connection, child->reply, max_size, 0);

				}			
	pthread_exit(NULL);
}

int main(){
	int theSocket, port;
	char hostname[256];
	struct sockaddr_in socketInfo;
	struct hostent *theHost;
	
	bzero (&theSocket, sizeof (sockaddr_in));

//	cout << "Port: ";
//	cin >> port;

	port = 1500;

	

		//get local address
	gethostname(hostname, 256);
	cout << hostname;

	if ((theHost = gethostbyname(hostname)) == NULL){
		cout << " Warning! System hostname is not correctly configured!" << endl;
//		return -1;
	}
	else cout << " (or) " << theHost << endl << "Host OK!" << endl;

		//create socket
	theSocket = socket (AF_INET, SOCK_STREAM, 0);
	
	if (theSocket < 0){
		close (theSocket);
		return -1;
	}
	else cout << "Socket OK!" << endl;

		//load system info into socket structure
	socketInfo.sin_family = AF_INET;
	socketInfo.sin_addr.s_addr = htonl (INADDR_ANY);
	socketInfo.sin_port = htons(port);
	
		//bind socket to local address
	if ((bind(theSocket, (struct sockaddr *) &socketInfo, sizeof (socketInfo))) < 0){
		close (theSocket);
		cerr << "Binding Error!" << endl << endl;
		return -1;
	}
	else cout << "Binding OK!" << endl;

	cout << "Listening at port " << port << " for client(s)...." << endl;

	listen (theSocket, 1);

//	int connection; 
//	int receive;
//	char buffer[512], reply[20];
	children child[10];
	strcpy(child[0].name, "Bob");
	strcpy(child[1].name, "Sam");
	strcpy(child[2].name, "Alice");
	strcpy(child[3].name, "Rick");
	strcpy(child[4].name, "Ryan");
	strcpy(child[5].name, "Hein");
	strcpy(child[6].name, "Josh");
	strcpy(child[7].name, "Clari");
	strcpy(child[8].name, "Wyane");
	strcpy(child[9].name, "Chris");

	int childCount = 0;

	pthread_t threads[11];
	int threadCount = 0;
	int rc[11] = {};

	for (;;){

		child[childCount].connection = accept (theSocket, NULL, NULL);
			if (child[childCount].connection < 0){
				return -1;
				//close(theSocket);
			}
			else {
				cout << "\n" << child[childCount].name << " Connected!\n" << endl;

				rc[childCount] = pthread_create(&threads[childCount], NULL, &ReadWrite, &child[childCount]);
				
				if (rc[childCount]) cout << "Cannot create thread, " << rc[childCount] << endl;
				

				send (child->connection, "You: ", max_size, 0);
						
				
//				thread threads[childCount](ReadWrite);
//				threads[childCount].join();

				
			/*************************************************************************************************************
				bool loop = true;
				while (loop){
					strcpy(child[childCount].reply, "Simple Reply!\n");
					child[childCount].receive = recv(child[childCount].connection, child[childCount].buffer, 512, 0);

			//		cout << "Message: " << child[childCount].buffer << endl;
			//		return 0;
					
					if (strcmp(child[childCount].buffer, "leave-chat") == 0) {
						loop = false;
			//			cout << "Client left!" << endl;

						send (child[childCount].connection, "exit==true", sizeof("exit==true"), 0);
					}

					else send (child[childCount].connection, child[childCount].reply, sizeof(child[childCount].reply), 0);
				}
			***************************************************************************************************************/
			}

			//close (child[childCount].connection);
			childCount++;
			cout << "Listening at port " << port << " for next client...." << endl;

			listen (theSocket, 1);
		}
	

	return 0;

}