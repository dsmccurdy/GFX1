#include <memory>

#include "IInput.h"

namespace Input{

	std::shared_ptr<IInput> IInput::_instance=nullptr;

	std::shared_ptr<IInput> IInput::getDefaultInstance(void){
		return _instance;
	}//IInput* IInput::getDefaultInstance(void)

	void IInput::setDefaultInstance(std::shared_ptr<IInput> instance){
		_instance = instance;
	}//void IInput::getDefaultInstance(IInput*instance)

}//namespace Input