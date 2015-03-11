#include "Color4f.h"

#include <d3d9.h>

namespace Graphics{

	Color4f::Color4f(){
		color[0] = color[1] = color[2] = color[3] = 0.0f;
	}//Color4f::Color4f()

	Color4f::Color4f(float r, float g, float b){
		color[0] = 1.0f;
		color[1] = r;
		color[2] = g;
		color[3] = b;
	}//Color4f::Color4f(float r, float g, float b)

	Color4f::Color4f(unsigned char r, unsigned char g, unsigned char b){
		color[0] = 1.0f;
		color[1] = ((float)r)/255.0f;
		color[2] = ((float)g) / 255.0f;
		color[3] = ((float)b) / 255.0f;
	}//Color4f::Color4f(unsigned char r, unsigned char g, unsigned char b)

	Color4f::Color4f(float a, float r, float g, float b){
		color[0] = a;
		color[1] = r;
		color[2] = g;
		color[3] = b;
	}//Color4f::Color4f(float a, float r, float g, float b)

	Color4f::Color4f(unsigned char a, unsigned char r, unsigned char g, unsigned char b){
		color[0] = ((float)a) / 255.0f;
		color[1] = ((float)r) / 255.0f;
		color[2] = ((float)g) / 255.0f;
		color[3] = ((float)b) / 255.0f;
	}//Color4f::Color4f(unsigned char a, unsigned char r, unsigned char g, unsigned char b)

	Color4f::~Color4f(){

	}//Color4f::~Color4f()

	float Color4f::a(void)const{
		return color[0];
	}//float Color4f::a(void)const

	float&Color4f::a(void){
		return color[0];
	}//float&Color4f::a(void)

	float&Color4f::a(float v){
		return color[0]=v;
	}//float&Color4f::a(float v)

	float Color4f::r(void)const{
		return color[1];
	}//float Color4f::r(void)const

	float&Color4f::r(void){
		return color[1];
	}//float&Color4f::r(void)

	float&Color4f::r(float v){
		return color[1]=v;
	}//float&Color4f::r(float v)

	float Color4f::g(void)const{
		return color[2];
	}//float Color4f::g(void)const

	float&Color4f::g(void){
		return color[2];
	}//float&Color4f::g(void)

	float&Color4f::g(float v){
		return color[2]=v;
	}//float&Color4f::g(float v)

	float Color4f::b(void)const{
		return color[3];
	}//float Color4f::b(void)const

	float&Color4f::b(void){
		return color[3];
	}//float&Color4f::b(void)

	float&Color4f::b(float v){
		return color[3]=v;
	}//float&Color4f::b(float v)

	float& Color4f::operator[](int i){
		return color[i];
	}//float& Color4f::operator[](int)

	float  Color4f::operator[](int i) const{
		return color[i];
	}//float  Color4f::operator[](int) const

	unsigned long Color4f::toDirectXColor(void) const{
		return D3DCOLOR_ARGB((DWORD)(color[0] * 255), (DWORD)(color[1] * 255), (DWORD)(color[2] * 255), (DWORD)(color[3] * 255));
	}//unsigned long Color4f::toDirectXColor(void) const

};//namespace Graphics