
.PHONY:all clean

all: mycp mymv

%.o: %.c
	gcc -o $@ $<
clean:
	rm -f *.o
