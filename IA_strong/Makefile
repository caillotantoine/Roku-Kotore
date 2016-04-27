all: IA

IA: client.o class_client.o ia.o
	cc -o IA -g client.o class_client.o ia.o

client.o: client.c 
	cc -c client.c
ia.o: ia.c
	cc -c ia.c

class_client.o: class_client.c
	cc -c class_client.c
clean:
	rm IA client.o class_client.o ia.o
