cs:
	gcc server/main.c server/functions.c -o server/server.out
ss:
	./server/server.out
cc:
	gcc -g -o client/client.out client/client.c
sc:
	./client/client.out
