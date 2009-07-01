/****************************************
Rap3D Engine
File: RapBillBoard.h
Desc: BillBoard
Author: Bill Hsu (C) All Rights Reserved
http://www.graptor.com
MSN/Email: bill@graptor.com
*****************************************/
#ifndef __RapBillBoard_H__
#define __RapBillBoard_H__

class Rap3d;

class RapBillBoard
{

private:
float M_fScale;

public:

Rap3d *m_pRap3d;
IDirect3DTexture9* m_pTexture;
ID3DXSprite* m_pSprite;

D3DXVECTOR3 m_Position;

D3DXMATRIX matPosition;
D3DXMATRIX matFace;

RapBillBoard(){}
RapBillBoard(Rap3d *pRap3d):m_pRap3d(pRap3d){init();}
~RapBillBoard(){CloseDown();}

void SetEngine(Rap3d *pRap3d)
{
m_pRap3d=pRap3d;
init();
}

void init();

void SetTexture(IDirect3DTexture9* pTexture)
{
m_pTexture=pTexture;
}

void SetPosition(float x=0.0f,float y=0.0f,float z=0.0f)
{
m_Position=D3DXVECTOR3(x,y,z);
D3DXMatrixTranslation(&matPosition,m_Position.x,y,z);
}

void SetScale(float scale)
{
M_fScale=scale;
D3DXMatrixScaling(&matFace,M_fScale,-M_fScale,M_fScale);
}

void Render(IDirect3DTexture9* pTexture=NULL,D3DCOLOR Color=0xffffffff);

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


void CloseDown();


};

#endif