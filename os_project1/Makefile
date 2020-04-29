CFLAG = -DDEBUG -Wall -std=c99

main: main.o scheduler.o control.o
	gcc $(CFLAG) main.o scheduler.o control.o -o main
main.o: main.c Makefile
	gcc $(CFLAG) main.c -c
scheduler.o: scheduler.c scheduler.h Makefile
	gcc $(CFLAG) scheduler.c -c
control.o: control.c control.h Makefile
	gcc $(CFLAG) control.c -c
clean:
	rm -rf *o
run:
	sudo ./main
