#include "Precompiled.hpp"
#include "Intersect.hpp"
#include "Plane.hpp"
#include "BoundingSphere.hpp"
#include "BoundingBox.hpp"
#include "Ray.hpp"
#include "Line.hpp"

namespace 
{
	float sign(const float n)
	{
		return n < 0.0f ? -1.0f : (n > 0.0f ? 1.0f : 0.0f);
	}

	float square(const float n)
	{
		return n * n;
	}
}

namespace Math
{

	Intersect::LinearResult Intersect::test(const Ray& ray, const Plane& plane)
	{
		const float denom = plane.dot(ray.direction());
		if (std::abs(denom) < FLT_EPSILON) return LinearResult();

		const float num = plane.distance(ray.origin());
		const float t = -(num / denom);
		return LinearResult(t >= 0, t);
	}


	Intersect::LinearResult Intersect::test(const Ray& ray, const BoundingSphere& sphere)
	{
		const Vector3& dir = ray.direction();
		const Vector3 origin = (ray.origin() - sphere.center());
		const float radius = sphere.radius();

		// Test if the origin is within the sphere
		if (origin.length_squared() <= radius * radius) return LinearResult(0.0f);

		// Using Quadratic equation in a numerically (floating point) stable form
		// Taken from http://en.wikipedia.org/wiki/Quadratic_formula (and that was taken from Numerical Recipes in C)
		// Using the formula => q = -0.5 * (b + sign(b) sqrt(b*b - 4*a*c)), with roots => r1 = q/a and r2 = c/q

		// Since the Ray direction is normalised, a = 1.0f, and we can remove it from the equations below
		const float b = 2.0f * origin.dot(dir);
		const float c = origin.dot(origin) - radius * radius;

		const float det = (b * b) - (4.0f * c);
		if (det < 0.0f) return LinearResult();

		const float q = -0.5f * (b + ::sign(b) * ::sqrt(det));
		return LinearResult((q < 0.0f) ? c / q : q);
	}

	Intersect::LinearResult Intersect::test(const Ray& ray, const BoundingBox& box)
	{
		const Vector3& origin = ray.origin();
		const Vector3& direction = ray.direction();
		const Vector3& minimum = box.minimum_corner();
		const Vector3& maximum = box.maximum_corner();

		if (box.contains(origin)) return LinearResult(0.0f);

		float xt = -1.0f;
		float yt = -1.0f;
		float zt = -1.0f;

		if (origin.x < minimum.x && direction.x > 0.0f)
		{
			xt = (minimum.x - origin.x) / direction.x;
		}
		else if (origin.x > maximum.x && direction.x < 0.0f)
		{
			xt = (maximum.x - origin.x) / direction.x;
		}
		if (origin.y < minimum.y && direction.y > 0.0f)
		{
			yt = (minimum.y - origin.y) / direction.y;
		}
		else if (origin.y > maximum.y && direction.y < 0.0f)
		{
			yt = (maximum.y - origin.y) / direction.y;
		}
		if (origin.z < minimum.z && direction.z > 0.0f)
		{
			zt = (minimum.z - origin.z) / direction.z;
		}
		else if (origin.z > maximum.z && direction.z < 0.0f)
		{
			zt = (maximum.z - origin.z) / direction.z;
		}

		Vector3 hitpoint;
		float t = 0.0f;
		bool intersect = false;

		if (xt >= 0.0f)
		{
			hitpoint = ray * xt;
			if ((minimum.y <= hitpoint.y && hitpoint.y <= maximum.y) &&
				(minimum.z <= hitpoint.z && hitpoint.z <= maximum.z))
			{
				if (!intersect || xt < t)
				{
					t = xt;
					intersect = true;
				}
			}
		}
		if (yt >= 0.0f)
		{
			hitpoint = ray * yt;
			if ((minimum.y <= hitpoint.x && hitpoint.x <= maximum.x) &&
				(minimum.z <= hitpoint.z && hitpoint.z <= maximum.z))
			{
				if (!intersect || yt < t)
				{
					t = yt;
					intersect = true;
				}
			}
		}
		if (zt >= 0.0f)
		{
			hitpoint = ray * zt;
			if ((minimum.x <= hitpoint.x && hitpoint.x <= maximum.x) &&
				(minimum.y <= hitpoint.y && hitpoint.y <= maximum.y))
			{
				if (!intersect || zt < t)
				{
					t = zt;
					intersect = true;
				}
			}
		}

		return LinearResult(intersect, t);
	}


	Intersect::LinearResult Intersect::test(const Line& line, const Plane& plane)
	{
		const float denom = plane.dot(line.vector());
		if (std::abs(denom) < FLT_EPSILON) return LinearResult();

		const float num = plane.distance(line.start_point);
		const float t = -(num / denom);
		return LinearResult(0.0f <= t && t <= 1.0f, t);
	}


	Intersect::LinearResult Intersect::test(const Line& line, const BoundingSphere& sphere)
	{
		// Pretty much the same algorithm and formula from the ray/sphere test but with an additional exit condition
		const Vector3 dir = line.vector(); // Note: not normalised
		const Vector3 origin = (line.start_point - sphere.center());
		const float radius = sphere.radius();

		// Test is the start point is within the sphere
		if (origin.length_squared() <= radius * radius) return LinearResult(0.0f);

		// Check that the closest point to the sphere is within its radius
		const float a = dir.length_squared();
		const float d = dir.cross(origin).length_squared() / a;
		if (d > radius * radius) return LinearResult();

		const float b = 2.0f * origin.dot(dir);
		const float c = origin.dot(origin) - radius * radius;

		const float det = (b * b) - (4.0f * a * c);
		if (det < 0.0f) return LinearResult();

		const float q = -0.5f * (b + ::sign(b) * ::sqrt(det));
		return LinearResult((q < 0.0f) ? c / q : q / a);
	}

	Intersect::LinearResult Intersect::test(const Line& line, const BoundingBox& box)
	{
		// Going to take the Line to be a special case of the Ray intersection test
		const Vector3 vector = line.vector();
		const float length = vector.length();
		const Ray ray = Ray(line.start_point, vector);
		const LinearResult result = test(ray, box);

		if (result.intersects() && result.distance() <= length)
		{
			return LinearResult(result.distance() / length);
		}

		return LinearResult();
	}


	Intersect::VolumeResult Intersect::test(const BoundingSphere& sphereA, const BoundingSphere& sphereB)
	{
		if (sphereA == sphereB) return VOLUME_IDENTICAL;

		const float distance = Vector3(sphereB.center() - sphereA.center()).length();
		const float radiusA = sphereA.radius();
		const float radiusB = sphereB.radius();

		if (distance <= radiusA + radiusB)
		{
			if (distance + radiusB <= radiusA)
			{
				return VOLUME_CONTAINS;
			}
			else if (distance + radiusA <= radiusB)
			{
				return VOLUME_CONTAINED;
			}

			return VOLUME_INTERSECT;
		}

		return VOLUME_DISJOINT;
	}

	Intersect::VolumeResult Intersect::test(const BoundingSphere& sphereA, const BoundingBox& boxB)
	{
		const Vector3& box_min = boxB.minimum_corner();
		const Vector3& box_max = boxB.maximum_corner();
		const Vector3& center = sphereA.center();
		const float radius = sphereA.radius();

		const float radius_squared = ::square(radius);
		float intersect_distance = 0.0f;

		if (center.x < box_min.x) intersect_distance += ::square(center.x - box_min.x);
		else if (center.x > box_max.x) intersect_distance += ::square(center.x - box_max.x);
		if (center.y < box_min.y) intersect_distance += ::square(center.y - box_min.y);
		else if (center.y > box_max.y) intersect_distance += ::square(center.y - box_max.y);
		if (center.z < box_min.z) intersect_distance += ::square(center.z - box_min.z);
		else if (center.z > box_max.z) intersect_distance += ::square(center.z - box_max.z);

		if (intersect_distance <= radius_squared)
		{
			const Vector3 radius_vector = Vector3(radius, radius, radius);
			const Vector3 sphere_min = center - radius_vector;
			const Vector3 sphere_max = center + radius_vector;

			if (box_min <= sphere_min && sphere_max <= box_max)
			{
				return VOLUME_CONTAINED;
			}

			const BoundingBox::CornerArray corners = boxB.get_all_corners();
			if (std::all_of(std::begin(corners), std::end(corners), 
				[center, radius_squared](const Vector3& corner) { return Vector3(corner - center).length_squared() <= radius_squared; }))
			{
				return VOLUME_CONTAINS;
			}

			return VOLUME_INTERSECT;
		}

		return VOLUME_DISJOINT;
	}

	Intersect::VolumeResult Intersect::test(const BoundingBox& boxA, const BoundingSphere& sphereB)
	{
		const VolumeResult result = test(sphereB, boxA);
		if (result == VOLUME_CONTAINED) return VOLUME_CONTAINS;
		if (result == VOLUME_CONTAINS) return VOLUME_CONTAINED;
		return result;
	}

	Intersect::VolumeResult Intersect::test(const BoundingBox& boxA, const BoundingBox& boxB)
	{
		if (boxA == boxB) return VOLUME_IDENTICAL;

		const Vector3& minA = boxA.minimum_corner();
		const Vector3& maxA = boxA.maximum_corner();
		const Vector3& minB = boxB.minimum_corner();
		const Vector3& maxB = boxB.maximum_corner();

		if (minA < maxB && minB < maxA)
		{
			if (minA < minB && maxB < maxA)
			{
				return VOLUME_CONTAINS;
			}
			if (minB < minA && maxA < maxB)
			{
				return VOLUME_CONTAINED;
			}

			return VOLUME_INTERSECT;
		}

		return VOLUME_DISJOINT;
	}


	Intersect::PlaneResult Intersect::test(const Plane& plane, const Vector3& point)
	{
		const float distance = plane.distance(point);
		if (distance > 0.0f) return INSIDE_PLANE;
		if (distance < -0.0f) return OUTSIDE_PLANE;
		return INTERSECTS_PLANE;
	}

	Intersect::PlaneResult Intersect::test(const Plane& plane, const BoundingSphere& sphere)
	{
		const float distance = plane.distance(sphere.center());
		const float radius = sphere.radius();
		if (distance > radius) return INSIDE_PLANE;
		if (distance < -radius) return OUTSIDE_PLANE;
		return INTERSECTS_PLANE;
	}

	Intersect::PlaneResult Intersect::test(const Plane& plane, const BoundingBox& box)
	{
		uint_t inside_count = 0;
		uint_t outside_count = 0;

		const BoundingBox::CornerArray corners = box.get_all_corners();
		std::for_each(std::begin(corners), std::end(corners), 
			[&](const Vector3& corner)
			{
				const float distance = plane.distance(corner);
				if (distance < -0.0f)
				{
					++outside_count;
				}
				else
				{
					++inside_count;
				}
			});

		if (inside_count == corners.size())	return INSIDE_PLANE;
		if (outside_count == corners.size()) return OUTSIDE_PLANE;
		return INTERSECTS_PLANE;
	}

} // namespace Math
