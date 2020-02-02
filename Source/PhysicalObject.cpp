#include "PhysicalObject.hpp"
#include "PhysicsManager.hpp"

PhysicalObject::PhysicalObject(PhysicsManager* manager)
	: mPosition(0.0f, 0.0f, 0.0f)
	, mVelocity(0.0f, 0.0f, 0.0f)
{
	manager->RegisterObject(this);
}

void PhysicalObject::AddVelocity(float3 velocity)
{
	mVelocity += velocity;
}

void PhysicalObject::SetVelocity(unsigned int index, float val)
{
	switch (index)
	{
		case 0:
			mVelocity.x = val;
			break;
		case 1:
			mVelocity.y = val;
			break;
		case 2:
			mVelocity.z = val;
			break;
	}
}

void PhysicalObject::SetVelocity(const float3 velocity)
{
	mVelocity = velocity;
}

void PhysicalObject::Move(float3 offset)
{
	mPosition += offset;
}

void PhysicalObject::PerformPhysics()
{
	Move(mVelocity);
}