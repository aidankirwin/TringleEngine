#include "Camera.h"

Camera::Camera(float screenWidth, float screenHeight) : 
	mScreenWidth(screenWidth), mScreenHeight(screenHeight)
{
	mAspectRatio = mScreenWidth / mScreenHeight;

	mFov = FOV;
	mUp = UP;
	mFront = FRONT;
	mView = VIEW;
}

Camera::Camera(glm::vec3 position, float screenWidth, float screenHeight, Projection type) :
	mPosition(position), mScreenWidth(screenWidth), mScreenHeight(screenHeight), mView(type)
{
	mAspectRatio = mScreenWidth / mScreenHeight;

	mFov = FOV;
	mUp = UP;
	mFront = FRONT;
}

Camera::Camera(glm::vec3 position, float screenWidth, float screenHeight, float fov, Projection type) :
	mPosition(position), mScreenWidth(screenWidth), mScreenHeight(screenHeight), mView(type), mFov(fov)
{
	mAspectRatio = mScreenWidth / mScreenHeight;

	mUp = UP;
	mFront = FRONT;
}

Camera::Camera(glm::vec3 position, float screenWidth, float screenHeight, float fov, Projection type, EulerAngles angles) :
	mPosition(position), mScreenWidth(screenWidth), mScreenHeight(screenHeight), mView(type), mFov(fov)
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
	// TODO
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
	* ---- Summary ----
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
	* ---- glm::ortho Function Declaration ----
	* template <typename T>
	* GLM_FUNC_DECL tmat4x4<T, defaultp> ortho(
	*	T left,
	*	T right,
	*	T bottom,
	*	T top,
	*	T zNear,
	*	T zFar);
	* 
	* ---- Summary ----
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