OBJF= copyfile.o foldercopy.o

OUTPUT=libcpfuncs.a

$(OUTPUT):$(OBJF)
	ar rv $(OUTPUT) $(OBJF)

%.o : %.c
	gcc -c -I../include $< -o $@


clean:
	rm $(OBJF)
	rm $(OUTPUT)
