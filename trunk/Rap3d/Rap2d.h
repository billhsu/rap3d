/****************************************
Rap3D Engine
File: Rap2d.h
Desc: Draw 2d on screen
Author: Bill Hsu (C) All Rights Reserved
http://www.graptor.com
MSN/Email: bill@graptor.com
*****************************************/
#ifndef __Rap2d_H__
#define __Rap2d_H__

class Rap3d;

class Rap2d
{

private:
Rap3d *m_pRap3d;
float M_fScale;

public:

D3DXMATRIX matFace;


IDirect3DTexture9* m_pTexture;
ID3DXSprite* m_pSprite;

D3DXVECTOR3 m_Position;

Rap2d(){}
Rap2d(Rap3d *pRap3d):m_pRap3d(pRap3d){init();}
~Rap2d(){CloseDown();}

void SetEngine(Rap3d *pRap3d)
{
m_pRap3d=pRap3d;
init();
}

void init();

void SetPosition(float x,float y)
{
m_Position=D3DXVECTOR3(x,y,0.0f);
}

void SetScale(float scale)
{
M_fScale=scale;
D3DXMatrixScaling(&matFace,M_fScale,M_fScale,M_fScale);
}


void SetTexture(IDirect3DTexture9* pTexture)
{
m_pTexture=pTexture;
}

UINT GetTexWidth()
{
D3DSURFACE_DESC d3dsur_desc;
m_pTexture->GetLevelDesc(0,&d3dsur_desc);
return d3dsur_desc.Width;
}

UINT GetTexHeight()
{
D3DSURFACE_DESC d3dsur_desc;
m_pTexture->GetLevelDesc(0,&d3dsur_desc);
return d3dsur_desc.Height;
}


void Render(IDirect3DTexture9* pTexture=NULL,D3DCOLOR Color=0xffffffff);

void CloseDown();


};
#endif