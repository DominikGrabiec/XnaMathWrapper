#pragma once
#ifndef __MATHS_LINE_HPP__
#define __MATHS_LINE_HPP__

#include "Vector3.hpp"

namespace Math
{

	class Line
	{
	public:
		Vector3 start_point;
		Vector3 end_point;

		Line()
		{
		}

		Line(const Vector3& start, const Vector3& end) : start_point(start), end_point(end)
		{
		}

		Line(const Line& line) : start_point(line.start_point), end_point(line.end_point)
		{
		}

		Line& operator = (const Line& line)
		{
			start_point = line.start_point;
			end_point = line.end_point;
			return *this;
		}

		bool operator == (const Line& line) const
		{
			return start_point == line.start_point && end_point == line.end_point;
		}
		bool operator != (const Line& line) const
		{
			return start_point != line.start_point || end_point != line.end_point;
		}


		float length() const;

		float length_squared() const;

		Vector3 vector() const
		{
			return end_point - start_point;
		}

		Vector3 direction() const;

		Vector3 mid_point() const;

		Vector3 point_at(float t) const
		{
			return Vector3::lerp(start_point, end_point, t);
		}

		void extend(float start_amount, float end_amount);
	};

} // namespace Math

#endif // __MATHS_LINE_HPP__
