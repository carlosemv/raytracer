#include "RayTracer.h"

int main() 
{
	RayTracer tracer;
	tracer.set_options("settings.conf");
	tracer.run();
	tracer.write_image("aaaaa.png");
	
	return EXIT_SUCCESS;
}