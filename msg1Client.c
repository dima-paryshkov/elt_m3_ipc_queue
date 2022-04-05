#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <malloc.h>

int main(int argc, char *argv[])
{
    const char pathname[] = ".msg";
    const int proj_id = 1;
    key_t key;

    int msqid;
    int pid;

    struct msgbuf
    {
        long mtype;
        int pid;
    } * msgp;

    msgp = (struct msgbuf *)malloc(sizeof(struct msgbuf));

    if ((key = ftok(pathname, proj_id)) == -1)
    {
        perror("Error: Cant't create key for msg queue");
        return 1;
    }

    if ((msqid = msgget(key, IPC_CREAT | 0666)) == -1)
    {
        perror("Error: can't create or open, if exist message queue");
        return 2;
    }

    msgp->mtype = 1;

    if (argc == 2)
    {
        msgp->pid = -1;
    }
    else
    {
        pid = getpid();
        msgp->pid = pid;
    }

    if (msgsnd(msqid, (void *)msgp, sizeof(int), 0) == -1)
    {
        perror("Error: Can't send message to queue");
        return 3;
    }

    if (argc == 1)
    {
        int err;
        if ((err = msgrcv(msqid, (void *)msgp, sizeof(int), pid, 0)) == -1)
        {
            perror("Error: Can't receive message from queue");
            return 4;
        }
        else if (err < sizeof(int))
        {
            fprintf(stderr, "Warning: not all bytes was read from message\n");
        }

        fprintf(stdout, "Process %d receive answer from server\n", pid);
    }
    else
    {
        fprintf(stdout, "Process %d send last message\n", pid);
    }
    return 0;
}