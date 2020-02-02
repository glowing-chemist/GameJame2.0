#include "PhysicsManager.hpp"
#include "PhysicalObject.hpp"

PhysicsManager::PhysicsManager()
	: mFloorHeight(0.0f)
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
		object->Finalise();
		float belowFloor = mFloorHeight - object->GetAABB().getBottom().y;
		if (belowFloor > 0)
		{
			object->Move({ 0.0f, belowFloor, 0.0f });
			object->Finalise();
		}
	}
}