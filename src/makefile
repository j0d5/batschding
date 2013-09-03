########################################
##                                    ##
## Makefile for batschding            ##
##                                    ##
########################################

# Versionsnummer
VERSION = 0.01
# Compiler
# CC = $(shell which mpic++)
CC = $(shell which g++)

# Compilerflags
CFLAGS = -Wall `pkg-config --cflags --libs opencv`

# Linkerflags
LDFLAGS  = 
PROGNAME = ../build/batschding
SRC  = 
OBJS = batschding.o Calibrator.o Color.o Output.o Gamelogic.o Player.o Tracker.o Rectangle.o

all: hello $(OBJS) finish
	@$(CC) $(CFLAGS) -o $(PROGNAME) $(OBJS) $(LDFLAGS)

%.o: %.cpp
    
	@$(CC) $(CFLAGS) -c $<

# Phony targets, will always be executed
.PHONY: clean hello finish
clean:
	@echo
	@echo "    cleaning dirs..."
	@echo
	@rm -f $(PROGNAME) $(OBJS)
	@echo
	@echo "    ...finished."
	@echo

hello:
	@echo
	@echo "    building" $(PROGNAME) $(VERSION) "..."
	@echo

finish:
	@echo
	@echo "    ...finished."
	@echo

