#include "RayTracer.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

glm::vec3 RayTracer::color(const Ray& _ray, int depth) const
{
	HitRecord record;
	float max = std::numeric_limits<float>::max();
	if (world.hit(_ray, 0.001, max, record)) {
		Ray scattered;
		glm::vec3 attenuation;
		bool scatter = record.material->scatter(_ray, record, attenuation, scattered);
		if (depth < max_depth && scatter)
			return attenuation*color(scattered, depth+1);
		else
			return glm::vec3(0, 0, 0);
	}

	glm::vec3 blue = glm::vec3(0.5, 0.7, 1.0);
	glm::vec3 white = glm::vec3(1.0, 1.0, 1.0);

	glm::vec3 unit_direction = glm::normalize(_ray.direction());
	float t = 0.5 * (unit_direction.y + 1.0);
	return (1.0F - t) * white + t * blue;
}

void RayTracer::run()
{
	data = std::make_unique<unsigned char[]>(width*height*3);
	auto byte = data.get();

    std::chrono::duration <double> time;

 	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			glm::vec3 col;
			for (int s = 0; s < samples; ++s) {
				
				float rightwardness = j + dis(gen);
				float upwardness = height - (i+1) + dis(gen);

				float u = rightwardness / float(width);
				float v = upwardness / float(height);
				
				Ray r = cam.get_ray_to(u, v);

				col += color(r, 0);
			}

			col /= float(samples);

			col = 255.99F * glm::sqrt(col);
			*byte++ = int(col.r);
			*byte++ = int(col.g);
			*byte++ = int(col.b);
		}
	}

	auto end = std::chrono::steady_clock::now();
	time += end-start;
    std::cout << "total: " << time.count() << " seconds\n";
}

void RayTracer::write_image(std::string file_name) const
{
	stbi_write_png(file_name.c_str(), width, height, 3, data.get(), 0);
}

void RayTracer::set_options(std::string config_file)
{
	// options, configuration, settings or parameters?
	namespace po = boost::program_options;

	// get regular options
	std::string lookfrom, lookat, vup; float vfov;
    po::options_description opts("Ray Tracer configuration");
    opts.add_options()
        ("Dimensions.width", po::value<int>(&width))
        ("Dimensions.height", po::value<int>(&height))
        ("Dimensions.samples", po::value<int>(&samples))
        ("Dimensions.maxdepth", po::value<int>(&max_depth))
        ("Camera.lookfrom", po::value<std::string>(&lookfrom))
        ("Camera.lookat", po::value<std::string>(&lookat))
        ("Camera.vup", po::value<std::string>(&vup))
        ("Camera.vfov", po::value<float>(&vfov));
    po::variables_map vm;
    auto parsed_opts = po::parse_config_file<char>(config_file.c_str(), opts, true);
    po::store(parsed_opts, vm);
    po::notify(vm);

    // create camera
    cam = Camera(init_vec3(lookfrom), init_vec3(lookat), init_vec3(vup),
    	vfov, float(width)/float(height));

    // get names of all variables
    std::set<std::string> all_vars;
 	for (const auto& o : parsed_opts.options) {
	    if (o.unregistered)
	        all_vars.insert(o.string_key);
	}

	// split variables by section, 
	// put them all in a po::options_description (var_opts)
	std::set<std::string> material_vars, object_vars;
	std::string materials_prefix("Materials.");
    std::string objects_prefix("Objects.");
	po::options_description var_opts("Ray Tracer variable options");
	for (auto v : all_vars) {
    	if (!v.compare(0, materials_prefix.size(), materials_prefix))
    		material_vars.insert(v);
    	else if (!v.compare(0, objects_prefix.size(), objects_prefix))
    		object_vars.insert(v);
        var_opts.add_options()
        	(v.c_str(), po::value<std::vector<std::string>>()->multitoken());
	}

	// parse config file again for var_opts
    parsed_opts = po::parse_config_file<char>(config_file.c_str(), var_opts, true);
    po::store(parsed_opts, vm);

    // create and map materials 
    std::map<std::string, std::shared_ptr<Material>> materials;
 	for (auto v : material_vars) {
 		auto params = vm[v].as<std::vector<std::string>>();
 		if (params[0] == "Lambertian") {
 			auto albedo = init_vec3(params[1]);
    		materials[v] = std::make_shared<Lambertian>(albedo, gen, dis);
 		}
 		else if (params[0] == "Metal") {
 			auto albedo = init_vec3(params[1]);
			auto fuzz = std::stof(params[2]);
    		materials[v] = std::make_shared<Metal>(albedo, fuzz, gen, dis);
 		}
	}

	// create objects and add them to world
 	for (auto v : object_vars) {
 		auto params = vm[v].as<std::vector<std::string>>();
 		if (params[0] == "Sphere") {
 			auto center = init_vec3(params[1]);
			auto radius = std::stof(params[2]);
			auto material = materials[materials_prefix+params[3]];
			auto s = std::make_unique<Sphere>(center, radius, material);
			world.add(std::move(s));
 		}
	}
}

glm::vec3 RayTracer::init_vec3(std::string _values) const
{
	std::istringstream iss(_values);
	float x, y, z;
	iss >> x >> y >> z;
	return glm::vec3(x, y, z);
}