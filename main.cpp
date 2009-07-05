#include"Rap3d.h"
#include "RaptorMission.h"
RaptorMission rapmision;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE prevInstance, 
				   PSTR cmdLine,
				   int showCmd)
{
Rap3d *rap3d=NULL;
rap3d=new Rap3d;

rap3d->Init(hInstance,&WndProc,800,600,true,"Hello Rap3d!",
			IDI_APPLICATION,D3DX_PI/3,1.33f,1.0f,450.0f);

rap3d->Clear();
rap3d->BeginRender();
rap3d->SetFont("Comic Sans MS",28);
rap3d->DrawText(300.0f,250.0f,"Loading....",0xffff0000,0);
rap3d->EndRender();
rapmision.SetEngine(rap3d);
rapmision.enter();

return 0;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_DESTROY:

		PostQuitMessage(0);
		break;
		
	case WM_KEYDOWN:
		if( wParam == VK_ESCAPE )
			DestroyWindow(hwnd);
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}