#include "Trackball.h"

#define GLM_FORCE_SWIZZLE 
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/detail/type_vec4.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include <glm/gtx/quaternion.hpp>

#include"GLWindow.h"
namespace OPENGL
{
	Trackball::Trackball(Camera* object,GLWindow* glwindow)
	{

		object_ = object;
		canvas_ = glwindow;
		isMouseBeingPressedAndHold_ = false;
		lastNDC_ = glm::vec3(0.0);
		
	}



	const glm::vec3& Trackball::getLookTo() const
	{
		return object_->getLookTo();
	}
	const glm::vec3& Trackball::getLookFrom() const
	{
		return object_->getLookFrom();
	}
	const glm::vec3& Trackball::getLookUp() const
	{
		return object_->getLookUp();
	}


	void Trackball::setLookTo(glm::vec3 lookTo)
	{
		object_->setLookTo(lookTo);
	}
	void Trackball::setLookFrom(glm::vec3 lookFrom)
	{
		object_->setLookFrom(lookFrom);
	}
	void Trackball::setLookUp(glm::vec3 lookUp)
	{
		object_->setLookUp(lookUp);
	}
	void Trackball::setLook(glm::vec3 lookFrom, glm::vec3 lookTo, glm::vec3 lookUp)
	{
		setLookTo(lookTo);
		setLookFrom(lookFrom);
		setLookUp(lookUp);

	}



	void Trackball::rotateTrackBall(const glm::vec3& fromTrackballPos, const glm::vec3& toTrackballPos)
	{
		
		const glm::vec3 view = glm::normalize(getLookFrom() - getLookTo());
		const glm::vec3 right = glm::cross(getLookUp(), view);
		// Transform virtual sphere coordinates to view space
		const glm::vec3 Pa =
			fromTrackballPos.x * right + fromTrackballPos.y * getLookUp() + fromTrackballPos.z * view;
		const glm::vec3 Pc = toTrackballPos.x * right + toTrackballPos.y * getLookUp() + toTrackballPos.z * view;
		// Compute the rotation that transforms coordinates
		const glm::quat quaternion = glm::quat(glm::normalize(Pc), glm::normalize(Pa));
		setLook(getLookTo() + glm::rotate(quaternion, getLookFrom() - getLookTo()), getLookTo(),
			glm::rotate(quaternion, getLookUp()));

	}

	glm::vec3 Trackball::mapNormalizedMousePosToTrackball(const glm::vec2& mousePos, float r) // mouse postion should be normalized to[-1,1]^2
	{ // project to sphere

		// set x and y to lie in interval [-r, r]
		const glm::vec2 centerOffset =glm:: vec2(2.f * mousePos.x - 1.f, 2.f * (1.f - mousePos.y) - 1.f);
		const float norm = glm::length2(centerOffset);
		float z = 0;
		// Mapping according to Holroyds trackball
		// Piece-wise sphere + hyperbolic sheet
		if (norm <= r * r / (2.0f)) {  // Spherical Region
			z = r * r - norm;
			z = z > 0.0f ? sqrtf(z) : 0.0f;
		}
		else {  // Hyperbolic Region - for smooth z values
			z = ((r * r) / (2.0f * sqrtf(norm)));
		}

		return glm::vec3(centerOffset.x, centerOffset.y, z);

	}

	glm::vec3 Trackball::getWorldSpaceTranslationFromNDCSpace(const glm::vec3& fromNDC,  // normalized device coord
		const glm::vec3& toNDC)
	{
		const glm::vec3 prevWorldPos = object_->getWorldPosFromNormalizedDeviceCoords(glm::vec3(fromNDC));
		const glm::vec3 worldPos = object_->getWorldPosFromNormalizedDeviceCoords(toNDC);

		std::cout << "world pos:" << prevWorldPos.x << " " << prevWorldPos.y << " " << prevWorldPos.z << std::endl;
		return worldPos - prevWorldPos;
	}




	std::pair<bool, glm::vec3> Trackball::getTrackBallIntersection(const glm::vec2 pos) const {
		const auto rayOrigin = object_->getWorldPosFromNormalizedDeviceCoords(glm::vec3(pos.x, pos.y, -1.f));
		const auto direction = glm::normalize(
			object_->getWorldPosFromNormalizedDeviceCoords(glm::vec3(pos.x, pos.y, 0.f)) - rayOrigin);
		const auto res = raySphereIntersection(getLookTo(), trackBallWorldSpaceRadius_, rayOrigin,
			direction, 0.0f, std::numeric_limits<float>::max());
		return{ res.first, rayOrigin + direction * res.second };
	}


	void Trackball::rotate(glm::vec2 newmouse, glm::vec2 oldmouse) // mouse normalized coord
	{
		/* Project the points onto the virtual trackball,
		* then figure out the axis of rotation, which is the cross
		* product of P1-P2 and O-P1 (O is the center of the ball, 0,0,0)
		* Note:  This is a deformed trackball -- it is a trackball in the center,
		* but is deformed into a hyperbolic sheet of rotation away from the
		* center (projectToSphere does that job).  This particular function was
		* chosen after trying out several variations.
		*
		* It is assumed that the arguments to this routine are in the range
		* (-1.0 ... 1.0) */



		const auto& to = getLookTo();
		const auto& from = getLookFrom();
		const auto& up = getLookUp();
		
		if (newmouse == oldmouse)
		{
			return; // do nothing, the mouse does not move
		}


		/* First, figure out z-coordinates for projection of P1 and P2 to deformed sphere */
		glm::vec3 p1 = mapNormalizedMousePosToTrackball(oldmouse);


		glm::vec3 p2 = mapNormalizedMousePosToTrackball(newmouse);

		/* Now, find the axis we are going to rotate about*/
		glm::vec3 axis = cross(p2, p1);

		/*... and calculate the angle phi between the two vectors which is the
		angle we need to rotate about*/
		glm::vec3 d = p1 - p2;
		float t = length(d) / (0.2f);

		/* avoid problems with out-of-control values... */
		if (t > 1.0f) t = 1.0f;
		if (t < -1.0f) t = -1.0f;

		float phi = 2.f * asinf(t);

		// change axis from view coord to world coord;


		glm::mat4 MV = object_->getViewMatrix();

		MV[0][3] = MV[1][3] = MV[2][3] = MV[3][0] = MV[3][1] = MV[3][2] = 0;
		MV[3][3] = 1;
		MV = glm::inverse(MV);
		glm::vec4 axis_ = glm::vec4(axis.x, axis.y, axis.z, 1)*MV;
		axis = glm::vec3(axis_.x / axis_.w, axis_.y / axis_.w, axis_.z / axis_.w);

		glm::quat q;

		q.x = axis.x * sin(phi / 2);
		q.y = axis.y * sin(phi / 2);
		q.z = axis.z * sin(phi / 2);
		q.w = cos(phi / 2);

		q = q / glm::length(q); // must have this step
		setLook(glm::rotate(q, from),  to, glm::rotate(q, up));


		lastRot_ = q;


		canvas_->update();
	}



	Trackball::~Trackball()
	{


	}
}

