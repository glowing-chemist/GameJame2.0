#include "PhysicsManager.hpp"
#include "PhysicalObject.hpp"

bool PhysicsManager::RegisterObject(PhysicalObject* object)
{
	mPhysicalObjects.push_back(object);

	return true;
}

void PhysicsManager::PerformPhysics()
{
	for (PhysicalObject* object : mPhysicalObjects)
	{
		object->AddVelocity({ 0.0f, -0.001f, 0.0f });
		object->PerformPhysics();
	}
}