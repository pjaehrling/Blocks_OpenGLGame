#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
CC=gcc
# CC=g++
FLAGS=-w -c

# Object Files
OBJECTFILES= \
	glm.o \
	gltx.o \
	Drawable.o \
	Texture.o \
	Field.o \
	Position.o \
	Block.o \
	helper.o

LIBS=glm.o gltx.o
	
# Link Libraries and Options
LDLIBSOPTIONS=-lglut -lGLU -lGL

blocksgame: movingBlocks.cpp ${OBJECTFILES}
	${CC} -w -o blocksgame movingBlocks.cpp ${OBJECTFILES} ${LDLIBSOPTIONS}

Drawable.o: Drawable.cpp ${LIBS}
	${CC} $(FLAGS) Drawable.cpp Drawable.hpp ${LIBS} ${LDLIBSOPTIONS}

Texture.o: Texture.cpp ${LIBS}
	${CC} $(FLAGS) Texture.cpp Texture.hpp ${LIBS} ${LDLIBSOPTIONS}

glm.o: glm.c 
	${CC} $(FLAGS) glm.c ${LDLIBSOPTIONS}

Block.o: Block.cpp ${LIBS}
	${CC} $(FLAGS) Block.cpp Block.hpp ${LIBS} ${LDLIBSOPTIONS}

gltx.o: gltx.c 
	${CC} $(FLAGS) gltx.c ${LDLIBSOPTIONS}

helper.o: helper.cpp 
	${CC} $(FLAGS) helper.cpp ${LDLIBSOPTIONS}

Field.o: Field.cpp 
	${CC} $(FLAGS) Field.cpp Field.hpp

Position.o: Position.cpp 
	${CC} $(FLAGS) Position.cpp Position.hpp

clean: 
	rm ${OBJECTFILES} blocksgame
