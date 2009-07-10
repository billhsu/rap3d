/****************************************
Rap3D Engine
File: Rap3d.cpp
Desc: Basic functions for Engine
Author: Bill Hsu (C) All Rights Reserved
http://www.graptor.com
MSN/Email: bill@graptor.com
*****************************************/

#include "Rap3d.h"

Rap3d::Rap3d()
{

}

Rap3d::~Rap3d()
{
CloseDown();
}

bool Rap3d::Init(HINSTANCE hInstance,//Window's instance
		  LRESULT (CALLBACK* WndProc)(HWND, UINT, WPARAM, LPARAM),//WNDPROC
		  int width,
		  int height,
		  bool windowed,//Full screen or not
		  const TCHAR*strCaption,//Caption
		  LPCTSTR IconName,//Icon
		  float fovy,float Aspect,float zn,float zf)//Perspective

{
m_hInstance=hInstance;

m_iWidth=width;
m_iHeight=height;

WNDCLASS wc;
wc.style         = CS_HREDRAW | CS_VREDRAW;
wc.lpfnWndProc   = (WNDPROC)WndProc; 
wc.cbClsExtra    = 0;
wc.cbWndExtra    = 0;
wc.hInstance     = hInstance;
wc.hIcon         = LoadIcon(m_hInstance, IconName);
wc.hCursor       = LoadCursor(0, IDC_ARROW);
wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
wc.lpszMenuName  = 0;
wc.lpszClassName = strCaption;

if( !RegisterClass(&wc) ) 
{
MessageBox(0, "RegisterClass() - FAILED", 0, 0);
return false;
}
		
HWND hwnd = 0;
int SysWidth=GetSystemMetrics(SM_CXSCREEN);
int SysHeight=GetSystemMetrics(SM_CYSCREEN);
hwnd = CreateWindow(strCaption, strCaption, 
WS_EX_TOPMOST|WS_SYSMENU,
SysWidth/2-width/2, SysHeight/2-height/2, width, height,
0 /*parent hwnd*/, 0 /* menu */, hInstance, 0 /*extra*/); 

if( !hwnd )
{
MessageBox(0, "CreateWindow() - FAILED", 0, 0);
return false;
}

ShowWindow(hwnd, SW_SHOW);
UpdateWindow(hwnd);

HRESULT hr = 0;

// Step 1: Create the IDirect3D9 object.
m_pIDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

if( !m_pIDirect3D )
{
MessageBox(0, "Direct3DCreate9() - FAILED", 0, 0);
return false;
}

// Step 2: Check for hardware vp.

D3DCAPS9 caps;
m_pIDirect3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

int vp = 0;
if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
else
vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

// Step 3: Fill out the D3DPRESENT_PARAMETERS structure.
 
D3DPRESENT_PARAMETERS d3dpp;
d3dpp.BackBufferWidth            = width;
d3dpp.BackBufferHeight           = height;
d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;
d3dpp.BackBufferCount            = 1;
d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;
d3dpp.MultiSampleQuality         = 0;
d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
d3dpp.hDeviceWindow              = hwnd;
d3dpp.Windowed                   = windowed;
d3dpp.EnableAutoDepthStencil     = true; 
d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;
d3dpp.Flags                      = 0;
d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

// Step 4: Create the device.

hr = m_pIDirect3D->CreateDevice(
D3DADAPTER_DEFAULT, // primary adapter
D3DDEVTYPE_HAL,         // device type
hwnd,               // window associated with device
vp,                 // vertex processing
&d3dpp,             // present parameters
&m_pIDirect3DDevice);            // return created device

if( FAILED(hr) )
{
// try again using a 16-bit depth buffer
d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		
hr = m_pIDirect3D->CreateDevice(
D3DADAPTER_DEFAULT,
D3DDEVTYPE_HAL,
hwnd,
vp,
&d3dpp,
&m_pIDirect3DDevice);

if( FAILED(hr) )
{
m_pIDirect3D->Release(); // done with d3d9 object
MessageBox(0, "CreateDevice() - FAILED", 0, 0);
return false;
}
}

m_pIDirect3D->Release(); // done with d3d9 object
m_pIDirect3D=NULL;

// Turn on the zbuffer
m_pIDirect3DDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
// Turn on ambient lighting 
m_pIDirect3DDevice->SetRenderState( D3DRS_AMBIENT, 0xffffffff );


m_pIDirect3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
m_pIDirect3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
m_pIDirect3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);



D3DXMatrixPerspectiveFovLH( &matProj, fovy, Aspect, zn, zf );
m_pIDirect3DDevice->SetTransform( D3DTS_PROJECTION, &matProj );

vEyeVec=D3DXVECTOR3(0.0f,0.0f,-1.0f);
vLookatVec=D3DXVECTOR3(0.0f,0.0f,0.0f);
vUpVec=D3DXVECTOR3(0.0f,1.0f,0.0f);
D3DXMatrixLookAtLH( &matView, &vEyeVec, &vLookatVec, &vUpVec );
m_pIDirect3DDevice->SetTransform( D3DTS_VIEW, &matView );
m_font=NULL;
SetFont();

font_rect.top=0;
font_rect.left=0;
font_rect.right=width;
font_rect.bottom=height;
return true;
}

void Rap3d::SetFont(const TCHAR*fontname,//Name of font.For example "Times New Roman"
			 unsigned height)//The Height of th font
{
if(m_font)
{
m_font->Release();
m_font=NULL;
}
D3DXCreateFont(m_pIDirect3DDevice,
			   height,0,FW_NORMAL,1,false,DEFAULT_CHARSET,
			   OUT_DEFAULT_PRECIS,ANTIALIASED_QUALITY,
			   DEFAULT_PITCH|FF_DONTCARE,
			   fontname,&m_font);
}

void Rap3d::DrawText(const TCHAR* strText,LPRECT pRect,DWORD dwColor)
{
if (pRect==NULL) pRect=&font_rect;
if(m_font)
{
m_font->DrawText(NULL,strText,-1,pRect,DT_LEFT|DT_NOCLIP,dwColor);
}

}

void Rap3d::SndCommand(const TCHAR* command)
{
mciSendString(command,NULL,0,m_hWnd);

}




void Rap3d::CloseDown()
{
if(m_font)
{
m_font->Release();
m_font=NULL;
}

if(m_pIDirect3DDevice!=NULL)
{
m_pIDirect3DDevice->Release();
m_pIDirect3DDevice=NULL;
}

}





