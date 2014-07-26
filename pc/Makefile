CC=g++

usetreg: main.o serial.o register.o
	$(CC) -o usetreg main.o serial.o -lboost_system

main.o: main.cpp
	$(CC) -o main.o -c main.cpp
	
serial.o: serial.cpp
	$(CC) -o serial.o -c serial.cpp

register.o: register.cpp
	$(CC) -o register.o -c register.cpp


clean:
	rm usetreg main.o serial.o
