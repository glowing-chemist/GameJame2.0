#include "PhysicsManager.hpp"
#include "PhysicalObject.hpp"

PhysicsManager::PhysicsManager(Scene* scene)
	: mScene      (scene)
	, mFloorHeight(0.0f)
{
}

bool PhysicsManager::RegisterObject(PhysicalObject* object)
{
	mPhysicalObjects.push_back(object);

	return true;
}

void PhysicsManager::PerformPhysics()
{
	for (PhysicalObject* object : mPhysicalObjects)
	{
		// Gravity
		object->AddVelocity({ 0.0f, -0.001f, 0.0f });
		object->PerformPhysics();
		float belowFloor = mFloorHeight - object->GetAABB().getBottom().y;
		if (belowFloor > 0)
		{
			object->Move({ 0.0f, belowFloor, 0.0f });
			object->SetVelocity(1, 0.0f);
		}
		std::vector<Scene::Intersection>& intersections = mScene->getIntersections(object->GetInstanceID(), object->GetAABB());
		if (!intersections.empty())
		{
				object->Move(float3(-1) * object->GetVelocity());
				object->SetVelocity(float3(0.0f));
		}

		object->Finalise();
	}
}