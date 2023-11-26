#pragma once

#include "glm.hpp"

class Camera
{
public:
	Camera(glm::vec3 position, float aspectRatio);
	glm::mat4 GetViewTransform();
	glm::mat4 GetProjectionMatrix();
	enum Projection
	{
		ORTHOGRAPHIC,
		PERSPECTIVE
	};

private:
	Projection mView;
	glm::vec3 mPosition;
	float mAspectRatio;

	// TODO

	glm::mat4 GetOrthoProjMat();
	glm::mat4 GetPerspProjMat();
};