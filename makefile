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
	@rm ${OUT}

perf: build
	gcc main.c lib/*.c -S -fno-asynchronous-unwind-tables -Ilib
	cat *.s > seed.s
	sudo perf stat ./cur seed.s -w
	rm *.s -f ${OUT}

clean:
	rm *.s -f ${OUT}