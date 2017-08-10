
compilecli: makebin lib
	gcc -o bin/cli cli/cli.c -Llib -Iinclude -lmath330 -lm

lib: makeX exp330.o log330.o cos330.o sin330.o tan330.o arccos330.o arcsin330.o arctan330.o 
	ar r libmath330.a exp330.o log330.o cos330.o sin330.o tan330.o arccos330.o arcsin330.o arctan330.o
	cp libmath330.a lib

makeX: math330.h
	mkdir -p include
	mkdir -p lib
	cp math330.h include

exp330.o: makeX exp/exp330.c 
	gcc -Iinclude -c exp/exp330.c 

log330.o: makeX exp/log330.c 
	gcc -Iinclude -c exp/log330.c 

cos330.o: makeX trig/cos330.c 
	gcc -Iinclude -c trig/cos330.c

sin330.o: makeX trig/sin330.c 
	gcc -Iinclude -c trig/sin330.c

tan330.o: makeX trig/tan330.c 
	gcc -Iinclude -c trig/tan330.c

arccos330.o: makeX arc/arccos330.c 
	gcc -Iinclude -c arc/arccos330.c

arcsin330.o: makeX arc/arcsin330.c 
	gcc -Iinclude -c arc/arcsin330.c

arctan330.o: makeX arc/arctan330.c 
	gcc -Iinclude -c arc/arctan330.c

makebin:
	mkdir -p bin

