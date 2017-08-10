proj_2D: driver_2D.o my_struct.o
	gcc -o proj_2D driver_2D.o my_struct.o

driver_2D.o: prototypes.h driver_2D.c 
	gcc -I. -c driver_2D.c

my_struct.o: prototypes.h my_struct.c
	gcc -I. -c my_struct.c

clean:
	-rm -rf *.o
	-rm -rf proj_2D
