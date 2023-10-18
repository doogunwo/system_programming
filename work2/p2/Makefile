main : main.o calc.o
	gcc -o main main.o calc.o
main.o : main.c
	gcc -c main.c 
calc.o : ../sub/calc.c 
	gcc -c ../sub/calc.c 
clean :
	rm -rf main calc.o 
	