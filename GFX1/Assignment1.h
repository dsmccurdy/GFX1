#ifndef ___ASSIGNMENT1_H___
#define ___ASSIGNMENT1_H___

#include "IGraphics.h"
#include "ISystem.h"
#include "IGfxObject.h"
#include "IKeyCallback.h"
#include "IInput.h"


namespace Assignments {
	namespace Assignment1{
		
		struct Assignment1Data;

		class Assignment1 : 
			public Graphics::IGfxObject, 
			public Input::IKeyCallback,
			public std::enable_shared_from_this<Assignment1>{
		private:
			Assignment1Data*data;
		public:

			Assignment1(std::shared_ptr<Graphics::IGraphics>, std::shared_ptr<System::ISystem>, std::shared_ptr<Input::IInput>);
			virtual ~Assignment1();

			void init(void);
			virtual void draw(void);

			virtual void keyDownCallback(Input::VKEY::VKEY key);

		};//class Assignment1

	}//namespace Assignment1
}//namespace Assignments

#endif//___ASSIGNMENT1_H___