#include <vec3.hpp>
#include <color.hpp>
#include <ray.hpp>

color ray_color(const ray& r){
    return color(0, 0, 0);
}

int main(){
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    int image_height = static_cast<int>(image_width/aspect_ratio);
    image_height = image_height < 1 ? 1 : image_height;

    auto focal_length = 1.0;
    auto viewport_height = 2.0;

    auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
    auto camera_center = point3(0, 0, 0);

    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, 0, -viewport_height);

    auto viewport_delta_u = viewport_u / image_width;
    auto viewport_delta_v = viewport_v / image_height;

    auto viewport_upper_left = camera_center - vec3(0, focal_length, 0) - viewport_u/2 - viewport_v/2;
    auto pixel100_loc = viewport_upper_left + 0.5 * (viewport_delta_u + viewport_delta_v);

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for(int j = 0; j < image_height; j++){
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        
        for(int i = 0; i < image_width; i++){
            auto pixel_center = pixel100_loc + (i * viewport_delta_u) + (j * viewport_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                            \n";
}