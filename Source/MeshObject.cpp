#include "MeshObject.hpp"

#include "Engine/Scene.h"
#include "Engine/StaticMesh.h"

#include "Engine/GeomUtils.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

MeshObject::MeshObject(float3 initPos, SceneID id, Scene* theScene, PhysicsManager* manager)
	: PhysicalObject(manager)
	, mSceneID(id)
	, mScene(theScene)
{
	mInstanceID = theScene->addMeshInstance(id, glm::mat4(1.0f));
	mPosition = initPos;

	Scene::MeshInstance* mesh = mScene->getMeshInstance(mInstanceID);

	mBaseBoundingBox = mesh->mMesh->getAABB();

	Finalise();
}

AABB MeshObject::GetAABB()
{
	glm::mat4 translateMatrix = glm::translate(mPosition);
	return AABB(mBaseBoundingBox * translateMatrix);
}

void MeshObject::Finalise()
{
	Scene::MeshInstance* mesh = mScene->getMeshInstance(mInstanceID);

	//glm::gtx::transform::translate(mesh->mTransformation, mPosition.x, mPosition.y, mPosition.z);
	//glm::mat4 translateMatrix = glm::translate(mPosition);

	auto& vector = mesh->mTransformation[3];

	vector.x = mPosition.x;
	vector.y = mPosition.y;
	vector.z = mPosition.z;
}
