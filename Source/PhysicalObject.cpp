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

void PhysicalObject::Move(float3 offset)
{
	mPosition += offset;
}

void PhysicalObject::PerformPhysics()
{
	Move(mVelocity);
}