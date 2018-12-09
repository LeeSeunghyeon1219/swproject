OUTPUT=mycat

CC=gcc

LPATH=-L../mycatlib
IPATH=-I../include
LIB=-lcatfuncs
OBJ=myls.o

$(OUTPUT) : $(OBJ)
        $(CC) -o $(OUTPUT) $(LPATH) $(OBJ) $(LIB)
$(OBJ):myls.c
        $(CC) -c $(IPATH) myls.c -o $(OBJ)

clean:
	rim *.o $(OUTPUT) 
~                           

