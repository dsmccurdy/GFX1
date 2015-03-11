
#include "DirectXFont.h"
#include "ISystem.h"

namespace Graphics{
	namespace DirectX{

		struct FontData{

			std::shared_ptr<DirectXGraphics>gfx;
			std::shared_ptr<System::ISystem>sys;

			LPD3DXFONT font;
		};
	

		Font::Font(std::shared_ptr<DirectXGraphics>gfx, std::shared_ptr<System::ISystem>sys){
			data = new FontData();
			data->gfx = gfx;
			data->sys = sys;

		}

		Font::~Font(){
			release();
		}

		bool Font::init(const std::string& name, int size){

				D3DXFONT_DESC desc;
				desc.Height = size;
				desc.Width = 0;
				desc.Weight = FW_NORMAL;
				desc.MipLevels = 1;
				desc.Italic = false;
				desc.CharSet = DEFAULT_CHARSET;
				desc.OutputPrecision = OUT_DEFAULT_PRECIS;
				desc.Quality = CLIP_DEFAULT_PRECIS;
				desc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
				MultiByteToWideChar(CP_UTF8, 0, name.c_str(), -1, desc.FaceName, LF_FACESIZE);

				D3DXCreateFontIndirect(data->gfx->getDevice(), &desc, &data->font);

				return true;
		}

		void Font::release(void){
			if (data){
				if (data->font){
					data->font->Release();
					data->font = nullptr;
				}
				delete data;
				data = nullptr;
			}
		}

		void Font::Draw(const std::string& str, int x, int y,DWORD color){
			data->gfx->getDevice()->BeginScene();

			RECT rect;
			rect.left = x;
			rect.top = y;
			rect.right = data->sys->getWindowWidth() - x;
			rect.bottom = data->sys->getWindowHeight() - y;

			data->font->DrawTextA(nullptr, str.c_str(), -1, &rect, DT_TOP | DT_LEFT,color);
			data->gfx->getDevice()->EndScene();

		}
	}
}

