CFLAGS = -g -lm
CC = g++ -std=c++0x
EXEC = table
ALL_OBJECTS = main.o ledSelector.o tableout.o
ALL_FILES = main.cpp ledSelector.cpp tableout.cpp

//g++ -std=c++0x -o table main.cpp tableout.cpp ledSelector.cpp -lwiringPi

table: $(ALL_OBJECTS)
	$(CC) $(CFLAGS) -o $(EXEC) $(ALL_OBJECTS)

main.o: main.cpp ledSelector.h tableout.h
tableout.o: tableout.cpp tableout.h ledSelector.h 
ledSelector.o: ledSelector.cpp ledSelector.h tableout.h

clean:
	-rm $(ALL_OBJECTS)
cleaner: clean
	-rm $(EXEC)
test: table
	-./table
