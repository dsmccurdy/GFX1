#ifndef ___IGFXOBJECT_H___
#define ___IGFXOBJECT_H___

namespace Graphics{

	class IGfxObject{
	public:

		IGfxObject(){};
		virtual ~IGfxObject(){};

		virtual void draw(void) = 0;

	};//class IGfxObject

}//namespace Graphics

#endif//___IGFXOBJECT_H___