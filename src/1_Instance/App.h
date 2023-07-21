#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace VK {

    const int WIDTH = 800;
    const int HEIGHT = 600;

    class APP
    {
    public:
        void run();

    private:
        void init_window();
        void init_vulkan();
        void main_loop();
        void cleanup();
        void create_instance();

        GLFWwindow* window;
        VkInstance instance;
    };
}