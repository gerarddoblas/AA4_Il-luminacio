#include "Camera.h"

Camera::Camera()
	: GameObject()
{
	mode = CameraMode::ORB;
	transform->position = glm::vec3(0.0f, orbitHeight, 0.0f);
	target = defaultTarget;
}

void Camera::Update(float dt)
{
	switch (mode)
	{
	case CameraMode::ORB:
	{
		angle += speed * dt;
		transform->position = glm::vec3(target.x + radius * cos(angle), transform->position.y, target.z + radius * sin(angle));
	}
		break;

	case CameraMode::STATIC:
		break;

	case CameraMode::DOLLYZOOM:
	{
		dollyZoomTimer += dt;

		//Clampeo la duración para simplemente poner si es más grande que 1
		float _clamp = glm::clamp(dollyZoomTimer / dollyZoomDuration, 0.0f, 1.0f);
		fFov = fFovDollyZoomStart + (fFovDollyZoomEnd - fFovDollyZoomStart) * _clamp;

		transform->position = dollyZoomPos + (target - dollyZoomPos) * _clamp;

		if (_clamp >= 1.0f)
		{
			SetMode(CameraMode::ORB);
			target = defaultTarget;
		}
	}
		break;
	default:
		break;
	}
}

void Camera::SetTarget(GameObject* gameObject)
{
	if (gameObject != nullptr)
		target = gameObject->GetTransform()->position;
}

void Camera::SetMode(CameraMode newMode)
{
	mode = newMode;

	switch (mode)
	{
	case CameraMode::ORB:
		fFov = fFovOrbit;
		transform->position.y = orbitHeight;
		break;

	case CameraMode::STATIC:
		fFov = fFovStatic;
		break;

	case CameraMode::DOLLYZOOM:
		fFov = fFovDollyZoomStart;
		dollyZoomTimer = 0.0f;
		dollyZoomPos = transform->position;
		break;
	default:
		mode = CameraMode::ORB;
		break;
	}
}

void Camera::SetPositionFromTarget(glm::vec3 offset) { transform->position = target + offset; }

glm::mat4 Camera::GetViewMatrix() const { return glm::lookAt(transform->position, target, localVectorUp); }

glm::mat4 Camera::GetProjectionMatrix(float aspectRatio) const { return glm::perspective(glm::radians(fFov), aspectRatio, fnear, fFar); }
