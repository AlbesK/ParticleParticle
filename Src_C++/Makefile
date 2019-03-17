# files needed to be compiled
SRC = initialiser.cpp pp_model.cpp main.cpp

# compilation options
CC = g++ -g
CFLAGS = 
LN = -lm

# resulting program
BIN = mcpp

OBJ = $(SRC:.cpp=.o)

${BIN} : ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${BIN} ${LN}

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f ${OBJ} ${BIN}

# Some dependencies
main.o :  main.cpp initialiser.o pp_model.o Functions.h
initialiser.o : initialiser.cpp Functions.h
pp_model.o : pp_model.cpp Functions.h