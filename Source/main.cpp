
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

	eng.startFrame();
	bool firstFrame = true;

	StaticMesh* firstMesh = new StaticMesh(
		"Assets\\Meshes\\BasicBrick.fbx",
		VertexAttributes::Position4 |
		VertexAttributes::TextureCoordinates |
		VertexAttributes::Normals,
		0
	);

	Scene testScene("Assets\\Materials");

	std::array<std::string, 6> skybox{ "./Assets/Skybox.png", "./Assets/Skybox.png", "./Assets/Skybox.png", "./Assets/Skybox.png", "./Assets/Skybox.png", "./Assets/Skybox.png" };
	testScene.loadSkybox(skybox, &eng);
	testScene.setShadowingLight(float3(10.0f, -10.0f, 10.0f), float3(0.0f, 0.0f, 1.0f));
	const SceneID meshID = testScene.addMesh(*firstMesh, MeshType::Dynamic);
	const InstanceID instanceID = testScene.addMeshInstance(meshID, glm::mat4(1.0f));
	testScene.loadMaterials(&eng);
	testScene.finalise(&eng);

	eng.setScene(testScene);

	eng.registerPass(PassType::GBuffer);
	eng.registerPass(PassType::DeferredPBRIBL);
	eng.registerPass(PassType::DFGGeneration);
	eng.registerPass(PassType::Skybox);
	eng.registerPass(PassType::ConvolveSkybox);
	eng.registerPass(PassType::Composite);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		if (!firstFrame)
			eng.startFrame();

		firstFrame = false;

		Camera& camera = eng.getCurrentSceneCamera();

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.moveForward(0.2f);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.moveBackward(0.2f);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.moveLeft(0.2f);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.moveRight(0.2f);
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			camera.rotateYaw(1.0f);
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			camera.rotateYaw(-1.0f);
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			camera.moveUp((0.2f));
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
			camera.moveDown(0.2f);

		eng.recordScene();
		eng.render();
		eng.swap();
		eng.endFrame();
	}
}
