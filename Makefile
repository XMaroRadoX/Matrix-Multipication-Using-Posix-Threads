all: run
matrix_multipication: main.o matmult.o
	gcc main.o matmult.o -o matrix_multipication -lpthread

main.o: main.c
	gcc -c main.c

matmult.o: matmult.c
	gcc -c matmult.c

clean:
	rm -f *.o matrix_multipication
run: clean main.o matmult.o matrix_multipication
	@ clear
	@ ./matrix_multipication