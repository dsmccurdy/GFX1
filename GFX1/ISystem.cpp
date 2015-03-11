#include "ISystem.h"

namespace System{

	std::shared_ptr<ISystem> ISystem::_inst = nullptr;

	std::shared_ptr<ISystem> ISystem::getInstance(void){
		return _inst;
	}//std::shared_ptr<ISystem> ISystem::getInstance(void)

	void ISystem::setInstance(std::shared_ptr<ISystem> inst){
		_inst = inst;
	}//void ISystem::setInstance(std::shared_ptr<ISystem> inst)


	ISystem::ISystem(){

	}//ISystem::ISystem()

	ISystem::~ISystem(){

	}//ISystem::~ISystem()

}//namespace System