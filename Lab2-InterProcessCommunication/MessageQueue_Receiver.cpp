#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#define QUEUE_SIZE 10
#define MSG_SIZE 100

using namespace std;

// structure for message queue
struct mesg_buffer {
	long mesg_type;
	char mesg_text[MSG_SIZE];
} message;

int main()
{
	// ftok to generate unique key
	key_t key = ftok("progfile", 65);

	// msgget creates a message queue
	// and returns identifier
	int msgid = msgget(key, 0666 | IPC_CREAT);

	while(1) {
		// msgrcv to receive message
		msgrcv(msgid, &message, sizeof(message), 1, 0);

		// display the message
		cout << "Data Received is : " << message.mesg_text << endl;
	}

	// to destroy the message queue
	msgctl(msgid, IPC_RMID, NULL);

	return 0;
}
