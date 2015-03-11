#include "IGraphics.h"

namespace Graphics{

	std::shared_ptr<IGraphics> IGraphics::s_instance = nullptr;

	std::shared_ptr<IGraphics> IGraphics::getInstance(void){
		return s_instance;
	}//std::shared_ptr<IGraphics> IGraphics::getInstance(void)

	void IGraphics::setInstance(std::shared_ptr<IGraphics> inst){
		s_instance = inst;
	}//void IGraphics::setInstance(std::shared_ptr<IGraphics> inst)

	IGraphics::IGraphics(){


	}//IGraphics::IGraphics()

	IGraphics::~IGraphics(){

	}//IGraphics::~IGraphics()

}//namespace Graphics