# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Object files
OBJS = main.o hulpfuncties.o

# Executable name
TARGET = DS

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cc hulpfuncties.h
	$(CXX) $(CXXFLAGS) -c main.cc

hulpfuncties.o: hulpfuncties.cc hulpfuncties.h
	$(CXX) $(CXXFLAGS) -c hulpfuncties.cc

clean:
	rm -f $(OBJS) $(TARGET)
