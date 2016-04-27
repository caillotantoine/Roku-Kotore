
all: RokuKotore

RokuKotore: main.o draw.o event.o text.o init.o image.o login.o plateau.o class_client.o setting.o menu.o singleplayer.o statistic.o multiplayer.o
	cc -o RokuKotore -g main.o draw.o event.o text.o init.o image.o login.o plateau.o class_client.o setting.o singleplayer.o menu.o statistic.o multiplayer.o -lSDL2 -lSDL2_mixer -lSDL2_ttf -lpthread 

main.o: main.c
	cc -c main.c -g

draw.o: draw.c
	cc -c draw.c -g

event.o: event.c
	cc -c event.c -g

text.o: text.c
	cc -c text.c -g

init.o: init.c
	cc -c init.c -g

image.o: image.c
	cc -c image.c -g

login.o: login.c
	cc -c login.c -g

plateau.o: plateau.c
	cc -c plateau.c -g

class_client.o: class_client.c
	cc -c class_client.c -g

setting.o: setting.c
	cc -c setting.c -g

menu.o: menu.c
	cc -c menu.c -g

singleplayer.o: singleplayer.c
	cc -c singleplayer.c -g

statistic.o: statistic.c
	cc -c statistic.c -g

multiplayer.o: multiplayer.c
	cc -c multiplayer.c -g

clean:
	rm RokuKotore main.o draw.o event.o text.o init.o image.o login.o plateau.o class_client.o setting.o menu.o singleplayer.o statistic.o multiplayer.o
