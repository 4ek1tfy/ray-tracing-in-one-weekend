#include "camera.hpp"
#include "constants.hpp"
#include "interval.hpp"
#include "material.hpp"
#include "hittable_list.hpp"

#include "stdexec/execution.hpp"
#include "stdexec/concepts.hpp"
#include "stdexec/coroutine.hpp"
#include "exec/start_detached.hpp"

#include "stb_image_write.hpp"

#include <semaphore>
#include <syncstream>

void camera::render(const hittable& world){
    initialize();

    std::clog << "Rendering scene...\n";

    auto raw_data_ptr = std::make_shared<std::vector<uint8_t>>(image_data);
    auto raw_world_ptr = std::shared_ptr<const hittable>(&world, [](const hittable*){});

    auto render_done = std::make_shared<std::binary_semaphore>(0);

    constexpr int tile_size_x = 32;
    constexpr int tile_size_y = 32;

    int tiles_x = (image_width + tile_size_x - 1) / tile_size_x;
    int tiles_y = (image_height + tile_size_y - 1) / tile_size_y;
    int total_tiles = tiles_x * tiles_y;

    int h = image_height;
    int w = image_width;
    int ch = channels;

    auto scheduler = pool.get_scheduler();

    auto render_pipeline = stdexec::just(raw_world_ptr, raw_data_ptr)
        | stdexec::continues_on(scheduler)

        | stdexec::bulk(stdexec::par, total_tiles, [=, this](int tile_idx, const auto& world_ptr, auto dev_data) {

            {
                std::osyncstream synced_out(std::clog);
                synced_out << "№" << tile_idx << "\n";
            }
            uint8_t* dev_data_ptr = dev_data->data();

            const hittable& local_world = *world_ptr;

            int tile_x = tile_idx % tiles_x;
            int tile_y = tile_idx / tiles_x;

            int start_x = tile_x * tile_size_x;
            int start_y = tile_y * tile_size_y;

            int end_x = std::min(start_x + tile_size_x, w);
            int end_y = std::min(start_y + tile_size_y, h);

            for(int j = start_y; j < end_y; j++){
                for(int i = start_x; i < end_x; i++){
                    color pixel_color(0, 0, 0);

                    for(int sample = 0; sample < samples_per_pixel; sample++){
                        ray r = get_ray(i, j);

                        pixel_color += ray_color(r, max_depth, local_world);
                    }
                    pixel_color = write_color(pixel_sample_scale * pixel_color);

                    uint8_t r = static_cast<int>(pixel_color.x());
                    uint8_t g = static_cast<int>(pixel_color.y());
                    uint8_t b = static_cast<int>(pixel_color.z());

                    int pixel_index = (w * j + i) * ch;

                    dev_data_ptr[pixel_index + 0] = r;
                    dev_data_ptr[pixel_index + 1] = g;
                    dev_data_ptr[pixel_index + 2] = b;
                }
            }         
        })
        | stdexec::then([=](const auto world,auto dev_data) {
            std::clog << "\nRender completed successfully! Saving file...\n";
            stbi_write_png("result.png", w, h, ch, 
                           dev_data->data(), ch * w);
            std::clog << "Done. result.png saved.\n";

            render_done->release();
        });

    exec::start_detached(std::move(render_pipeline));

    render_done->acquire();

    return;
}

void camera::initialize(){
    image_height = static_cast<int>(image_width/aspect_ratio);
    image_height = image_height < 1 ? 1 : image_height;

    image_data.resize(image_height * image_width * channels);

    pixel_sample_scale = 1.0 / samples_per_pixel;

    center = lookfrom;

    auto theta = degrees_to_radians(vfov);
    auto h = std::tan(theta/2);
    auto viewport_height = 2 * h * focus_dist;
    auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    auto viewport_u = viewport_width * u;
    auto viewport_v = viewport_height * -v;
    
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
    
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
}

ray camera::get_ray(int i, int j) const {
    auto offset = sample_square();

    auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

    auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
    auto ray_direction = pixel_sample - ray_origin;
    auto ray_time = random_double();

    return ray(ray_origin, ray_direction, ray_time);
}

vec3 camera::sample_square() const {
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

color camera::ray_color(const ray& r, int depth, const hittable& world) const {
    if(depth <= 0) return color(0, 0, 0);

    hit_record rec;
    if (!world.hit(r, interval(0.001, infinity), rec))
        return background;

    ray scattered;
    color attenuation;
    color color_from_emission = rec.mat->emitted(rec.u, rec.v, rec.p);

    if (!rec.mat->scatter(r, rec, attenuation, scattered))
        return color_from_emission;

    color color_from_scatter = attenuation * ray_color(scattered, depth-1, world);

    return color_from_emission + color_from_scatter;
}

point3 camera::defocus_disk_sample() const {
    auto p = random_in_unit_disk();
    return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}