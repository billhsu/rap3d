/****************************************
Rap3D Engine
File: RapTexManager.cpp
Desc: Manage Texture
Author: Bill Hsu (C) All Rights Reserved
http://www.graptor.com
MSN/Email: bill@graptor.com
*****************************************/
#include "Rap3d.h"
#include "RapTexManager.h"

void RapTexManager::LoadTex(std::string FileName,std::string TexName,D3DCOLOR alpha)
{
IDirect3DTexture9* pTexture;

if (alpha!=NULL)
{
if(FAILED(D3DXCreateTextureFromFileEx(m_pRap3d->GetDevice(),
   FileName.c_str(),D3DX_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,0,
   D3DFMT_A8R8G8B8,D3DPOOL_MANAGED,D3DX_FILTER_TRIANGLE,
   D3DX_FILTER_TRIANGLE,alpha,NULL,NULL,
   &pTexture)))
MessageBox(NULL,"Wrong Texture File","Error",MB_OK);

}
else
{
if(FAILED(D3DXCreateTextureFromFile(m_pRap3d->GetDevice(),
   FileName.c_str(),
   &pTexture)))
MessageBox(NULL,"Wrong Texture File","Error",MB_OK);

}

if (TexName=="") TexName=FileName;

iter=TexManager.find(TexName);
if(TexManager.end()==iter)
{
TexManager.insert(TexMap::value_type(TexName, pTexture));
++iCount;
}
else
{
MessageBox(NULL,"Load the same texture","Error",MB_OK);
}

}

IDirect3DTexture9* RapTexManager::GetTex(std::string TexName)
{
iter=TexManager.find(TexName);
if(TexManager.end()!=iter)
{
m_pTexture=iter->second;
return m_pTexture;
}
else
{
MessageBox(NULL,"No Such texture","Error",MB_OK);
return NULL;
}

}

void RapTexManager::Remove(std::string TexName)
{
iter=TexManager.find(TexName);
if(TexManager.end()!=iter)
{
TexManager.erase(TexName);
}
else
{
MessageBox(NULL,"No Such texture","Error",MB_OK);
}
}

void RapTexManager::CloseDown()
{
iter=TexManager.begin();
for(;iter!=TexManager.end();++iter )
{
if(iter->second!=NULL)
{
iter->second->Release();
iter->second=NULL;
}


}
TexManager.clear();
}