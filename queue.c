#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>

#include "queue.h"

int msg_init()
{
  int msgid;

  if ((msgid = msgget(IPC_PRIVATE, 0660 | IPC_CREAT)) < 0) {
    perror("Couldn\'t create message queue: ");
    exit(-1);
  }

  return msgid;
}

void msg_free(int msgid)
{
  if (msgctl(msgid, IPC_RMID, NULL) < 0) {
    perror("Can\'t delete queue: ");
    exit(-1);
  }
}

void msg_send(int msgid, Message *msg)
{
  if ((msgsnd(msgid, msg, sizeof(Message) - sizeof(long), 0)) < 0) {
    perror("Failed to send message in queue: ");
    exit(-1);
  }
}
