#ifndef ___VECTOR4F_H___
#define ___VECTOR4F_H___


namespace Math{

	class Vector3f;

	class Vector4f{
	public:

		union{
			float v[4];
			struct{
				float x, y, z, w;
			};
		};
		

		Vector4f();
		Vector4f(float x, float y, float z, float w);
		Vector4f(const float*vec);
		Vector4f(const Vector4f& vec);
		Vector4f(const Vector4f* vec);

		Vector4f(const Vector3f& vec);
		Vector4f(const Vector3f* vec);
		Vector4f(const Vector3f& vec,float w);
		Vector4f(const Vector3f* vec,float w);

		~Vector4f();

		Vector4f operator+(const Vector4f&v) const;
		Vector4f operator+=(const Vector4f&v);

		Vector4f operator-(const Vector4f&v) const;
		Vector4f operator-=(const Vector4f&v);

		float length(void) const;
		float lengthSquard(void) const;

		void normalize(void);
		Vector4f getNormalized(void) const;

		Vector4f operator*(float scalar) const;
		Vector4f operator*=(float scalar);

		Vector4f operator/(float scalar) const;
		Vector4f operator/=(float scalar);

		float dot(const Vector4f&v)const;
		Vector4f cross(const Vector4f&v)const;

		float angle(const Vector4f&v)const;

	};//class Vector4f

	typedef Vector4f Vertex4f;

}//namespace Math


#endif//___VECTOR4F_H___