#########################
# makefile
#########################

###################
###  VARIABLES  ###
###################
CC = clang				# compiler
FLAGS = ${CF} ${LF} 	# all flags
CF = -g -Wall			# compiler flags
LF = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer	#linker flags

###################
###  FUNCTIONS  ###
###################
###  all  ###
all: System Objects Main
	${CC} *.o ${FLAGS} -o ENGINE

###  compile main  ###
Main: ./src/main.cpp
	@echo Compiling main...
	${CC} main.cpp -c ${FLAGS}

###  compile system ###
System: ./src/sys*.cpp ./include/sys*.h
	@echo Compiling system...
	${CC} ./src/sys*.cpp -c ${FLAGS}

###  compile game objects  ###
Objects: ./src/go*.cpp ./src/go*.h
	@echo Compiling game objects...
	${CC} ./src/go*.cpp -c ${FLAGS}

###  clean  ###
clean:
	rm ENGINE.exe