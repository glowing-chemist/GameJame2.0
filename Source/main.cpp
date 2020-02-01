
#include "Engine/Engine.hpp"
#include "GLFW/glfw3.h"

#include "Engine/StaticMesh.h"
#include "Player.hpp"
#include "PhysicsManager.hpp"
#include "MeshObject.hpp"

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

	PhysicsManager* physicsManager = new PhysicsManager();

	Scene testScene("Assets\\Materials");

	std::array<std::string, 6> skybox{ "./Assets/Skybox.png", "./Assets/Skybox.png", "./Assets/Skybox.png", "./Assets/Skybox.png", "./Assets/Skybox.png", "./Assets/Skybox.png" };
	testScene.loadSkybox(skybox, &eng);
	testScene.setShadowingLight(float3(10.0f, -10.0f, 10.0f), float3(0.0f, 0.0f, 1.0f));

	const SceneID meshID = testScene.addMesh(*firstMesh, MeshType::Dynamic);

	testScene.loadMaterials(&eng);
	testScene.finalise(&eng);

	eng.setScene(testScene);

	MeshObject* object1 = new MeshObject(meshID, &eng.getScene(), physicsManager);

	eng.registerPass(PassType::GBuffer);
	eng.registerPass(PassType::DeferredPBRIBL);
	eng.registerPass(PassType::DFGGeneration);
	eng.registerPass(PassType::Skybox);
	eng.registerPass(PassType::ConvolveSkybox);
	eng.registerPass(PassType::Composite);

	Player* thePlayer = new Player(window, eng.getCurrentSceneCamera(), physicsManager);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		if (!firstFrame)
			eng.startFrame();

		firstFrame = false;

		thePlayer->DoInput();

		physicsManager->PerformPhysics();

		testScene.finalise(&eng);

		eng.recordScene();
		eng.render();
		eng.swap();
		eng.endFrame();
	}

	delete firstMesh;
	delete thePlayer;
}
