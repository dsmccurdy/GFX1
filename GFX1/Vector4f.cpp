#include "Vector4f.h"
#include "Vector3f.h"

#include <math.h>

namespace Math{

	Vector4f::Vector4f(){
		x = y = z = w = 0.0f;
	}//Vector4f::Vector4f()

	Vector4f::Vector4f(float x, float y, float z, float w){
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}//Vector4f::Vector4f(float x, float y, float z, float w)

	Vector4f::Vector4f(const float* vec){
		x = vec[0];
		y = vec[1];
		z = vec[2];
		w = vec[3];
	}//Vector4f::Vector4f(const float* vec)

	Vector4f::Vector4f(const Vector4f& vec){
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;
	}//Vector4f::Vector4f(const Vector4f& vec)

	Vector4f::Vector4f(const Vector4f* vec){
		x = vec->x;
		y = vec->y;
		z = vec->z;
		w = vec->w;
	}//Vector4f::Vector4f(const Vector4f* vec)

	Vector4f::Vector4f(const Vector3f& vec){
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = 1.0f;
	}//Vector4f::Vector4f(const Vector3f& vec)

	Vector4f::Vector4f(const Vector3f* vec){
		x = vec->x;
		y = vec->y;
		z = vec->z;
		w = 1.0f;
	}//Vector4f::Vector4f(const Vector3f* vec)

	Vector4f::Vector4f(const Vector3f& vec,float w){
		x = vec.x;
		y = vec.y;
		z = vec.z;
		this->w = w;
	}//Vector4f::Vector4f(const Vector3f& vec,float w)

	Vector4f::Vector4f(const Vector3f* vec, float w){
		x = vec->x;
		y = vec->y;
		z = vec->z;
		this->w = w;
	}//Vector4f::Vector4f(const Vector3f* vec,float w)

	Vector4f::~Vector4f(){

	}//Vector4f::~Vector4f()

	Vector4f Vector4f::operator+(const Vector4f&v) const{
		return Vector4f(x + v.x, y + v.y, z + v.z, 1.0f);
	}//Vector4f Vector4f::operator+(const Vector4f&v) const

	Vector4f Vector4f::operator+=(const Vector4f&v){
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}//Vector4f Vector4f::operator+=(const Vector4f&v)

	Vector4f Vector4f::operator-(const Vector4f&v) const{
		return Vector4f(x - v.x, y - v.y, z - v.z, 1.0f);
	}//Vector4f Vector4f::operator-(const Vector4f&v) const

	Vector4f Vector4f::operator-=(const Vector4f&v){
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}//Vector4f Vector4f::operator-=(const Vector4f&v)

	float Vector4f::length(void) const{
		return sqrtf(x*x + y*y + z*z);
	}//float Vector4f::length(void) const

	float Vector4f::lengthSquard(void) const{
		return x*x + y*y + z*z;
	}//float Vector4f::lengthSquard(void) const

	void Vector4f::normalize(void){
		float d = sqrtf(x*x + y*y + z*z);
		if (d != 0.0f){
			x /= d;
			y /= d;
			z /= d;
		}
		w = 1.0f;
	}//void Vector4f::normalize(void)

	Vector4f Vector4f::getNormalized(void) const{
		float d = sqrtf(x*x + y*y + z*z);
		d = (d == 0.0f) ? 1.0f : d;
		return Vector4f(x / d, y / d, z / d, 1.0f);
	}//Vector4f Vector4f::getNormalized(void) const

	Vector4f Vector4f::operator*(float scalar) const{
		return Vector4f(x*scalar, y*scalar, z*scalar, w);
	}//Vector4f Vector4f::operator*(float scalar) const

	Vector4f Vector4f::operator*=(float scalar){
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}//Vector4f Vector4f::operator*=(float scalar)

	Vector4f Vector4f::operator/(float scalar) const{
		return Vector4f(x/scalar, y/scalar, z/scalar, w);
	}//Vector4f Vector4f::operator/(float scalar) const

	Vector4f Vector4f::operator/=(float scalar){
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}//Vector4f Vector4f::operator/=(float scalar)

	float Vector4f::dot(const Vector4f&v)const{
		return x*v.x + y*v.y*z*v.z;
	}//float Vector4f::dot(const Vector4f&v)const

	Vector4f Vector4f::cross(const Vector4f&v)const{
		return Vector4f(y*v.z - x*v.y, z*v.x - x*v.z, x*v.y - y*v.x, 1.0f);
	}//Vector4f Vector4f::cross(const Vector4f&v)const

	float Vector4f::angle(const Vector4f&v)const{
		return acosf(dot(v) / (length()*v.length()));
	}//float Vector4f::angle(const Vector4f&v)const

}//namespace Math