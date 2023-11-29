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
	float yaw;
	float pitch;
	// float roll;
	// TODO: change update view to allow for roll
};

class Camera
{
public:
	Camera(float screenWidth, float screenHeight);
	Camera(glm::vec3 position, float screenWidth, float screenHeight, Projection type);
	Camera(glm::vec3 position, float screenWidth, float screenHeight, float fov, Projection type);
	Camera(glm::vec3 position, float screenWidth, float screenHeight, float fov, Projection type, EulerAngles angles);

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
	glm::vec3 mFront;
	float mFov;

	// Default values
	const float FOV = 45.0f;
	const glm::vec3 POSITION = glm::vec3(0.0f, 0.0f, 0.0f);
	const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 FRONT = glm::vec3(0.0f, 0.0f, -1.0f);
	const Projection VIEW = Projection::PERSPECTIVE;

	glm::mat4 GetOrthoProjMat();
	glm::mat4 GetPerspProjMat();
};