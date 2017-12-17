# commands
CXX = g++
DEL = rm

# options
DEBUG = -g
WARNING = -Wall
OPTMIZE = -O3
STD = -std=c++14
OPTIONSCXX = $(STD) $(WARNING) $(OPTMIZE)


# directories
DECLRDIR = -I . -I ./include
SRCDIR = ./src/
BINDIR = ./bin/

EXEC = exec

### executable target
main: bin Vec3.o HitableList.o Sphere.o main.o
	$(CXX) $(BINDIR)Vec3.o $(BINDIR)HitableList.o $(BINDIR)Sphere.o $(BINDIR)main.o -o $(EXEC) $(OPTIONSCXX)

### bin folder (created only if it doesnt exist)
bin:
	mkdir -p ./bin/

main.o: $(SRCDIR)main.cpp
	$(CXX) $(SRCDIR)main.cpp -c -o $(BINDIR)main.o $(OPTIONSCXX) $(DECLRDIR)

Vec3.o: $(SRCDIR)Vec3.cpp
	$(CXX) $(SRCDIR)Vec3.cpp -c -o $(BINDIR)Vec3.o $(OPTIONSCXX) $(DECLRDIR)

HitableList.o: $(SRCDIR)HitableList.cpp
	$(CXX) $(SRCDIR)HitableList.cpp -c -o $(BINDIR)HitableList.o $(OPTIONSCXX) $(DECLRDIR)

Sphere.o: $(SRCDIR)Sphere.cpp
	$(CXX) $(SRCDIR)Sphere.cpp -c -o $(BINDIR)Sphere.o $(OPTIONSCXX) $(DECLRDIR)


### clear objects & executable
clean: bin
	$(DEL) ./$(EXEC)
	$(DEL) $(BINDIR)*.o
