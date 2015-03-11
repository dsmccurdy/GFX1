#ifndef ___VECTOR3F_H___
#define ___VECTOR3F_H___


namespace Math{

	class Vector4f;

	class Vector3f{
	public:

		union{
			float v[3];
			struct{
				float x, y, z;
			};
		};

		Vector3f();
		Vector3f(float x, float y, float z);
		Vector3f(const float*vec);
		Vector3f(const Vector3f& vec);
		Vector3f(const Vector3f* vec);
		Vector3f(const Vector4f& vec);
		Vector3f(const Vector4f* vec);

		~Vector3f();

		Vector3f operator+(const Vector3f&v) const;
		Vector3f operator+=(const Vector3f&v);

		Vector3f operator-(const Vector3f&v) const;
		Vector3f operator-=(const Vector3f&v);

		float length(void) const;
		float lengthSquard(void) const;

		void normalize(void);
		Vector3f getNormalized(void) const;

		Vector3f operator*(float scalar) const;
		Vector3f operator*=(float scalar);

		Vector3f operator/(float scalar) const;
		Vector3f operator/=(float scalar);

		float dot(const Vector3f&v)const;
		Vector3f cross(const Vector3f&v)const;

		float angle(const Vector3f&v)const;

	};//class Vector3f

	typedef Vector3f Vertex3f;

}//namespace Math


#endif//___VECTOR4F_H___