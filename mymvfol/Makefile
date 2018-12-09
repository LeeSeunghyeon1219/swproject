OUTPUT=mymv

CC=gcc

LPATH=-L../mymvlib
IPATH=-I../include
LIB=-lmvfuncs
OBJ=mymv.o

$(OUTPUT):$(OBJ)
	$(CC) -o $(OUTPUT) $(LPATH) $(OBJ) $(LIB)
$(OBJ):mymvmain.c
	$(CC) -c $(IPATH) mymvmain.c -o $(OBJ)


clean:
	rm *.o $(OUTPUT)
