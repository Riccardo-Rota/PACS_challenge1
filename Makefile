#SETTING THE VARIABLES
COMPILER = g++
OPTIONS = -std=c++20 -Wall
OPTIONS += -I./include
EXEC = main
SOURCES = main.cpp gradient_method.cpp point.cpp
HEADERS = gradient_method.hpp point.hpp
MUPARSER_FILES = ./include/*
RM = rm
 
#COMPILING THE EXECUTABLE
$(EXEC) : $(SOURCES) $(HEADERS)
	$(COMPILER) $(OPTIONS) $(SOURCES) $(MUPARSER_FILES) -o $(EXEC)
 
#CLEANING
clean:
	@$(RM) $(EXEC)

