#include "Vector2D.h"

namespace dt{
	Vector2D::Vector2D(long double x, long double y){
		this->x = x;
		this->y = y;
	}

	long double Vector2D::getX(){
		return this->x;
	}

	long double Vector2D::getY(){
		return this->y;
	}

	Vector2D Vector2D::to(Vector2D& otherVector2D){
		return Vector2D(otherVector2D.x - x, otherVector2D.y - y);
	};

	Vector2D Vector2D::to(Vector2D& otherVector2D, long double& magnitude){
		long double scalar = sqrt(pow(magnitude, 2) / (pow(otherVector2D.x - x, 2) + pow(otherVector2D.y - y, 2)));
		return Vector2D(scalar * (otherVector2D.x - x), scalar * (otherVector2D.y - y));
	};

	long double Vector2D::distanceTo(Vector2D& otherVector2D){
		return sqrt(pow(otherVector2D.x - x, 2) + pow(otherVector2D.y - y, 2));
	};

	Vector2D Vector2D::multiply(long double multiplier){
		return Vector2D(x * multiplier, y * multiplier);
	};

	Vector2D Vector2D::divide(long double divisor){
		return Vector2D(x / divisor, y / divisor);
	};

	void Vector2D::operator+=(Vector2D otherVector2D){
		x += otherVector2D.x;
		y += otherVector2D.y;
	};

	std::ostream& operator<<(std::ostream& out, const Vector2D& vector2D){
		out << "x = " << vector2D.x << "; y = " << vector2D.y << std::endl;
		return out;
	};
}