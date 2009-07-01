/****************************************
Rap3D Engine
File: RapBillBoard.cpp
Desc: BillBoard
Author: Bill Hsu (C) All Rights Reserved
http://www.graptor.com
MSN/Email: bill@graptor.com
*****************************************/
#include "Rap3d.h"
#include "RapBillBoard.h"

void RapBillBoard::init()
{
if(FAILED(D3DXCreateSprite(m_pRap3d->GetDevice(),&m_pSprite)))
MessageBox(NULL,"RapBillBoard::init()","Error",MB_OK);
M_fScale=1.0f;
D3DXMatrixScaling(&matFace,M_fScale,-M_fScale,M_fScale);
}

void RapBillBoard::Render(IDirect3DTexture9* pTexture,D3DCOLOR Color)
{
m_pSprite->SetTransform(&matFace);
m_pSprite->SetWorldViewLH(&matPosition,&m_pRap3d->matView);
if (pTexture==NULL) pTexture=m_pTexture;
m_pSprite->Begin(D3DXSPRITE_BILLBOARD|D3DXSPRITE_ALPHABLEND);
m_pSprite->Draw(m_pTexture,NULL,NULL,NULL,Color);
m_pSprite->End();
}

void RapBillBoard::CloseDown()
{
if(m_pSprite!=NULL)
{
m_pSprite->Release();
m_pSprite=NULL;
}


}