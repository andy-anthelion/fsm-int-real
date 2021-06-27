CC = g++
FLAGS = -Wall

unit: fsm_int_real.cpp List.o Array.o
	$(CC) $(FLAGS) -D_UNIT_TESTS  -o fsm.unit fsm_int_real.cpp List.o Array.o

all: fsm_int_real.cpp List.o Array.o
	$(CC) $(FLAGS) -o fsm.out fsm_int_real.cpp List.o Array.o

List.o: List.cpp List.h
	$(CC) $(FLAGS) -c List.cpp

Array.o: Array.h Array.cpp
	$(CC) $(FLAGS) -c Array.cpp

clean:
	rm *.o *.out
