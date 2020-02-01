//#include "Engine.h"

#include "Engine/Engine.hpp"
#include "GLFW/glfw3.h"

#include "PhysicalObject.hpp"

class Player : public PhysicalObject
{
public:
	Player(struct GLFWwindow* window, Camera& camera, class PhysicsManager* manager);
	~Player() = default;

	float3 GetPosition() { return mPosition; }

	void DoInput();

private:
	struct GLFWwindow* mWindow;
	Camera& mCamera;
};