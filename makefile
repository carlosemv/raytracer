# commands
CXX = g++
DEL = rm -f

# options
DEBUG = -g
WARNING = -Wall
OPTMIZE = -O3
STD = -std=c++14
CXXFLAGS = $(STD) $(WARNING) $(OPTMIZE)

#libraries
LIBS = -lboost_program_options

# directories
DECLRDIR = -I ./include -I ./glm-0.9.7.1
SRCDIR = ./src/
BINDIR = ./bin/

EXEC = raytracer

_OBJ = Camera.o Lambertian.o Metal.o HitableList.o Sphere.o RayTracer.o main.o
OBJ = $(patsubst %,$(BINDIR)%,$(_OBJ))

### executable target
main: bin $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC) $(CXXFLAGS) $(LIBS)

bin:
	mkdir -p ./bin/

$(BINDIR)%.o: $(SRCDIR)%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(DECLRDIR)

### clear objects & executable
clean: bin
	$(DEL) ./$(EXEC)
	$(DEL) $(BINDIR)*.o