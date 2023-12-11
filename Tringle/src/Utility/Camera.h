#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

enum Projection
{
	ORTHOGRAPHIC,
	PERSPECTIVE
};

struct EulerAngles
{
	EulerAngles(float y, float p) : yaw(y), pitch(p) {}
	float yaw;
	float pitch;
	// float roll;
	// TODO: change update view to allow for roll
};

class Camera
{
public:
	// TODO: add additional constructors, or find alternative method for variable number of input parameters

	Camera(float screenWidth, float screenHeight);
	Camera(glm::vec3 position, glm::vec3 worldUp, float screenWidth, float screenHeight, float fov, Projection type, EulerAngles angles);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	
	void UpdateView(EulerAngles angles);

private:
	// Window props
	// Needed to calculate projection matrix
	float mScreenWidth;
	float mScreenHeight;
	float mAspectRatio;

	// Projection matrix type (orthographic || perspective)
	Projection mView;

	// Camera view props
	glm::vec3 mPosition;
	glm::vec3 mUp;
	glm::vec3 mRight;
	glm::vec3 mFront;
	float mFov;

	// World up vector
	glm::vec3 mWorldUp;

	// Default values
	const float FOV = 45.0f;
	const glm::vec3 POSITION = glm::vec3(0.0f, 0.0f, 0.0f);
	const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 WORLDUP = glm::vec3(0.0f, 1.0f, 0.0f);
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const Projection VIEW = Projection::PERSPECTIVE;

	glm::mat4 GetOrthoProjMat();
	glm::mat4 GetPerspProjMat();
};