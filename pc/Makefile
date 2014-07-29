CC=g++

usetreg: main.o serial.o register.o exceptions.o ucontroller.o
	$(CC) -o usetreg main.o serial.o register.o exceptions.o -lboost_system

main.o: main.cpp
	$(CC) -o main.o -c main.cpp
	
serial.o: serial.cpp
	$(CC) -o serial.o -c serial.cpp

register.o: register.cpp
	$(CC) -o register.o -c register.cpp

excetions.o: exceptions.cpp
	$(CC) -o exceptions.o -c exceptions.cpp

ucontroller.o: ucontroller.cpp
	$(CC) -o ucontroller.o -c ucontroller.cpp

clean:
	rm usetreg main.o serial.o
