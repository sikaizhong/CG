
#ifndef CAMERA_H
#define CAMERA_H
#include<glm/glm.hpp>
#include<glm/detail/type_vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

/*
*FIX ME
*/

namespace OPENGL {

	/**
	* \brief Base class for cameras.
	* Override this class to set your own projection matrix.
	* @see PerspectiveCamera
	* @see OrthographicCamera
	*/
	class Camera {
	public:
		/**
		* \brief Default parameters creates a right handed coordinate system
		* with camera looking towards the negative z-axis.
		* with X = (1, 0, 0), Y = (0, 1, 0), Z = (0, 0, -1)
		*
		* @param lookFrom Camera position (eye)
		* @param lookTo Camera focus point (center)
		* @param lookUp Camera up direction
		*/
		Camera(glm::vec3 lookFrom = glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3 lookTo = glm::vec3(0.0f),
			glm::vec3 lookUp = glm::vec3(0.0f, 1.0f, 0.0f), float nearPlane = 0.01f,
			float farPlane = 10000.0f);
		virtual ~Camera() = default;
		Camera(const Camera& other) = default;
		Camera& operator=(const Camera& other) = default;

		virtual Camera* clone() const = 0;
		virtual bool update(const Camera* source) = 0;

		glm::vec3& getLookFrom() { return lookFrom_; }
		const glm::vec3& getLookFrom() const;
		void setLookFrom(glm::vec3 val);

		glm::vec3& getLookTo() { return lookTo_; }
		const glm::vec3& getLookTo() const;
		void setLookTo(glm::vec3 val);

		glm::vec3& getLookUp() { return lookUp_; }
		const glm::vec3& getLookUp() const;
		void setLookUp(glm::vec3 val);

		virtual float getAspectRatio() const = 0;
		virtual void setAspectRatio(float val) = 0;

		/**
		* \brief Get unnormalized direction of camera: lookTo - lookFrom
		*
		* @return Unnormalized direction of camera
		*/
		glm::vec3 getDirection() const { return lookTo_ - lookFrom_; }

		float getNearPlaneDist() const;
		/**
		* \brief Set distance to the near plane from lookFrom.
		*
		* @param val Distance
		*/
		void setNearPlaneDist(float val);

		float getFarPlaneDist() const;
		/**
		* \brief Set distance to the far plane from lookFrom.
		*
		* @param val Distance
		*/
		void setFarPlaneDist(float val);

		const glm::mat4& getViewMatrix() const;
		const glm::mat4& getProjectionMatrix() const;
		const glm::mat4& getInverseViewMatrix() const;
		const glm::mat4& getInverseProjectionMatrix() const;

		/**
		* \brief Convert from normalized device coordinates (xyz in [-1 1]) to world coordinates.
		*
		* @param ndcCoords Coordinates in [-1 1]
		* @return World space position
		*/
		glm::vec3 getWorldPosFromNormalizedDeviceCoords(const glm::vec3& ndcCoords) const;

		/**
		* \brief Convert from normalized device coordinates (xyz in [-1 1]) to clip coordinates,
		* where z value of -1 correspond to the near plane and 1 to the far plane.
		* Coordinates outside of the [-1 1]^3 range will be clipped.
		*
		* @param ndcCoords xyz clip-coordinates in [-1 1]^3, and the clip w-coordinate used for
		* perspective division.
		* @return Clip space position
		*/
		glm::vec4 getClipPosFromNormalizedDeviceCoords(const glm::vec3& ndcCoords) const;

		glm::vec3 getNormalizedDeviceFromNormalizedScreenAtFocusPointDepth(
			const glm::vec2& normalizedScreenCoord) const;



		bool equalTo(const Camera& other) const;
		/**
		* \brief Calculate and return the projection matrix for the camera.
		*
		* Implement this function to provide your own projection computation functionality.
		* For example orthogonal or perspective projection.
		* This function will be called when the projection matrix is invalid.
		* @see PerspectiveCamera
		* @see OrthographicCamera
		*/
		virtual glm::mat4 calculateProjectionMatrix() const = 0;
		void invalidateViewMatrix();
		void invalidateProjectionMatrix();


	protected:

		glm::vec3 lookFrom_;
		glm::vec3 lookTo_;
		glm::vec3 lookUp_;

		float nearPlaneDist_;  ///< Distance to the near plane from lookFrom.
		float farPlaneDist_;   ///< Distance to the far plane from lookFrom.

		// Make mutable to allow then to be changed even though they are called from const function.
		// This allows us to perform lazy evaluation.
		mutable bool invalidViewMatrix_;  // check whether  view matrix is valid
		mutable bool invalidProjectionMatrix_;
		mutable glm::mat4 viewMatrix_;
		mutable glm::mat4 projectionMatrix_;
		mutable glm::mat4 inverseViewMatrix_;
		mutable glm::mat4 inverseProjectionMatrix_;
	};

	class  PerspectiveCamera : public Camera {
	public:
		PerspectiveCamera(glm::vec3 lookFrom = glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3 lookTo = glm::vec3(0.0f),
			glm::vec3 lookUp = glm::vec3(0.0f, 1.0f, 0.0f), float nearPlane = 0.01f,
			float farPlane = 10000.0f, float fieldOfView = 60.f, float aspectRatio = 1.f);
		virtual ~PerspectiveCamera() = default;
		PerspectiveCamera(const PerspectiveCamera& other) = default;
		PerspectiveCamera& operator=(const PerspectiveCamera& other) = default;
		virtual PerspectiveCamera* clone() const override;
		virtual bool update(const Camera* source) override;
		//virtual void configureProperties(CompositeProperty* comp) override;


		friend bool operator==(const PerspectiveCamera& lhs, const PerspectiveCamera& rhs);
		friend bool operator!=(const PerspectiveCamera& lhs, const PerspectiveCamera& rhs);

		float getFovy() const;
		void setFovy(float val);
		virtual float getAspectRatio() const override;
		virtual void setAspectRatio(float val) override;

	protected:
		virtual glm::mat4 calculateProjectionMatrix() const override;

		float fovy_;
		float aspectRatio_;
	};

	bool operator==(const PerspectiveCamera& lhs, const PerspectiveCamera& rhs);
	bool operator!=(const PerspectiveCamera& lhs, const PerspectiveCamera& rhs);

	/**
	* \class OrthographicCamera
	*
	* \brief Camera with no perspective projection.
	* Objects far away will appear as large as objects close.
	* @see Camera
	* @see OrthographicCamera
	*/
	class  OrthographicCamera : public Camera {
	public:
		OrthographicCamera(glm::vec3 lookFrom = glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3 lookTo = glm::vec3(0.0f),
			glm::vec3 lookUp = glm::vec3(0.0f, 1.0f, 0.0f), float nearPlane = 0.01f,
			float farPlane = 10000.0f, glm::vec4 frustum = glm::vec4(-01, 10, -10, 10));
		virtual ~OrthographicCamera() = default;
		OrthographicCamera(const OrthographicCamera& other) = default;
		OrthographicCamera& operator=(const OrthographicCamera& other) = default;
		virtual OrthographicCamera* clone() const override;
		virtual bool update(const Camera* source) override;
		//virtual void configureProperties(CompositeProperty* comp) override;

		friend bool operator==(const OrthographicCamera& lhs, const OrthographicCamera& rhs);
		friend bool operator!=(const OrthographicCamera& lhs, const OrthographicCamera& rhs);

		const glm::vec4& getFrustum() const;
		/**
		* \brief Left, right, bottom, top view volume
		*
		* Set view frustum used for projection matrix calculation.
		*/
		void setFrustum(glm::vec4 val);
		virtual float getAspectRatio() const override;
		virtual void setAspectRatio(float val) override;

	protected:
		virtual glm::mat4 calculateProjectionMatrix() const override;

		// Left, right, bottom, top view volume
		glm::vec4 frustum_;
	};

	bool operator==(const OrthographicCamera& lhs, const OrthographicCamera& rhs);
	bool operator!=(const OrthographicCamera& lhs, const OrthographicCamera& rhs);

	/**
	* \brief Camera with off axis perspective projection.
	*
	* The camera with unsymmetrical frustum for stereo in VR
	* Kooima, Robert. "Generalized perspective projection." School of Elect. Eng. and Computer Science
	* (2008): 1-7.
	* @see Camera
	* @see SkewedPerspectiveCamera
	*/
	class  SkewedPerspectiveCamera : public Camera {
	public:
		SkewedPerspectiveCamera(glm::vec3 lookFrom = glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3 lookTo = glm::vec3(0.0f),
			glm::vec3 lookUp = glm::vec3(0.0f, 1.0f, 0.0f), float nearPlane = 0.01f,
			float farPlane = 10000.0f, glm::vec4 frustum = glm::vec4(-01, 10, -10, 10),
			glm::vec2 frustumOffset = glm::vec2(0.0f, 0.0f));
		virtual ~SkewedPerspectiveCamera() = default;
		SkewedPerspectiveCamera(const SkewedPerspectiveCamera& other) = default;
		SkewedPerspectiveCamera& operator=(const SkewedPerspectiveCamera& other) = default;
		virtual SkewedPerspectiveCamera* clone() const override;
		virtual bool update(const Camera* source) override;
		//virtual void configureProperties(CompositeProperty* comp) override;

		friend bool operator==(const SkewedPerspectiveCamera& lhs, const SkewedPerspectiveCamera& rhs);
		friend bool operator!=(const SkewedPerspectiveCamera& lhs, const SkewedPerspectiveCamera& rhs);

		const glm::vec4& getFrustum() const;
		/**
		* \brief Left, right, bottom, top view volume
		*
		* Set view frustum used for projection matrix calculation.
		*/
		void setFrustum(glm::vec4 val);

		const glm::vec2& getFrustumOffset() const;
		/**
		* \brief Left, right, bottom, top view volume
		*
		* Set view frustum used for projection matrix calculation.
		*/
		void setFrustumOffset(glm::vec2 val);
		virtual float getAspectRatio() const override;
		virtual void setAspectRatio(float val) override;

	protected:
		virtual glm::mat4 calculateProjectionMatrix() const override;

		// Left, right, bottom, top view volume
		glm::vec4 frustum_;
		glm::vec2 frustumSkewOffset_;
	};

	bool operator==(const SkewedPerspectiveCamera& lhs, const SkewedPerspectiveCamera& rhs);
	bool operator!=(const SkewedPerspectiveCamera& lhs, const SkewedPerspectiveCamera& rhs);


	// Implementation details

	inline const glm::vec3& Camera::getLookFrom() const { return lookFrom_; }
	inline void Camera::setLookFrom(glm::vec3 val) {
		lookFrom_ = val;
		invalidateViewMatrix();
	}
	inline const glm::vec3& Camera::getLookTo() const { return lookTo_; }
	inline void Camera::setLookTo(glm::vec3 val) {
		lookTo_ = val;
		invalidateViewMatrix();
	}
	inline const glm::vec3& Camera::getLookUp() const { return lookUp_; }
	inline void Camera::setLookUp(glm::vec3 val) {
		lookUp_ = val;
		invalidateViewMatrix();
	}

	inline float Camera::getNearPlaneDist() const { return nearPlaneDist_; }
	inline void Camera::setNearPlaneDist(float val) {
		nearPlaneDist_ = val;
		invalidateProjectionMatrix();
	}
	inline float Camera::getFarPlaneDist() const { return farPlaneDist_; }
	inline void Camera::setFarPlaneDist(float val) {
		farPlaneDist_ = val;
		invalidateProjectionMatrix();
	}

	inline void Camera::invalidateViewMatrix() { invalidViewMatrix_ = true; }
	inline void Camera::invalidateProjectionMatrix() { invalidProjectionMatrix_ = true; }

	inline float PerspectiveCamera::getFovy() const { return fovy_; }
	inline void PerspectiveCamera::setFovy(float val) {
		fovy_ = val;
		invalidateProjectionMatrix();
	}
	inline float PerspectiveCamera::getAspectRatio() const { return aspectRatio_; }
	inline void PerspectiveCamera::setAspectRatio(float val) {
		aspectRatio_ = val;
		invalidateProjectionMatrix();
	}

	inline glm::mat4 PerspectiveCamera::calculateProjectionMatrix() const {
		return glm::perspective(glm::radians(fovy_), aspectRatio_, nearPlaneDist_, farPlaneDist_);
	};

	inline const glm::vec4& OrthographicCamera::getFrustum() const { return frustum_; }

	inline void OrthographicCamera::setFrustum(glm::vec4 val) {
		frustum_ = val;
		invalidateProjectionMatrix();
	}

	inline glm::mat4 OrthographicCamera::calculateProjectionMatrix() const {
		return glm::ortho(frustum_.x, frustum_.y, frustum_.z, frustum_.w, nearPlaneDist_,
			farPlaneDist_);
	};

	inline const glm::vec4& SkewedPerspectiveCamera::getFrustum() const { return frustum_; }

	inline void SkewedPerspectiveCamera::setFrustum(glm::vec4 val) {
		frustum_ = val;
		invalidateProjectionMatrix();
	}

	inline const glm::vec2& SkewedPerspectiveCamera::getFrustumOffset() const { return frustumSkewOffset_; }
	inline void SkewedPerspectiveCamera::setFrustumOffset(glm::vec2 offset) {
		frustumSkewOffset_ = offset;
		invalidateProjectionMatrix();
	}

}  // namespace

#endif  // IVW_CAMERA_H
