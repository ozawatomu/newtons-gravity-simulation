#pragma once

#include <math.h>
#include <iostream>

namespace dt{
	class Vector2D{
		long double x, y;
	public:
		Vector2D(long double x = 0.0, long double y = 0.0);
		long double getX();
		long double getY();
		Vector2D to(Vector2D& otherVector2D);
		Vector2D to(Vector2D& otherVector2D, long double& magnitude);
		long double distanceTo(Vector2D& otherVector2D);
		Vector2D multiply(long double multiplier);
		Vector2D divide(long double divisor);
		void operator+=(Vector2D otherVector2D);
		friend std::ostream& operator << (std::ostream& out, const Vector2D& vector2D);
	};
}

