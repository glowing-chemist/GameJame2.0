
#include "Engine/Engine.hpp"
#include "GLFW/glfw3.h"

#include "Engine/StaticMesh.h"
#include "Player.hpp"
#include "PhysicsManager.hpp"
#include "MeshObject.hpp"

#include <glm/gtx/transform.hpp>

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

	StaticMesh* floor = new StaticMesh(
		"Assets\\Meshes\\plane.fbx",
		VertexAttributes::Position4 |
		VertexAttributes::TextureCoordinates |
		VertexAttributes::Normals,
		1
	);

	Scene testScene("Assets\\Materials");

	std::array<std::string, 6> skybox{ "./Assets/textures/bluecloud_ft.jpg", "./Assets/textures/bluecloud_bk.jpg", "./Assets/textures/bluecloud_up.jpg", "./Assets/textures/bluecloud_dn.jpg", "./Assets/textures/bluecloud_rt.jpg","./Assets/textures/bluecloud_lf.jpg" };
	testScene.loadSkybox(skybox, &eng);
	testScene.setShadowingLight(float3(10.0f, -10.0f, 10.0f), float3(0.0f, 0.0f, 1.0f));

	const SceneID meshID = testScene.addMesh(*firstMesh, MeshType::Dynamic);
	const SceneID planeID = testScene.addMesh(*floor, MeshType::Static);

	const InstanceID groundInstance = testScene.addMeshInstance(planeID, glm::scale(float3(100.0f, 100.0f, 100.0f)) *  glm::rotate(glm::radians(-90.0f), float3(1.0f, 0.0f, 0.0f)));

	testScene.loadMaterials(&eng);
	testScene.uploadData(&eng);

	eng.setScene(testScene);
	PhysicsManager* physicsManager = new PhysicsManager(&eng.getScene());

	MeshObject* object1 = new MeshObject({ 0.0f, 10.0f, 0.0f }, meshID, &eng.getScene(), physicsManager);
	MeshObject* object2 = new MeshObject({ 2.5f, 10.0f, 0.0f }, meshID, &eng.getScene(), physicsManager);
	MeshObject* object3 = new MeshObject({ -2.5f, 10.0f, 0.0f }, meshID, &eng.getScene(), physicsManager);

	MeshObject* object4 = new MeshObject({ 0.0f, 14.0f, 0.0f }, meshID, &eng.getScene(), physicsManager);
	MeshObject* object5 = new MeshObject({ 2.5f, 14.0f, 0.0f }, meshID, &eng.getScene(), physicsManager);
	MeshObject* object6 = new MeshObject({ -2.5f, 14.0f, 0.0f }, meshID, &eng.getScene(), physicsManager);

	eng.getScene().computeBounds(MeshType::Dynamic);
	eng.getScene().computeBounds(MeshType::Static);

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

		eng.getScene().computeBounds(MeshType::Dynamic);

		eng.recordScene();
		eng.render();
		eng.swap();
		eng.endFrame();
	}

	delete firstMesh;
	delete thePlayer;
}
