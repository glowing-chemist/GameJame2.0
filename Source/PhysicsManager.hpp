#include <vector>

class PhysicsManager
{
public:
	PhysicsManager(class Scene* scene);
	~PhysicsManager() = default;
	bool RegisterObject(class PhysicalObject* object);
	void PerformPhysics();
private:
	std::vector<class PhysicalObject*> mPhysicalObjects;

	class Scene* mScene;
	float mFloorHeight;
};