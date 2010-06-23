all:	kbattery

kbattery.o: kbattery.c
	gcc -c kbattery.c

kbattery: kbattery.o
	gcc -o kbattery kbattery.o

clean:
	rm *.o kbattery
