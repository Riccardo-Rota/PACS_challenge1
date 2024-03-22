#SETTING THE VARIABLES
COMPILER = g++
OPTIONS = -std=c++20 -Wall
EXEC = main
SOURCES = main.cpp gradient_method.cpp point.cpp
HEADERS = gradient_method.hpp point.hpp
RM = rm

#COMPILING THE EXECUTABLE
$(EXEC) : $(SOURCES) $(HEADERS)
	$(COMPILER) $(OPTIONS) $(SOURCES) -o $(EXEC)

#CLEANING
clean:
	@$(RM) $(EXEC)
