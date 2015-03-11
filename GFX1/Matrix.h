#ifndef ___MATRIX_H___
#define ___MATRIX_H___

namespace Math{

	class Matrix{
	public:
		union {
			float m[4][4];
			struct {
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
		};

		Matrix();
		Matrix(Matrix&);
		Matrix(Matrix*);
		Matrix(float*);
		~Matrix();



		static Matrix createTranslation(float x, float y, float z);
		static Matrix createRotateX(float theta);
		static Matrix createRotateY(float theta);
		static Matrix createRotateZ(float theta);

		//TODO Implment Math::Matrix Mul,Add,Dot,ETC
	};

}//namespace Math

#endif//___MATRIX_H___
