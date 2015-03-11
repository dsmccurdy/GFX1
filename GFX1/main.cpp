#include <Windows.h>

#include "ISystem.h"
#include "WindowsSystem.h"
#include "OpenGLGraphics.h"
#include "DirectXGraphics.h"
#include "WindowsInput.h"

#include "Assignment1.h"
#include "Box2d.h"
#include "Box2d2.h"
#include "Circle2D.h"
#include "junk.h"
#include "Texture2D.h"

#include "Debug.h"


void WinExit(void){
	std::shared_ptr<System::WindowsSystem::WindowsSystem> sys = std::static_pointer_cast<System::WindowsSystem::WindowsSystem>(System::ISystem::getInstance());
	sys->release();
}//void WinExit(void)


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	std::shared_ptr<System::WindowsSystem::WindowsSystem> ws (new System::WindowsSystem::WindowsSystem());
	System::ISystem::setInstance(ws);

	atexit(WinExit);

	ws->init(lpCmdLine);

	std::shared_ptr<Graphics::DirectX::DirectXGraphics> gfx(new Graphics::DirectX::DirectXGraphics(ws));
	ws->registerSubSystem(gfx);

	std::shared_ptr<Input::WindowsInput::WindowsInput> input(new Input::WindowsInput::WindowsInput(ws));
	ws->registerSubSystem(input);

	ws->initalizeStage1();
	ws->initalizeStage2();

	gfx->setClearColor(0, 0, 0);

	

	/*
	std::shared_ptr<Assignments::Assignment1::Assignment1> a1 ( new Assignments::Assignment1::Assignment1(gfx, ws, input));
	a1->init();
	gfx->addObject(a1);*/

	/*std::shared_ptr<Assignments::Box2D::Box2D> b2d (new Assignments::Box2D::Box2D(gfx, ws));
	gfx->addObject(b2d);*/

	

	/*std::shared_ptr<Assignments::Box2D2::Box2D2> b2d2(new Assignments::Box2D2::Box2D2(gfx, ws));
	b2d2->newBox(100, 200, 300, 400, D3DCOLOR_ARGB(255, 0, 0, 190));
	b2d2->setVelocity(5, 0);
	gfx->addObject(b2d2);*/
	
	/*std::shared_ptr<Assignments::Circle2D::Circle2D> c2d (new Assignments::Circle2D::Circle2D(gfx, ws,nullptr));
	c2d->newCircle(100, 200, 50, 30, D3DCOLOR_ARGB(128, 0, 0, 255),true);
	gfx->addObject(c2d);
	
	std::shared_ptr<Assignments::Circle2D::Circle2D> c2d2(new Assignments::Circle2D::Circle2D(gfx, ws, nullptr));
	c2d2->newCircle(300, 300, 150, 30, D3DCOLOR_ARGB(128, 0, 255, 0), true);
	gfx->addObject(c2d2);
	
	std::shared_ptr<Assignments::Circle2D::Circle2D> c2d3(new Assignments::Circle2D::Circle2D(gfx, ws, nullptr));
	c2d3->newCircle(400, 100, 200, 30, D3DCOLOR_ARGB(128, 255, 0, 0), true);
	gfx->addObject(c2d3);

	std::shared_ptr<Assignments::Circle2D::Circle2D> c2d4(new Assignments::Circle2D::Circle2D(gfx, ws, input));
	c2d4->newCircle(0, 0, 100, 30, D3DCOLOR_ARGB(128, 148, 0, 211), false);
	gfx->addObject(c2d4);*/
	
	std::shared_ptr<Assignments::Junk::Junk> junk(new Assignments::Junk::Junk(gfx, ws, input));
	junk->init();
	gfx->addObject(junk);

	/*std::shared_ptr<Assignments::Texture2D::Texture2D> t1(new Assignments::Texture2D::Texture2D(gfx, "C:\\Users\\mccur_000\\Documents\\Visual Studio 2013\\Projects\\GFX1\\GFX1\\assets\\stuff.png", 10, 10));
	t1->init();
	gfx->addObject(t1);
	*/

	ws->run();

	ws->release();

	return 0;

}//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)