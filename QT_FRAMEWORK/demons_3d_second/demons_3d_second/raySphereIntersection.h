
#ifndef RAYSPHEREINTERSECTION_H
#define RAYSPHEREINTERSECTION_H

#include<utility>
namespace OPENGL {

	/**
	* \brief Intersects a ray with a sphere.
	*
	* @param sphereCenter Center of sphere
	* @param radius Sphere radius
	* @param origin Ray origin
	* @param direction Ray direction
	* @param t0 Parameterized start position along ray
	* @param t1 Parameterized end position along ray
	* @return True if intersecting, otherwise false. result.second will contain the point of
	* intersection along the ray if intersecting.
	*/

	template <typename T, glm::precision P>
	std::pair<bool, float> raySphereIntersection(const glm::tvec3<T, P>& sphereCenter,
		const T radius, const glm::tvec3<T, P>& origin,
		const glm::tvec3<T, P>& direction, const T t0,
		const T t1) {
		glm::tvec3<T, P> m = origin - sphereCenter;
		T b = glm::dot(m, direction);
		T c = glm::dot(m, m) - radius * radius;
		// Exit if ray origin is outside of sphere and pointing away from sphere
		if (c > 0.f && b > 0.f) return{ false, T{ 0.0 } };

		T discr = b * b - c;
		// Negative discriminant means that ray misses sphere
		if (discr < 0.0) return{ false, T{ 0.0 } };

		// Ray intersects sphere, compute first intersection point (smallest t1)
		T tHit = -b - glm::sqrt(discr);
		// If t is negative, ray started inside sphere, so we clamp it to zero
		if (tHit < 0.f) tHit = T{ 0.0 };
		// Check if intersection was behind start point
		if (tHit >= t0 && tHit <= t1) {
			return{ true, tHit };
		}
		else {
			return{ false, T{ 0.0 } };
		}
	}

} // namespace

#endif // IVW_RAYSPHEREINTERSECTION_H

