#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "GameObject.h"

enum class CameraMode {
	ORB,
	STATIC,
	DOLLYZOOM
};

class Camera : public GameObject {
public:

	glm::vec3 localVectorUp = glm::vec3(0.f, 1.f, 0.f);
	glm::vec3 target = glm::vec3(0.f);
	const glm::vec3 defaultTarget = glm::vec3(-0.1f, -0.8f, -1.5f);

	float fFov = 45.f;
	float fnear = 0.1f;
	float fFar = 100.f;

	float radius = 5.0f;
	float angle = 0.0f;

	//Orbit
	const float orbitHeight = 3.0f;
	const float fFovOrbit = 45.0f;

	//Static
	const float fFovStatic = 60.0f;

	//dollyZoom
	float dollyZoomTimer = 0.0f;
	const float dollyZoomDuration = 3.0f;
	const float fFovDollyZoom = 60.0f;
	const float fFovDollyZoomStart = 10.0f;
	const float fFovDollyZoomEnd = 60.0f;

	glm::vec3 dollyZoomPos = glm::vec3(0.f);

	Camera();

	CameraMode mode;

	void Update(float dt) override;
	void SetTarget(GameObject* gameObject);
	void SetMode(CameraMode mode);
	void SetPositionFromTarget(glm::vec3 offset);

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix(float aspectRatio) const;
};