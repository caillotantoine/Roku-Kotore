all: ancien_client

ancien_client: client.o class_client.o
	cc -o ancien_client -g client.o class_client.o -lpthread

client.o: client.c
	cc -c client.c

class_client.o: class_client.c
	cc -c class_client.c

clean: 
	rm ancien_client client.o class_client.o
