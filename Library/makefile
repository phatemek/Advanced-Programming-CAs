CC := g++ --std=c++11

all: a.out

a.out: main.o Library.o Person.o Document.o Student.o Professor.o Book.o Reference.o Magazine.o
	$(CC) main.o Library.o Person.o Document.o Student.o Professor.o Book.o Reference.o Magazine.o -o a.out

main.o: Library.hh main.cc
	$(CC) -c main.cc -o main.o

Library.o: Library.hh Person.hh Document.hh Student.hh Professor.hh Book.hh Reference.hh Magazine.hh Library.cc
	$(CC) -c Library.cc -o Library.o

Person.o: Person.hh Document.hh Person.cc
	$(CC) -c Person.cc -o Person.o

Document.o: Document.hh Document.cc
	$(CC) -c Document.cc -o Document.o

Student.o: Student.hh Person.hh Student.cc
	$(CC) -c Student.cc -o Student.o

Professor.o: Professor.hh Person.hh Professor.cc
	$(CC) -c Professor.cc -o Professor.o

Book.o: Book.hh Document.hh Book.cc
	$(CC) -c Book.cc -o Book.o

Reference.o: Reference.hh Document.hh Reference.cc
	$(CC) -c Reference.cc -o Reference.o

Magazine.o: Magazine.hh Document.hh Magazine.cc
	$(CC) -c Magazine.cc -o Magazine.o

.PHONY: clean
clean:
	rm -r *.o
