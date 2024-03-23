#SETTING THE VARIABLES
COMPILER = g++
CXXFLAGS = -std=c++20 -Wall
JSONPATH = /home/riccardorota/PACS/pacs-examples/Examples/include
INCLUDES = -I$(JSONPATH)
EXEC = main
SOURCES = main.cpp gradient_method.cpp point.cpp
HEADERS = gradient_method.hpp point.hpp
RM = rm

#COMPILING THE EXECUTABLE
$(EXEC) : $(SOURCES) $(HEADERS)
	$(COMPILER) $(CXXFLAGS) $(INCLUDES) $(SOURCES) -o $(EXEC) 
 
#CLEANING
clean:
	@$(RM) $(EXEC)

