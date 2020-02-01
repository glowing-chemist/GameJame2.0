#include "MeshObject.hpp"

#include "Engine/Scene.h"
#include "Engine/StaticMesh.h"

MeshObject::MeshObject(SceneID id, Scene* theScene, PhysicsManager* manager)
	: PhysicalObject(manager)
	, mSceneID(id)
	, mScene(theScene)
{
	mInstanceID = theScene->addMeshInstance(id, glm::mat4(1.0f));
}

void MeshObject::Finalise()
{
	Scene::MeshInstance* mesh = mScene->getMeshInstance(mInstanceID);

	auto& vector = mesh->mTransformation[3];

	vector.x = mPosition.x;
	vector.y = mPosition.y;
	vector.z = mPosition.z;
}