#include "Assignment1.h"
#include "Debug.h"

namespace Assignments {
	namespace Assignment1{

		struct Assignment1Data{
			std::shared_ptr<Graphics::IGraphics> gfx = nullptr;
			std::shared_ptr<System::ISystem> system = nullptr;
			std::shared_ptr<Input::IInput> input = nullptr;

			Graphics::Material material;
			
		};// struct Assignment1Data

		Assignment1::Assignment1(std::shared_ptr<Graphics::IGraphics> gfx, std::shared_ptr<System::ISystem> system, std::shared_ptr<Input::IInput> input){
			data = new Assignment1Data();

			data->gfx = gfx;
			data->system = system;
			data->input = input;

			
			

		}//Assignment1::Assignment1(IGraphics*gfx, ISystem*system)

		Assignment1::~Assignment1(){
			if (data){

				//data->input->unregisterKeyboardCallback(shared_from_this());
				//data->gfx->removeObject(shared_from_this());

				delete data;
				data = nullptr;
			}
		}//Assignment1::~Assignment1()

		void Assignment1::init(void){

			data->input->registerKeyboardCallback(shared_from_this());

		}//void Assignment1::init()

		

		void Assignment1::draw(void){
			data->gfx->setMaterial(data->material);


		}//void Assignment1::draw(void)

		void Assignment1::keyDownCallback(Input::VKEY::VKEY key){
			switch (key){
			case Input::VKEY::VKEY_R:
				data->gfx->setClearColor(1.0f, 0.0f, 0.0f);
				break;
			case Input::VKEY::VKEY_G:
				data->gfx->setClearColor(0.0f, 1.0f, 0.0f);
				break;
			case Input::VKEY::VKEY_B:
				data->gfx->setClearColor(0.0f, 0.0f, 1.0f);
				break;
			}//switch (key)
		}//void Assignment1::keyDownCallback(VKEY key)

	}//namespace Assignment1
}//namespace Assignments