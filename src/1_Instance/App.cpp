#include "App.h"

#include <vector>
#include <iostream>
#include <stdexcept>

namespace VK {
	void APP::run()
	{
		init_window();
		init_vulkan();
		main_loop();
		cleanup();
	}

	void APP::init_window()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	}

	void APP::init_vulkan()
	{
		create_instance();
	}

	void APP::main_loop()
	{
		while (!glfwWindowShouldClose(window))
			glfwPollEvents();
	}

	void APP::cleanup()
	{
		vkDestroyInstance(instance, nullptr);
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void APP::create_instance()
	{
		VkApplicationInfo app_info = {};
		app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		app_info.pNext = nullptr;
		app_info.pApplicationName = "Vulkan Instance";
		app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		app_info.pEngineName = "No Engine";
		app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		app_info.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo create_info = {};
		create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		create_info.pApplicationInfo = &app_info;

		unsigned int glfw_extension_count = 0;
		const char** glfw_extensions;
		glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

		create_info.enabledExtensionCount = glfw_extension_count;
		create_info.ppEnabledExtensionNames = glfw_extensions;
		create_info.enabledLayerCount = 0;

		if (vkCreateInstance(&create_info, nullptr, &instance))
			throw std::runtime_error("failed to create instance!");

		uint32_t extensions_count = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensions_count, nullptr);
		std::vector<VkExtensionProperties> extensions(extensions_count);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensions_count, extensions.data());

		std::cout << "available extensions:" << std::endl;
		for (const auto& extension : extensions)
			std::cout << "\t" << extension.extensionName << std::endl;
		std::cout << "glfw_extensions:" << glfw_extension_count << std::endl;
		std::cout << *glfw_extensions << std::endl;
	}
}
