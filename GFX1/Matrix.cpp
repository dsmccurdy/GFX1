#include "Matrix.h"

#include <memory.h>
#include <math.h>

namespace Math{

	Matrix::Matrix(){
		memset(m, 0, sizeof(m));
		_11 = _22 = _33 = _44 = 1.0f;
	}//Matrix::Matrix()

	Matrix::Matrix(Matrix&matrix){
		memcpy(m, matrix.m, sizeof(m));
	}//Matrix::Matrix(Matrix&matrix)

	Matrix::Matrix(Matrix*matrix){
		memcpy(m, matrix->m, sizeof(m));
	}//Matrix::Matrix(Matrix*matrix)

	Matrix::Matrix(float*matrix){
		memcpy(m, matrix, sizeof(m));
	}//Matrix::Matrix(float*matrix)

	Matrix::~Matrix(){

	}//Matrix::~Matrix()





	Matrix Matrix::createTranslation(float x, float y, float z){
		Matrix m;
		m._41 = x;
		m._42 = y;
		m._43 = z;

		return m;
	}

	Matrix Matrix::createRotateX(float theta){
		Matrix m;

		float s = sinf(theta);
		float c = cosf(theta);

		m._22 = c;
		m._23 = s;
		m._32 = -s;
		m._33 = c;

		return m;
	}//Matrix Matrix::createRotateX(float theta)

	Matrix Matrix::createRotateY(float theta){
		Matrix m;

		float s = sinf(theta);
		float c = cosf(theta);

		//TODO implment Matrix::createRotateY

		return m;
	}//Matrix Matrix::createRotateY(float theta)

	Matrix Matrix::createRotateZ(float theta){
		Matrix m;

		float s = sinf(theta);
		float c = cosf(theta);

		//TODO implement Matrix::createRotateZ

		return m;
	}//Matrix Matrix::createRotateZ(float theta)




}//namespace Math