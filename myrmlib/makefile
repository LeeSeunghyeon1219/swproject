OBJF=myrmlib.o

OUTPUT=librmfuncs.a

$(OUTPUT): $(OBJF)
        ar rv $(OUTPUT) $(OBJF)

%.o: %.c
        gcc -c -I../Include $< -o $@

clean:
	rm $(OBJF)
	 rm $(OUTPUT)


