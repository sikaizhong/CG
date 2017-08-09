#define GLM_FORCE_SWIZZLE 
#include"Camera.h"
using namespace glm;

namespace OPENGL {

	Camera::Camera(vec3 lookFrom, vec3 lookTo, vec3 lookUp, float nearPlane, float farPlane)
		: lookFrom_(lookFrom)
		, lookTo_(lookTo)
		, lookUp_(lookUp)
		, nearPlaneDist_(nearPlane)
		, farPlaneDist_(farPlane)
		, invalidViewMatrix_(true)
		, invalidProjectionMatrix_(true) {}

	const mat4& Camera::getViewMatrix() const {
		if (invalidViewMatrix_) {
			viewMatrix_ = glm::lookAt(lookFrom_, lookTo_, lookUp_); // get view matrix
			inverseViewMatrix_ = glm::inverse(viewMatrix_);
			invalidViewMatrix_ = false;
		}
		return viewMatrix_;
	}

	const mat4& Camera::getProjectionMatrix() const {
		if (invalidProjectionMatrix_) {
			projectionMatrix_ = calculateProjectionMatrix();
			inverseProjectionMatrix_ = glm::inverse(projectionMatrix_);
			invalidProjectionMatrix_ = false;
		}
		return projectionMatrix_;
	}

	const mat4& Camera::getInverseViewMatrix() const {
		if (invalidViewMatrix_) getViewMatrix();
		return inverseViewMatrix_;
	}

	const mat4& Camera::getInverseProjectionMatrix() const {
		if (invalidProjectionMatrix_) getProjectionMatrix();
		return inverseProjectionMatrix_;
	}

	vec3 Camera::getWorldPosFromNormalizedDeviceCoords(const vec3& ndcCoords) const {
		vec4 clipCoords = getClipPosFromNormalizedDeviceCoords(ndcCoords);
		vec4 eyeCoords = getInverseProjectionMatrix() * clipCoords;
		vec4 worldCoords = getInverseViewMatrix() * eyeCoords;
		worldCoords /= worldCoords.w;
		return worldCoords.xyz();
	}

	vec4 Camera::getClipPosFromNormalizedDeviceCoords(const vec3& ndcCoords) const {
		float clipW = projectionMatrix_[2][3] /
			(ndcCoords.z - (projectionMatrix_[2][2] / projectionMatrix_[3][2]));
		return vec4(ndcCoords * clipW, clipW);
	}

	vec3 Camera::getNormalizedDeviceFromNormalizedScreenAtFocusPointDepth(
		const vec2& normalizedScreenCoord) const {
		// Default to using focus point for depth
		vec4 lookToClipCoord = getProjectionMatrix() * getViewMatrix() * vec4(getLookTo(), 1.f);
		return vec3(2.f * normalizedScreenCoord - 1.f, lookToClipCoord.z / lookToClipCoord.w);
	}

	bool Camera::equalTo(const Camera& other) const {
		return !(glm::any(glm::notEqual(lookFrom_, other.lookFrom_)) |
			glm::any(glm::notEqual(lookTo_, other.lookTo_)) |
			(nearPlaneDist_ != other.nearPlaneDist_) | (farPlaneDist_ != other.farPlaneDist_));
	}

	PerspectiveCamera::PerspectiveCamera(vec3 lookFrom, vec3 lookTo, vec3 lookUp, float nearPlane,
		float farPlane, float fieldOfView, float aspectRatio)
		: Camera(lookFrom, lookTo, lookUp, nearPlane, farPlane)
		, fovy_(fieldOfView)
		, aspectRatio_(aspectRatio){};

	PerspectiveCamera* PerspectiveCamera::clone() const { return new PerspectiveCamera(*this); }

	bool PerspectiveCamera::update(const Camera* source) {
		if (auto perspectiveCamera = dynamic_cast<const PerspectiveCamera*>(source)) {
			*this = *perspectiveCamera;
			return true;
		}
		else {
			return false;
		}
	}


	bool operator==(const PerspectiveCamera& lhs, const PerspectiveCamera& rhs) {
		return !(lhs.equalTo(rhs) | (lhs.fovy_ != rhs.fovy_) | (lhs.aspectRatio_ != rhs.aspectRatio_));
	}

	bool operator!=(const PerspectiveCamera& lhs, const PerspectiveCamera& rhs) {
		return (lhs.equalTo(rhs) | (lhs.fovy_ != rhs.fovy_) | (lhs.aspectRatio_ != rhs.aspectRatio_));
	}



	OrthographicCamera::OrthographicCamera(vec3 lookFrom, vec3 lookTo, vec3 lookUp, float nearPlane,
		float farPlane, vec4 frustum)
		: Camera(lookFrom, lookTo, lookUp, nearPlane, farPlane), frustum_(frustum){};

	OrthographicCamera* OrthographicCamera::clone() const { return new OrthographicCamera(*this); }

	bool OrthographicCamera::update(const Camera* source) {
		if (auto orthographicCamera = dynamic_cast<const OrthographicCamera*>(source)) {
			*this = *orthographicCamera;
			return true;
		}
		else {
			return false;
		}
	}




	bool operator==(const OrthographicCamera& lhs, const OrthographicCamera& rhs) {
		return !(lhs.equalTo(rhs) | glm::any(glm::notEqual(lhs.frustum_, rhs.frustum_)));
	}

	bool operator!=(const OrthographicCamera& lhs, const OrthographicCamera& rhs) {
		return (lhs.equalTo(rhs) | glm::any(glm::notEqual(lhs.frustum_, rhs.frustum_)));
	}

	float OrthographicCamera::getAspectRatio() const {
		// Left, right, bottom, top view volume
		const float width{ frustum_.y - frustum_.x };
		const float height{ frustum_.w - frustum_.z };
		return width / height;
	}

	void OrthographicCamera::setAspectRatio(float val) {
		// Left, right, bottom, top view volume
		const float width{ frustum_.y - frustum_.x };
		const float height{ width / val };
		frustum_.z = -height / 2.0f;
		frustum_.w = +height / 2.0f;
		invalidateProjectionMatrix();
	}




	SkewedPerspectiveCamera::SkewedPerspectiveCamera(vec3 lookFrom, vec3 lookTo, vec3 lookUp, float nearPlane,
		float farPlane, vec4 frustum, vec2 frustumOffset)
		: Camera(lookFrom, lookTo, lookUp, nearPlane, farPlane), frustum_(frustum), frustumSkewOffset_(frustumOffset){};

	SkewedPerspectiveCamera* SkewedPerspectiveCamera::clone() const { return new SkewedPerspectiveCamera(*this); }

	bool SkewedPerspectiveCamera::update(const Camera* source) {
		if (auto skewedPerspectiveCamera = dynamic_cast<const SkewedPerspectiveCamera*>(source)) {
			*this = *skewedPerspectiveCamera;
			return true;
		}
		else {
			return false;
		}
	}




	bool operator==(const SkewedPerspectiveCamera& lhs, const SkewedPerspectiveCamera& rhs) {
		return !(lhs.equalTo(rhs) | glm::any(glm::notEqual(lhs.frustum_, rhs.frustum_)) |
			glm::any(glm::notEqual(lhs.frustumSkewOffset_, rhs.frustumSkewOffset_)));
	}

	bool operator!=(const SkewedPerspectiveCamera& lhs, const SkewedPerspectiveCamera& rhs) {
		return (lhs.equalTo(rhs) | glm::any(glm::notEqual(lhs.frustum_, rhs.frustum_)) |
			glm::any(glm::notEqual(lhs.frustumSkewOffset_, rhs.frustumSkewOffset_)));
	}

	float SkewedPerspectiveCamera::getAspectRatio() const {
		// Left, right, bottom, top view volume
		const float width{ frustum_.y - frustum_.x };
		const float height{ frustum_.w - frustum_.z };
		return width / height;
	}

	void SkewedPerspectiveCamera::setAspectRatio(float val) {
		// Left, right, bottom, top view volume
		const float width{ frustum_.y - frustum_.x };
		const float height{ width / val };
		frustum_.z = -height / 2.0f;
		frustum_.w = +height / 2.0f;
		invalidateProjectionMatrix();
	}

	mat4 SkewedPerspectiveCamera::calculateProjectionMatrix() const {
		vec4 f(frustum_);
		float left = f.x + frustumSkewOffset_.x;
		float right = (f.x + frustumSkewOffset_.x) + (f.y - f.x);
		float up = f.z + frustumSkewOffset_.y;
		float down = (f.z + frustumSkewOffset_.y) + (f.w - f.z);
		return glm::frustum(left, right, up, down, nearPlaneDist_, farPlaneDist_);
	};

}  // namespace
