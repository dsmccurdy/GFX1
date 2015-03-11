#ifndef ___IMOUSECALLBACK_H___
#define ___IMOUSECALLBACK_H___

namespace Input{

	enum MouseButton{
		UNKNOWN = 0,
		LEFT = 1,
		MIDDLE = 2,
		RIGHT = 3
	};

	class IMouseCallback{
	public:

		virtual ~IMouseCallback(){};

		virtual void mouseMove(float x, float y) {};

		virtual void mouseButtonDown(MouseButton button) {};
		virtual void mouseButtonUp(MouseButton button) {};

		virtual void mouseWheel(float delta, float absolute) {}
		virtual void mouseHorizontalWheel(float delta, float absolute) {}
	};
}

#endif//___IMOUSECALLBACK_H___