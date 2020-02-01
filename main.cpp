
#include "Engine/Engine.hpp"
#include "GLFW/glfw3.h"

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // only resize explicitly
	auto* window = glfwCreateWindow(1600, 900, "wall", nullptr, nullptr);

	Engine eng(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
}
