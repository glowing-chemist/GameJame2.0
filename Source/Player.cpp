#include "Player.hpp"

Player::Player(class GLFWwindow* window, Camera& camera, PhysicsManager* manager)
	: PhysicalObject(manager)
	, mWindow(window)
	, mCamera(camera)
{
	mPosition = { 0.0f, 0.0f, -10.0f };
}

void Player::DoInput()
{
	float3 movement{ 0.0f, 0.0f, 0.0f };

	if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
		movement.z += 0.2f;
	if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
		movement.z -= 0.2f;
	if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
		movement.x -= 0.2f;
	if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
		movement.x += 0.2f;
	if (glfwGetKey(mWindow, GLFW_KEY_Q) == GLFW_PRESS)
		mCamera.rotateYaw(1.0f);
	if (glfwGetKey(mWindow, GLFW_KEY_E) == GLFW_PRESS)
		mCamera.rotateYaw(-1.0f);
	if (glfwGetKey(mWindow, GLFW_KEY_X) == GLFW_PRESS)
	{
		mVelocity = float3(0.0f);
		movement.y += 0.2f;
	}
	if (glfwGetKey(mWindow, GLFW_KEY_Z) == GLFW_PRESS)
		movement.y -= 0.2f;
	if (glfwGetKey(mWindow, GLFW_KEY_C) == GLFW_PRESS)
		mCamera.rotatePitch(1.0f);
	if (glfwGetKey(mWindow, GLFW_KEY_V) == GLFW_PRESS)
		mCamera.rotatePitch(-1.0f);

	Move(movement);
	mCamera.setPosition(mPosition);
}