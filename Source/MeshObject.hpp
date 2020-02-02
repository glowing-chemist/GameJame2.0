#include "PhysicalObject.hpp"

class MeshObject : public PhysicalObject
{
public:
	MeshObject(float3 initPos, SceneID id, class Scene* theScene, class PhysicsManager* manager);
	virtual void Finalise() override;

	virtual InstanceID GetInstanceID() { return mInstanceID; }

	virtual AABB GetAABB() override;

private:
	SceneID mSceneID;
	InstanceID mInstanceID;
	class Scene* mScene;

	AABB mBaseBoundingBox;
};
