OBJF= mvfoldercopy.o myfile.o

OUTPUT=libmvfuncs.a

$(OUTPUT):$(OBJF)
	ar rv $(OUTPUT) $(OBJF)

%.o : %.c
	gcc -c -I../include $< -o $@


clean:
	rm $(OBJF)
	rm $(OUTPUT)
