#include "sem.h"

//
// a message is an array of 10 integers
//
typedef struct message
{
	int MessageBody[10];
} message;

//
// A port is something that contains N messages, make N=10. 
// There would be semaphores associated with the port, for controlling synchronization. 
// The port “contains” messages hence a port may be a pointer to a Q of messages, or an array of messages.
//
typedef struct port
{
	message Messages[10];
	int InIndex;
	int OutIndex;
	Semaphore_t Empty;
	Semaphore_t Full;
	Semaphore_t Mutex;
} port;

port Ports[100];

//
// The send is a “blocking” asynchronous send that is: it places the message in the port and returns but blocks if port is full.
//
void Send(int PortNumber, message* SendMessage)
{
	int SendMsgIndex;

	P(&(Ports[PortNumber].Empty));
	P(&(Ports[PortNumber].Mutex));

	SendMsgIndex = Ports[PortNumber].InIndex;
	Ports[PortNumber].Messages[SendMsgIndex] = *SendMessage;
	++Ports[PortNumber].InIndex;

	if (Ports[PortNumber].InIndex > 9)
	{
		Ports[PortNumber].InIndex = 0;
	}

	V(&(Ports[PortNumber].Mutex));
	V(&(Ports[PortNumber].Full));
}

//
// The receive is a “blocking” receive.
//
void Receive(int PortNumber, message** ReceiveMessage)
{
	int RecvMsgIndex;

	P(&(Ports[PortNumber].Full));
	P(&(Ports[PortNumber].Mutex));

	RecvMsgIndex = Ports[PortNumber].OutIndex;
	*ReceiveMessage = &Ports[PortNumber].Messages[RecvMsgIndex];
	++Ports[PortNumber].OutIndex;

	if (Ports[PortNumber].OutIndex > 9)
	{
		Ports[PortNumber].OutIndex = 0;
	}

	V(&(Ports[PortNumber].Mutex));
	V(&(Ports[PortNumber].Empty));
}

