#########################
# makefile
#########################

###################
###  VARIABLES  ###
###################
CC = clang++				# compiler
FLAGS = ${WF} ${CF} ${LF} 	# all flags
CF = -g # compiler flags
WF = -Wno-comments -Wno-unused-command-line-argument #warning flags
LF =  -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lglut -lGLEW -lGLU -lGL -lm	#linker flags

###################
###  FUNCTIONS  ###
###################
###  all  ###
all: system GOs main
	@${CC} *.o ${FLAGS} -o ./bin/sundile

###  compile main  ###
main: ./src/main.cpp
	@echo =====================
	@echo Compiling main...
	@echo =====================
	@${CC} ./src/main.cpp -c ${FLAGS}
	@echo =====================
	@echo Main compiled!
	@echo =====================

###  compile system ###
sys: system
system: $(wildcard ./src/sys%.cpp ./include/sys%.h)
	@echo =====================
	@echo Compiling system...
	@echo =====================
	@${CC} $(wildcard ./src/sys*.cpp) -c ${FLAGS}
	@echo =====================
	@echo System compiled!
	@echo =====================

###  compile game objects  ###
GOs: gos
gos: $(wildcard ./src/go%.cpp ./include/go%.h)
	@echo =====================
	@echo Compiling GO\'s...
	@echo =====================
	@${CC} $(wildcard ./src/go*.cpp) -c ${FLAGS}
	@echo =====================
	@echo GO\'s compiled!
	@echo =====================

###  clean  ###
clean:
	@rm ./bin/*
