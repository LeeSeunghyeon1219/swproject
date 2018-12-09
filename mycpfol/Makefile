OUTPUT=mycp

CC=gcc

LPATH=-L../mycplib
IPATH=-I../include
LIB=-lcpfuncs
OBJ=mycp.o

$(OUTPUT):$(OBJ)
	$(CC) -o $(OUTPUT) $(LPATH) $(OBJ) $(LIB)
$(OBJ):mycpmain.c
	$(CC) -c $(IPATH) mycpmain.c -o $(OBJ)


clean:
	rm *.o $(OUTPUT)
