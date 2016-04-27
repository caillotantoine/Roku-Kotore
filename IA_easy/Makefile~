all: IA_ease

IA_ease: client.o class_client.o 
	cc -o IA_ease -g client.o class_client.o 

client.o: client.c 
	cc -c client.c


class_client.o: class_client.c
	cc -c class_client.c
clean:
	rm IA_ease client.o class_client.o 
