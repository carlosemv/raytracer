# commands
CXX = g++
DEL = rm

# options
DEBUG = -g
WARNING = -Wall
OPTMIZE = -O3
STD = -std=c++14
OPTIONSCXX = $(STD) $(WARNING) $(OPTMIZE)

#libraries
LIBS = -lboost_program_options

# directories
DECLRDIR = -I ./include -I ./glm-0.9.7.1
SRCDIR = ./src/
BINDIR = ./bin/

EXEC = raytracer

### executable target
main: bin Camera.o Lambertian.o Metal.o HitableList.o Sphere.o RayTracer.o main.o
	$(CXX) $(BINDIR)Camera.o $(BINDIR)Lambertian.o $(BINDIR)Metal.o $(BINDIR)HitableList.o \
	$(BINDIR)Sphere.o $(BINDIR)RayTracer.o $(BINDIR)main.o -o $(EXEC) $(OPTIONSCXX) $(LIBS)

### bin folder (created only if it doesnt exist)
bin:
	mkdir -p ./bin/

%.o: $(SRCDIR)%.cpp
	$(CXX) -c $< -o $(BINDIR)$@ $(OPTIONSCXX) $(DECLRDIR)

main.o: $(SRCDIR)main.cpp
Camera.o: $(SRCDIR)Camera.cpp
Lambertian.o: $(SRCDIR)Lambertian.cpp
Metal.o: $(SRCDIR)Metal.cpp
HitableList.o: $(SRCDIR)HitableList.cpp
Sphere.o: $(SRCDIR)Sphere.cpp
RayTracer.o: $(SRCDIR)RayTracer.cpp


### clear objects & executable
clean: bin
	$(DEL) ./$(EXEC)
	$(DEL) $(BINDIR)*.o
