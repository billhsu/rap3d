/****************************************
Rap3D Engine
File: Rap3d.h
Desc: Basic functions for Engine
Author: Bill Hsu (C) All Rights Reserved
http://www.graptor.com
MSN/Email: bill@graptor.com
*****************************************/

#ifndef __Rap3dH__
#define __Rap3dH__


#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include<mmsystem.h>

class CD3DFont;

class Rap3d{

private:
HINSTANCE m_hInstance;

int m_iWidth;
int m_iHeight;
IDirect3D9*  m_pIDirect3D;
IDirect3DDevice9*  m_pIDirect3DDevice;
CD3DFont* m_pFont;
HWND  m_hWnd;

public:

D3DXMATRIXA16 matProj;
D3DXMATRIXA16 matView;


Rap3d();
~Rap3d();

D3DXVECTOR3 vEyeVec,vLookatVec,vUpVec;//You can get the camera vector from here

//Init Rap3d
bool Init(HINSTANCE hInstance,//Window's instance
		  LRESULT (CALLBACK* WndProc)(HWND, UINT, WPARAM, LPARAM),//WNDPROC
		  int width,
		  int height,
		  bool windowed,//Full screen or not
		  const TCHAR*strCaption,//Caption
		  LPCTSTR IconName=IDI_APPLICATION,//Icon
		  float fovy=D3DX_PI/4,float Aspect=1.0f,float zn=1.0f,float zf=1000.0f);//Perspective


//Clear Screen
bool ClearScreen(D3DCOLOR c=0x00000000)
{
if(FAILED(m_pIDirect3DDevice->Clear(0,NULL,D3DCLEAR_TARGET,c,1.0f,0))) return false;

return true;
}

//Clear Z-Buffur
bool ClearZBuffer(float z=1.0f)
{
if(FAILED(m_pIDirect3DDevice->Clear(0,NULL,D3DCLEAR_ZBUFFER,0,z,0))) return false;

return true;
}

//Clear both Screen and Z-Buffer
bool Clear(D3DCOLOR c=0x00000000,float z=1.0f)
{
if(FAILED(m_pIDirect3DDevice->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,c, z, 0))) 
{
MessageBox(NULL,"Clear()","Error",MB_OK);
return false;
}
return true;
}
//Set The Camera
void SetCamera(D3DXVECTOR3 eyePos,D3DXVECTOR3 aimPos,D3DXVECTOR3 up=D3DXVECTOR3(0.0f,1.0f,0.0f))
{
vEyeVec=eyePos;
vLookatVec=aimPos;
vUpVec=up;
D3DXMatrixLookAtLH( &matView, &vEyeVec, &vLookatVec, &vUpVec );
m_pIDirect3DDevice->SetTransform( D3DTS_VIEW, &matView );
}



//Begin Render
bool BeginRender()
{
if(FAILED(m_pIDirect3DDevice->BeginScene())) 
{MessageBox(NULL,"BeginRender()","Error",MB_OK);
return false;}

return true;
}
//End Render
bool EndRender()
{
m_pIDirect3DDevice->EndScene();

m_pIDirect3DDevice->Present(NULL,NULL,NULL,NULL);

return true;

}

//music command
void SndCommand(const TCHAR* command);

//Set Font
void SetFont(const TCHAR*fontname="Times New Roman",//Name of font.For example "Times New Roman"
			 DWORD dwHeight=16,DWORD dwFlags=0);//The Height of th font

//Draw text on the 3d device
void DrawText(float x,float y,//Position to draw text
			  const TCHAR* strText,//Text to draw
			  DWORD dwColor=0x00000000,//Color
			  DWORD dwFlags=0);//D3DFONT_BLOD,D3DFONT_ITALIC,D3DFONT_ZENABLE

//Get Device pointer
inline IDirect3DDevice9* GetDevice(){return m_pIDirect3DDevice;}

inline int GetHeight(){return m_iWidth;}
inline int GetWidth(){return m_iHeight;}


template<class T>void Release(T t)
{
if(t){
t->Release();
t=NULL;
}

}

template<class T>void Delete(T t)
{
if(t){
delete t;
t=NULL;
}

}


//Close Rap3d
void CloseDown();
};

#endif //__Rap3dH__