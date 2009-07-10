/****************************************
Rap3D Engine
File: Rap2d.cpp
Desc: Draw 2d on screen
Author: Bill Hsu (C) All Rights Reserved
http://www.graptor.com
MSN/Email: bill@graptor.com
*****************************************/
#include "Rap3d.h"
#include "Rap2d.h"

void Rap2d::init()
{
if(FAILED(D3DXCreateSprite(m_pRap3d->GetDevice(),&m_pSprite)))
MessageBox(NULL,"Rap2d::init()","Error",MB_OK);

m_Position=D3DXVECTOR3(0.0f,0.0f,0.0f);

M_fScale=1.0f;
D3DXMatrixScaling(&matFace,M_fScale,M_fScale,M_fScale);

}

void Rap2d::Render(IDirect3DTexture9* pTexture,D3DCOLOR Color)
{
if (pTexture==NULL) pTexture=m_pTexture;
m_pSprite->SetTransform(&matFace);
m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
m_pSprite->Draw(m_pTexture,NULL,NULL,&m_Position,Color);
m_pSprite->End();
}

void Rap2d::CloseDown()
{
if(m_pSprite!=NULL)
{
m_pSprite->Release();
m_pSprite=NULL;
}


}