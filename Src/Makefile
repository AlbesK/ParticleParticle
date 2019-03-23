# files needed to be compiled
SRC = initialiser.c pp_model.c leapfrog.c main.c 

# compilation options
CC = gcc -g
CFLAGS = --std=c99
LN = -lm

# resulting program
BIN = m

OBJ = $(SRC:.c=.o)

${BIN} : ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${BIN} ${LN}

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f ${OBJ} ${BIN}

# Some dependencies
main.o :  main.c initialiser.o pp_model.o Functions.h
initialiser.o : initialiser.c Functions.h
pp_model.o : pp_model.c Functions.h
leapfrog.o : leapfrog.c Functions.h
