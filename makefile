CC=gcc
OUT=cur
lib=lib
IN=main.c ${lib}/*.c
CFLAGS=-I${lib} -O3

build:
	@echo "building..."
	@${CC} ${IN} -o ${OUT} ${CFLAGS}

install: build
	@echo "installing..."
	@sudo install -m 755 ${OUT} /usr/bin
	@echo "done"
	@rm ${OUT}

perf:
	${CC} ${IN} -o ${OUT} ${CFLAGS}
	gcc main.c lib/*.c -S -fno-asynchronous-unwind-tables -Ilib
	cat *.s > seed.s
	sudo perf stat ./cur seed.s -w
	rm -f *.s ${OUT}

report:
	${CC} ${IN} -o ${OUT} ${CFLAGS}
	gcc main.c lib/*.c -S -fno-asynchronous-unwind-tables -Ilib
	cat *.s > seed.s
	sudo perf record ./cur seed.s -w
	perf report
	rm -f *.s *.data ${OUT} 

clean:
	rm -f *.s ${OUT}