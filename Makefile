all:
	cp -r headers /usr/include/
	gcc -o server server.c
	gcc -o client client.c