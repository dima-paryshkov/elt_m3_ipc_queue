#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdbool.h>
#include <malloc.h>

int main()
{
    const char pathname[] = ".msg";
    const int proj_id = 1;
    key_t key;

    int msqid;

    struct msgbuf
    {
        long mtype;
        int pid;
    } *msgp;

    msgp = (struct msgbuf*)malloc(sizeof(struct msgbuf));

    if ((key = ftok(pathname, proj_id)) == -1)
    {
        perror("Error: Cant't create key for msg queue");
        return 1;
    }

    if ((msqid = msgget(key, IPC_CREAT | 0666)) == -1)
    {
        perror("Error: can't open or create message queue");
        return 2;
    }

    int err;
    while (true)
    {
        if ((err = msgrcv(msqid, (void*)msgp, sizeof(int), 1, 0)) == -1)
        {
            if (errno == EAGAIN)
            {
                perror("Error: Queue was delete");
                return 3;
            }
            else
            {
                perror("Error: Can't get message from queue");
                return 4;
            }
        }

        if (err < sizeof(int))
        {
            fprintf(stdout, "Warning: not all bytes was read from message\n");
        }

        msgp->mtype = msgp->pid;
        msgp->pid = 0;

        fprintf(stdout, "Connect new process with pid %d\n", msgp->pid);

        if (msgsnd(msqid, (void*)msgp, sizeof(int), 0) == -1)
        {
            perror("Error: Can't send message to queue");
            return 5;
        }

    }

    return 0;
}