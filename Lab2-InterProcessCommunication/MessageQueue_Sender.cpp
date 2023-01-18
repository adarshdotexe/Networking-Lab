#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#define QUEUE_SIZE 10
#define MSG_SIZE 100

using namespace std;

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
	message.mesg_type = 1;

	while(1) {
		cout << "Write Data : ";
		cin.getline(message.mesg_text, MSG_SIZE);

		// msgsnd to send message
		msgsnd(msgid, &message, sizeof(message), 0);

		// display the message
		cout << "Data send is : " << message.mesg_text << endl;
	}

	return 0;
}
