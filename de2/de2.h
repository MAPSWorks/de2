#pragma once

#include "framework.h"
#include "shader.h"
//https://github.com/ademirtug/ecs_s/
#include "../../ecs_s/ecs_s.hpp"
#include "thread_pool.h"
#include <any>
#include <iostream>

class mesh;
class model;
class light;
class camera;

struct visible { bool value{ true }; };
struct invisible {};

template<typename T>
class sub_system {
public:
    virtual void process(ecs_s::registry& world, T& evt) = 0;
};

class renderer_system : public sub_system<std::chrono::nanoseconds> {
public:
    renderer_system();
    void enable_fill_mode();
    void enable_point_mode();
    void enable_wireframe_mode();
    void process(ecs_s::registry& world, std::chrono::nanoseconds& interval) override;
    
    glm::mat4 get_view();
    glm::mat4 get_projection();

    std::shared_ptr<camera> cam_;
    std::shared_ptr<light> l;
    glm::vec2 mouse_pos{ 0, 0 };
    float fov{ glm::pi<float>() / 4 }, z_near{ 0.01f }, z_far{ 200.0f };
};


//event types
struct resize {};
struct key {};
struct process_input {};
struct pre_render {};
struct render {};
struct post_render {};

//engine
class de2 {

    template<typename T>
    auto& get_subs() {
        static std::vector<std::function<void(std::chrono::nanoseconds)>> subs;
        return subs;
    }

public:
    //term: meyers singleton
    static de2& get_instance();

    de2(const de2& other) = delete;
    de2 operator=(const de2& other) = delete;
    void init();
    void run();

    void set_title(const std::string& title);
    std::string get_title();
    void resize(size_t width, size_t height);
    bool has_model(const std::string& key);
    
    template<typename T, typename ...Ts>
    [[nodiscard]] std::shared_ptr<model> load_model(const std::string& key, Ts... args) {
        if (model_cache_.exists(key))
            return std::static_pointer_cast<T>(model_cache_.get(key));

        std::shared_ptr<T> md = std::make_shared<T>(std::forward<Ts>(args)...);
        md->upload();
        model_cache_.put(key, md);
        return md;
    }
    template<typename T, typename ...Ts>
    [[nodiscard]] auto load_model_async(std::string key = "", Ts... args) -> decltype(auto) {
        return pool_.enqueue([this, key, args...]() {
            if (model_cache_.exists(key)) {
                return model_cache_.get(key);
            }
            std::shared_ptr<model> md;
            try {
                md = std::make_shared<T>(args...);
                return md;
            }
            catch (std::exception e) {
                //std::cout << "pool error: key ->" << key << " - " << e.what();
            }
            return md;
        });
    }
    template<typename T, typename F>
    void on(F&& f) {
        get_subs<T>().emplace_back(f);
    }


    //events
    std::function<void(int key, int scancode, int action, int mods)>			on_key;
    std::function<void(int error, const char* desc)>							on_error;
    std::function<void(int width, int height)>									on_resize;
    std::function<void()>                                                       on_process_input;


    std::function<void (GLFWwindow* window, double xpos, double ypos)>          cursor_pos_callback;
    std::function<void (GLFWwindow* window, double xoffset, double yoffset)>    mouse_wheel_callback;
    std::function<void(GLFWwindow* window, int button, int action, int mods)>   mouse_button_callback;

    std::unordered_map<std::string, std::shared_ptr<program>> programs;
    glm::vec2 viewport{ 1024, 768 };
    GLFWwindow* window{ nullptr };
    size_t fps{ 0 };
    thread_safe_lru_cache<std::string, std::shared_ptr<model>> model_cache_;
protected:
    de2();
    thread_pool pool_;
    
};



