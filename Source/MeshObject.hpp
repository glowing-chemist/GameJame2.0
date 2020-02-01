#include "PhysicalObject.hpp"

class MeshObject : public PhysicalObject
{
public:
	MeshObject(SceneID id, class Scene* theScene, class PhysicsManager* manager);
	virtual void Finalise() override;
private:
	SceneID mSceneID;
	InstanceID mInstanceID;
	class Scene* mScene;
};