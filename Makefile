.PHONY: run

all: gridsolver run

gridsolver: main.c util.c
	gcc -o gridsolver main.c util.c
	chmod a+x gridsolver

run: gridsolver
	./gridsolver