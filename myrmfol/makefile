OUTPUT=myrm

CC=gcc

LPATH=-L../myrmlib
IPATH=-I../include
LIB=-lrmfuncs
OBJ=myrm.o

$(OUTPUT) : $(OBJ)
        $(CC) -o $(OUTPUT) $(LPATH) $(OBJ) $(LIB)
$(OBJ):myls.c
        $(CC) -c $(IPATH) myrm.c -o $(OBJ)

clean:
	rm *.o $(OUTPUT)

~                           

