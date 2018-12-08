
.PHONY:all clean


%.o: %.c
	gcc -o $@ $<
clean:
	rm -f *.o
