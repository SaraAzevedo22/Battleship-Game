############################# Makefile ##########################
all: ./main
battleship: battleship.o main.o
				gcc -o battleship battleship.o main.o
battleship.o: battleship.c
				gcc -o battleship.o battleship.c -c -W -Wall
main.o: main.c battleship.h
				gcc -o main.o main.c -c -W -Wall
clean:
				rm -rf *.o