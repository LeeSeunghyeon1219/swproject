OBJF=mylslib.o

OUTPUT=liblsfuncs.a

$(OUTPUT): $(OBJF)
	ar rv $(OUTPUT) $(OBJF)

%.o: %.c
	gcc -c -I../Include $< -o $@

clean:
	rm $(OBJF)
	rm $(OUTPUT)

