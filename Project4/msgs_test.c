
//	Compile Command: gcc msgs_test.c
//
#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "msgs.h"

#define MAX_MESSAGE_LENGTH 10
#define MAX_PORT_NUMBER 100

void Server1()
{
	int MyPort = 11;
	int ServerID = 1;
	int ReceivePort;

	message* SendMessage = malloc(sizeof(struct message));
	message* ReceiveMessage;

	printf("Server %d Started on Port %d\n", ServerID, MyPort);

	sleep(1);

	while(1)
	{
		//
		// 	RECEIVE
		//
		Receive(MyPort, &ReceiveMessage);
		ReceivePort = ReceiveMessage->MessageBody[0];
		printf("[Server %d][Port %d <- Port %d] RECEIVE msg from client ", ServerID, MyPort, ReceivePort);
		printf("(content: ");
		for (int ix = 1; ix < MAX_MESSAGE_LENGTH; ++ix)
		{
			printf("%d ", ReceiveMessage->MessageBody[ix]);
		}
		printf(")\n");
		sleep(1);

		//
		// 	SEND
		//
		SendMessage->MessageBody[0] = MyPort;
		for (int ix = 1; ix < MAX_MESSAGE_LENGTH; ++ix)
		{
			SendMessage->MessageBody[ix] = (rand() % 90) + 10;
		}

		printf("[Server %d][Port %d -> Port %d] SEND msg to client      ", ServerID, MyPort, ReceivePort);
		printf("(content: ");
		for (int ix = 1; ix < MAX_MESSAGE_LENGTH; ++ix)
		{
			printf("%d ", SendMessage->MessageBody[ix]);
		}
		printf(")\n");
		sleep(1);
		Send(ReceivePort, SendMessage);
	}
}

void Client1()
{
	int MyPort = 22;
	int ClientID = 1;
	int ServerPort = 11;
	int ReceivePort;

	message* SendMessage = malloc(sizeof(struct message));
	message* ReceiveMessage;

	printf("Client %d Started on Port %d\n", ClientID, MyPort);

	sleep(1);

	while(1)
	{
		//
		//	SEND
		//
		SendMessage->MessageBody[0] = MyPort;
		for (int ix = 1; ix < MAX_MESSAGE_LENGTH; ++ix)
		{
			SendMessage->MessageBody[ix] = (rand() % 90) + 10;
		}

		printf("[Client %d][Port %d -> Port %d] SEND msg to server      ", ClientID, MyPort, ServerPort);
		printf("(content: ");
		for (int ix = 1; ix < MAX_MESSAGE_LENGTH; ++ix)
		{
			printf("%d ", SendMessage->MessageBody[ix]);
		}
		printf(")\n");
		sleep(1);
		Send(ServerPort, SendMessage);

		//
		//	RECEIVE
		//
		Receive(MyPort, &ReceiveMessage);
		ReceivePort = ReceiveMessage->MessageBody[0];
		printf("[Client %d][Port %d <- Port %d] RECEIVE msg from server ", ClientID, MyPort, ReceivePort);
		printf("(content: ");
		for (int ix = 1; ix < MAX_MESSAGE_LENGTH; ++ix)
		{
			printf("%d ", ReceiveMessage->MessageBody[ix]);
		}
		printf(")\n");
		sleep(1);
	}
}

void Client2()
{
	int MyPort = 33;
	int ClientID = 2;
	int ServerPort = 11;
	int ReceivePort;

	message* SendMessage = malloc(sizeof(struct message));
	message* ReceiveMessage;

	printf("Client %d Started on Port %d\n", ClientID, MyPort);

	sleep(1);

	while(1)
	{
		//
		//	SEND
		//
		SendMessage->MessageBody[0] = MyPort;
		for (int ix = 1; ix < MAX_MESSAGE_LENGTH; ++ix)
		{
			SendMessage->MessageBody[ix] = (rand() % 90) + 10;
		}

		printf("[Client %d][Port %d -> Port %d] SEND msg to server      ", ClientID, MyPort, ServerPort);
		printf("(content: ");
		for (int ix = 1; ix < MAX_MESSAGE_LENGTH; ++ix)
		{
			printf("%d ", SendMessage->MessageBody[ix]);
		}
		printf(")\n");
		sleep(1);
		Send(ServerPort, SendMessage);

		//
		//	RECEIVE
		//
		Receive(MyPort, &ReceiveMessage);
		ReceivePort = ReceiveMessage->MessageBody[0];
		printf("[Client %d][Port %d <- Port %d] RECEIVE msg from server ", ClientID, MyPort, ReceivePort);
		printf("(content: ");
		for (int ix = 1; ix < MAX_MESSAGE_LENGTH; ++ix)
		{
			printf("%d ", ReceiveMessage->MessageBody[ix]);
		}
		printf(")\n");
		sleep(1);
	}
}

void Client3()
{
	int MyPort = 44;
	int ClientID = 3;
	int ServerPort = 11;
	int ReceivePort;

	message* SendMessage = malloc(sizeof(struct message));
	message* ReceiveMessage;

	printf("Client %d Started on Port %d\n", ClientID, MyPort);

	sleep(1);

	while(1)
	{
		//
		//	SEND
		//
		SendMessage->MessageBody[0] = MyPort;
		for (int ix = 1; ix < MAX_MESSAGE_LENGTH; ++ix)
		{
			SendMessage->MessageBody[ix] = (rand() % 90) + 10;
		}

		printf("[Client %d][Port %d -> Port %d] SEND msg to server      ", ClientID, MyPort, ServerPort);
		printf("(content: ");
		for (int ix = 1; ix < MAX_MESSAGE_LENGTH; ++ix)
		{
			printf("%d ", SendMessage->MessageBody[ix]);
		}
		printf(")\n");
		sleep(1);
		Send(ServerPort, SendMessage);

		//
		//	RECEIVE
		//
		Receive(MyPort, &ReceiveMessage);
		ReceivePort = ReceiveMessage->MessageBody[0];
		printf("[Client %d][Port %d <- Port %d] RECEIVE msg from server ", ClientID, MyPort, ReceivePort);
		printf("(content: ");
		for (int ix = 1; ix < MAX_MESSAGE_LENGTH; ++ix)
		{
			printf("%d ", ReceiveMessage->MessageBody[ix]);
		}
		printf(")\n");
		sleep(1);
	}
}



int main()
{
	// Initialization
	srand(time(NULL));
	for (int ix = 0; ix < MAX_PORT_NUMBER; ++ix)
	{
		Ports[ix].InIndex = 0;
		Ports[ix].OutIndex = 0;
		Ports[ix].Empty = *(CreateSem(10));
		Ports[ix].Full = *(CreateSem(0));
		Ports[ix].Mutex = *(CreateSem(1));
	}

	// Start the Server and Clients
	ReadyQ = newQueue();
	start_thread(Server1);
	start_thread(Client1);
	start_thread(Client2);
	start_thread(Client3);
	run();
}

