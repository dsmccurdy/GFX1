#define _CRT_SECURE_NO_WARNINGS
#include "Debug.h"
#include <Windows.h>
#include <stdio.h>

namespace Debug{
	void Print(const char* message, ...){
#ifdef _DEBUG

		if (message){

			va_list args;
			va_start(args, message);

			int size = vsnprintf(NULL, 0, message, args);
			if (size > 0){}
			char*buffer = new char[size + 1];
			vsnprintf(buffer, size + 1, message, args);
			OutputDebugStringA(buffer);
			delete[]buffer;

			va_end(args);
		}//if (message)
#endif //_DEBUG

	}//void Print(const char* message, ...)

}//namesapce Debug