std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> dis;

int width = 600;
int height = 300;

// _lookfrom, _lookat, _vup, float _vfov, float _aspect
Camera cam(glm::vec3(-2,2,1), glm::vec3(0,0,-1), glm::vec3(0,1,0),
	0.1, float(width)/float(height));

auto m1 = std::make_shared<Lambertian>(glm::vec3(1.0, 0.0, 0.0), gen, dis);
auto m2 = std::make_shared<Lambertian>(glm::vec3(0.8, 0.8, 0.0), gen, dis);
auto m3 = std::make_shared<Metal>(glm::vec3(0.8, 0.6, 0.2), 0.5, gen, dis);
auto m4 = std::make_shared<Metal>(glm::vec3(0.8, 0.8, 0.8), 0, gen, dis);

HitableList world;
auto s1 = std::make_unique<Sphere>(glm::vec3(0, 0, -1), 0.5, m1);
auto s2 = std::make_unique<Sphere>(glm::vec3(0, -100.5, -1), 100, m2);
auto s3 = std::make_unique<Sphere>(glm::vec3(1, 0, -1), 0.5, m3);
auto s4 = std::make_unique<Sphere>(glm::vec3(-1, 0, -1), 0.5, m4);

world.add(std::move(s1)); world.add(std::move(s2));
world.add(std::move(s3)); world.add(std::move(s4));

auto data = std::make_unique<unsigned char[]>(width*height*3);
auto byte = data.get();

int samples = 100;