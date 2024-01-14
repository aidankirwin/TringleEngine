#include "Camera.h"

Camera::Camera(float screenWidth, float screenHeight) : 
	mScreenWidth(screenWidth), mScreenHeight(screenHeight)
{
	mAspectRatio = mScreenWidth / mScreenHeight;

	mWorldUp = WORLDUP;
	mFov = FOV;
	mUp = UP;
	mView = VIEW;

	EulerAngles angles(YAW, PITCH);
	UpdateView(angles);
}

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, float screenWidth, float screenHeight, float fov, Projection type, EulerAngles angles) :
	mPosition(position), mWorldUp(worldUp), mScreenWidth(screenWidth), mScreenHeight(screenHeight), mView(type), mFov(fov)
{
	mAspectRatio = mScreenWidth / mScreenHeight;

	UpdateView(angles);
}

glm::mat4 Camera::GetProjectionMatrix()
{
	if (mView == Projection::PERSPECTIVE)
	{
		return GetPerspProjMat();
	}

	return GetOrthoProjMat();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

void Camera::UpdateView(EulerAngles angles)
{
	// Clamp pitch to be between -89 degrees and 89 degrees
	// If front and worldUp are parallel then we can not define a right vector (cross product yields 0 vector)
	// Up vector becomes zero vector, view matrix is indeterminate
	if (angles.pitch > 89.0f) angles.pitch = 89.0f;
	if (angles.pitch < -89.0f) angles.pitch = -89.0f;

	// Calculate new front vector
	mFront.x = cos(glm::radians(angles.yaw)) * cos(glm::radians(angles.pitch));
	mFront.y = sin(glm::radians(angles.pitch));
	mFront.z = sin(glm::radians(angles.yaw)) * cos(glm::radians(angles.pitch));
	mFront = glm::normalize(mFront);

	// Update right and up vectors
	// Right vector is always orthogonal to the front-worldUp plane
	mRight = glm::normalize(glm::cross(mFront, mWorldUp));
	// Up vector is always orthogonal to the front-right plane
	mUp = glm::normalize(glm::cross(mRight, mFront));
}

glm::mat4 Camera::GetPerspProjMat()
{
	/*
	* template <typename T>
	* GLM_FUNC_DECL tmat4x4<T, defaultp> perspective(
	*	T fovy,
	*	T aspect,
	*	T near,
	*	T far);
	* 
	* Given parameters that define the dimensions of the frustrum,
	* glm::perspective outputs a perspective projection matrix.
	*	- 1st param: FOV in radians, how large the viewspace is
	*	- 2nd param: aspect ratio
	*	- 3rd and 4th params: near and far planes of frustrum
	* 
	* Camera::GetPerspProjMat() always sets near and far coordinates to be 0.1 and 100.
	*/

	return glm::perspective(glm::radians(mFov), mAspectRatio, 0.1f, 100.0f);
}

glm::mat4 Camera::GetOrthoProjMat()
{
	/*
	* template <typename T>
	* GLM_FUNC_DECL tmat4x4<T, defaultp> ortho(
	*	T left,
	*	T right,
	*	T bottom,
	*	T top,
	*	T zNear,
	*	T zFar);
	* 
	* Given parameters that define the dimensions of the frustrum,
	* glm::ortho outputs an orthographic projection matrix.
	*	- 1st and 2nd params: left and right coordinates of frustrum
	*	- 3rd and 4th params: bottom and top coordinates of frustrum
	*	- 5th and 6th params: near and far coordinates of frustrum
	* 
	* Camera::GetOrthoProjMat() always sets near and far coordinates to be 0.1 and 100.
	*/

	return glm::ortho(0.0f, mScreenWidth, 0.0f, mScreenHeight, 0.1f, 100.0f);
}