.PHONY: run

all: gridsolver run

gridsolver: main.c util.c checksolution.c
	gcc -o gridsolver main.c util.c checksolution.c
	chmod a+x gridsolver

run: gridsolver
	./gridsolver test_remi.txt
	./gridsolver test_remi1.txt
	./gridsolver test_remi2.txt
