#ifndef TRAACKBALL_
#define TRACKBALL_
#include"Camera.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include"raySphereIntersection.h"
#include<utility>

/*

* Trackball is binded to a camera object
* Trackball resides in an opengl window 
*/
/*
*FIX ME
*/


 namespace OPENGL
{
	class GLWindow;
	class Trackball
	{
	protected:
		Camera* object_; //  trackball is binded to a camera object

		GLWindow* canvas_;// The trackball resides in a glwindow;

		

		const float radius = 0.5f;  ///< Radius in normalized screen space [0 1]^2
		const float stepsize = 0.05f;

		float trackBallWorldSpaceRadius_;
		glm::vec3 lastNDC_;
		bool isMouseBeingPressedAndHold_;
		glm::quat lastRot_;


	public:
		const glm::vec3& getLookTo() const;
		const glm::vec3& getLookFrom() const;
		const glm::vec3& getLookUp() const;

		void setLookTo(glm::vec3 lookTo);
		void setLookFrom(glm::vec3 lookFrom);
		void setLookUp(glm::vec3 lookUp);
		void setLook(glm::vec3 lookFrom, glm::vec3 lookTo, glm::vec3 lookUp);

		enum class Direction { Up = 0, Left, Down, Right };
		// cal
		glm::vec3 mapNormalizedMousePosToTrackball(const glm::vec2& mousePos, float radius = 1.0f);
		glm::vec3 getWorldSpaceTranslationFromNDCSpace(const glm::vec3& fromNDC,
			const glm::vec3& toNDC);

		std::pair<bool, glm::vec3> getTrackBallIntersection(const glm::vec2 pos) const;

		void Trackball::rotate(glm::vec2 newmouse, glm::vec2 oldmouse);

		void rotateTrackBall(const glm::vec3& fromTrackballPos, const glm::vec3& toTrackballPos);

	public:
		Trackball(Camera* object, GLWindow* window);
		~Trackball();
	};

};



#endif