hwk1: hwk1.o List.o List.h
	cc -o hwk1 hwk1.o List.o

%.o: %.c
	cc -c -o $@ $< -std=c99
clean:
	rm -f hwk1 *.o