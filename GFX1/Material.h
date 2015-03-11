#ifndef ___IMATERIAL_H___
#define ___IMATERIAL_H___

namespace Graphics {

	enum CULLMODE {
		CULLMODE_NONE=0,
		CULLMODE_CW=1,
		CULLMODE_CCW=2,
	};

	enum BLEND{
		BLEND_ZERO				= 0,
		BLEND_ONE				= 1,
		BLEND_SRC_COLOR			= 2,
		BLEND_INV_SRC_COLOR		= 3,
		BLEND_SRC_ALPHA			= 4,
		BLEND_INV_SRC_ALPHA		= 5,
		BLEND_DEST_ALPHA		= 6,
		BLEND_INV_DEST_ALPHA	= 7,
		BLEND_DEST_COLOR		= 8,
		BLEND_INV_DEST_COLOR	= 9
	};

	class Material {
	public:

		bool alphaBlendEnable;
		BLEND alphaSourceBlend;
		BLEND alphaDestinationBlend;
		
		bool lightingEnable;

		CULLMODE cullMode;







		Material(){
			alphaBlendEnable = false;
			alphaSourceBlend = BLEND_ONE;
			alphaDestinationBlend = BLEND_ZERO;

			lightingEnable = true;

			cullMode = CULLMODE_CCW;



		};
		~Material(){};

	};
}


#endif//____IMATERIAL_H___