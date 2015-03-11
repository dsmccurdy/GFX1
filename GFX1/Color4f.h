#ifndef ___COLOR4F_H___
#define ___COLOR4F_H___


namespace Graphics{
	

	class Color4f{
	private:
		float color[4];

	public:

		Color4f();
		Color4f(float r, float g, float b);
		Color4f(unsigned char r, unsigned char g, unsigned char b);
		Color4f(float a, float r, float g, float b);
		Color4f(unsigned char a,unsigned char r, unsigned char g, unsigned char b);
		
		~Color4f();

		float a(void)const;
		float&a(void);
		float&a(float v);

		float r(void)const;
		float&r(void);
		float&r(float v);

		float g(void)const;
		float&g(void);
		float&g(float v);

		float b(void)const;
		float&b(void);
		float&b(float v);

		float& operator[](int);
		float  operator[](int) const;

		unsigned long toDirectXColor(void)const;


	};//class Color4f

}//namespace Graphics


#endif//___COLOR4F_H___