
#include "Engine/Engine.hpp"
#include "GLFW/glfw3.h"

#include "Engine/StaticMesh.h"

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // only resize explicitly
	auto* window = glfwCreateWindow(1600, 900, "wall", nullptr, nullptr);

	Engine eng(window);

	StaticMesh* firstMesh = new StaticMesh(
		"Assets\\Meshes\\BasicBrick.fbx",
		VertexAttributes::Position4 |
		VertexAttributes::TextureCoordinates |
		VertexAttributes::Normals,
		0
	);

	Scene testScene("Assets\\Materials");
	//testScene.loadFromFile(VertexAttributes::Position4 | VertexAttributes::Normals | VertexAttributes::TextureCoordinates | VertexAttributes::Material, &engine);
	//testScene.loadSkybox(skybox, &engine);
	testScene.setShadowingLight(float3(10.0f, -10.0f, 10.0f), float3(0.0f, 0.0f, 1.0f));
	testScene.loadMaterials(&eng);
	testScene.finalise(&eng);

	eng.setScene(testScene);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
}
