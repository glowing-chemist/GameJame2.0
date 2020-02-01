#include <vector>

class PhysicsManager
{
public:
	bool RegisterObject(class PhysicalObject* object);
	void PerformPhysics();
private:
	std::vector<class PhysicalObject*> mPhysicalObjects;
};