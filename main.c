
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>

typedef  struct message {
  long type;
  char text[20];
} t_msg;

int main()
{
  int 		val;
  int		msg_id;
  t_msg		msg;

  msg.type = 2;
  msg_id = 884736;
  strcpy(msg.text, "Hello");
  msgsnd(msg_id, &msg, strlen(msg.text) + 1, IPC_NOWAIT);

}
