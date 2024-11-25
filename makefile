.PHONY: run clean compile

compile program: main.o
	@gcc -o program main.o

run: program
	@./program

clean:
	@rm -f *.o program

main.o: main.c
	@gcc -c main.c
