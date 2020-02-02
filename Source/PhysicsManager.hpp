#include <vector>

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager() = default;
	bool RegisterObject(class PhysicalObject* object);
	void PerformPhysics();
private:
	std::vector<class PhysicalObject*> mPhysicalObjects;

	float mFloorHeight;
};