### During the development of the project, the means of working with System V IPC

This a repository is continue of [this](https://github.com/dima-paryshkov/elt_m3_ipc)

#### Part 3 - message queue 

##### Exercise 5

In this model one of the process is Server. Server get a requests from Client, where code is process ID, who send message, and send them an answer with code 0. If Server get message with pid -1, it's mean that it's last message and Server finish work. 
The client and server progamm can create the queue, it depent on who started first. 
After that server get last message, server stoped and delete queue from system. 

Compile:

    make msg1

or 

	gcc msg1Server.c -o msg1Server
	gcc msg1Client.c -o msg1Client

Launch:
    
    ./msg1Server
    ./msg1Client <word>

"<word>" it's any symbol(s) or number. This option mean last message.

For instance, if you launch so `./msg1Client 1` or `./msg1Client lastmsg` client send message with pid = -1 and it'll be last message, server finish work.