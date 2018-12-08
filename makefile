
.PHONY:all clean

all: mycp mymv

<<<<<<< Updated upstream
%.o: %.c
	gcc -o $@ $<
clean:
	rm -f *.o
=======
mycp: mycp.c
	gcc -o mycp mycp.c
mymv: mymv.c
	gcc -o mymv mymv.c


clean : 
	rm -r mycp
	rm -r mymv
>>>>>>> Stashed changes
