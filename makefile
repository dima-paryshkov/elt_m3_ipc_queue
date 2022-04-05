msg1: msg1Server.c msg1Client.c
	gcc msg1Server.c -o msg1Server
	gcc msg1Client.c -o msg1Client

msg1Server: msg1Server.c
	gcc msg1Server.c -o msg1Server

msg1Client:  msg1Client.c
	gcc msg1Client.c -o msg1Client
	
msg9-7a: msg9-7a.c
	gcc msg9-7a.c -o msg9-7a

msg9-7b: msg9-7b.c
	gcc msg9-7b.c -o msg9-7b

msg9-7:
	gcc msg9-7a.c -o msg9-7a
	gcc msg9-7b.c -o msg9-7b

