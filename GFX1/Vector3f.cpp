#include "Vector3f.h"
#include "Vector4f.h"

#include <math.h>

namespace Math{

	Vector3f::Vector3f(){
		x = y = z = 0.0f;
	}//Vector3f::Vector3f()

	Vector3f::Vector3f(float x, float y, float z){
		this->x = x;
		this->y = y;
		this->z = z;

	}//Vector3f::Vector3f(float x, float y, float z)

	Vector3f::Vector3f(const float* vec){
		x = vec[0];
		y = vec[1];
		z = vec[2];
	}//Vector3f::Vector3f(const float* vec)

	Vector3f::Vector3f(const Vector3f& vec){
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}//Vector3f::Vector3f(const Vector3f& vec)

	Vector3f::Vector3f(const Vector3f* vec){
		x = vec->x;
		y = vec->y;
		z = vec->z;
	}//Vector3f::Vector3f(const Vector3f* vec)

	Vector3f::Vector3f(const Vector4f& vec){
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	Vector3f::Vector3f(const Vector4f* vec){
		x = vec->x;
		y = vec->y;
		z = vec->z;
	}

	Vector3f::~Vector3f(){
		
	}//Vector3f::~Vector3f()

	Vector3f Vector3f::operator+(const Vector3f&v) const{
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}//Vector3f Vector3f::operator+(Vector3f&v)

	Vector3f Vector3f::operator+=(const Vector3f&v){
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}//Vector3f Vector3f::operator+=(Vector3f&v)

	Vector3f Vector3f::operator-(const Vector3f&v) const{
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}//Vector3f Vector3f::operator+(Vector3f&v)

	Vector3f Vector3f::operator-=(const Vector3f&v){
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}//Vector3f Vector3f::operator+=(Vector3f&v)

	float Vector3f::length(void) const{
		return sqrtf(x*x + y*y + z*z);
	}//float Vector3f::length(void) const

	float Vector3f::lengthSquard(void) const{
		return x*x + y*y + z*z;
	}//float Vector3f::lengthSquard(void) const

	void Vector3f::normalize(void){
		float d = sqrtf(x*x + y*y + z*z);
		if (d != 0.0f){
			x /= d;
			y /= d;
			z /= d;
		}
	}//void Vector3f::normalized(void)

	Vector3f Vector3f::getNormalized(void) const{
		float d = sqrtf(x*x + y*y + z*z);
		d = (d == 0.0f) ? 1.0f : d;
		return Vector3f(x / d, y / d, z / d);
	}//Vector3f Vector3f::getNormalized(void) const

	Vector3f Vector3f::operator*(float scalar) const{
		return Vector3f(x*scalar, y*scalar, z*scalar);
	}//Vector3f Vector3f::operator*(float scalar) const

	Vector3f Vector3f::operator*=(float scalar){
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}//Vector3f Vector3f::operator*=(float scalar)

	Vector3f Vector3f::operator/(float scalar) const{
		return Vector3f(x/scalar, y/scalar, z/scalar);
	}//Vector3f Vector3f::operator/(float scalar) const

	Vector3f Vector3f::operator/=(float scalar){
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}//Vector3f Vector3f::operator/=(float scalar)

	float Vector3f::dot(const Vector3f&v)const{
		return x*v.x + y*v.y*z*v.z;
	}//float Vector3f::dot(Vector3f&v)const

	Vector3f Vector3f::cross(const Vector3f&v)const{
		return Vector3f(y*v.z - x*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
	}//Vector3f Vector3f::cross(const Vector3f&v)const

	float Vector3f::angle(const Vector3f&v)const{
		return acosf(dot(v) / (length()*v.length()) );
	}//float Vector3f::angle(const Vector3f&v)const

}//namespace Math