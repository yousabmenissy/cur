CC=gcc
OUT=cur
lib=lib
IN=main.c ${lib}/*.c
CFLAGS=-I${lib} -O3

build:
	@echo "building..."
	${CC} ${IN} -o ${OUT} ${CFLAGS}

install: build
	@echo "installing..."
	@sudo install -m 755 ${OUT} /usr/bin
	@echo "done"
