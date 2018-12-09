OUTPUT=myls

CC=gcc

LPATH=-L../mylslib
IPATH=-I../include
LIB=-llsfuncs
OBJ=myls.o

$(OUTPUT) : $(OBJ)
	$(CC) -o $(OUTPUT) $(LPATH) $(OBJ) $(LIB)
$(OBJ):myls.c
	$(CC) -c $(IPATH) myls.c -o $(OBJ)

clean:
	rm *.o $(OUTPUT)

