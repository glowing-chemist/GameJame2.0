#ifndef PHYSICALOBJECT_HDR
#define PHYSICALOBJECT_HDR
#include "Engine/Engine.hpp"

class PhysicalObject
{
public:
	PhysicalObject(class PhysicsManager* manager);
	~PhysicalObject() = default;

	float3 GetPosition() { return mPosition; }
	virtual const AABB& GetAABB() = 0;

	void Move(const float3 offset);

	float3 GetVelocity() { return mVelocity; }
	void AddVelocity(const float3 velocity);
	void SetVelocity(unsigned int index, float val);
	void SetVelocity(const float3 velocity);

	virtual InstanceID GetInstanceID() { return 0; }

	void PerformPhysics();
	virtual void Finalise() {}

protected:
	float3 mPosition;
	float3 mVelocity;
};

#endif