#ifndef PHYSICALOBJECT_HDR
#define PHYSICALOBJECT_HDR
#include "Engine/Engine.hpp"

class PhysicalObject
{
public:
	PhysicalObject(class PhysicsManager* manager);
	~PhysicalObject() = default;

	float3 GetPosition() { return mPosition; }
	void Move(const float3 offset);
	void AddVelocity(const float3 velocity);

	void PerformPhysics();
	virtual void Finalise() {}

protected:
	float3 mPosition;
	float3 mVelocity;
};

#endif