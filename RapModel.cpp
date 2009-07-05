/****************************************
Rap3D Engine
File: RapModel.cpp
Desc: Model Ctrl
Author: Bill Hsu (C) All Rights Reserved
http://www.graptor.com
MSN/Email: bill@graptor.com
*****************************************/
#include "Rap3d.h"
#include "RapModel.h"
#include <string>
#include <iostream>

bool RapModel::LoadXfile(const TCHAR* filename)
{
HRESULT hr=0;
std::string strtmp,strtmp1,strtmp2;

int l=(int)strlen(filename);
int i;

for(i=l-1;i>=0;i--)
{
if(filename[i]=='\\')
break;
}

if(i==-1)
{
strtmp="";
}

else 
{

for(int j=0;j<=i;++j)
{
strtmp+=filename[j];
}

}


ID3DXBuffer* adjBuffer=0;
ID3DXBuffer* mtrlBuffer=0;
numMtrls=0;
hr=D3DXLoadMeshFromX(filename,D3DXMESH_MANAGED,
					 m_pRap3d->GetDevice(),&adjBuffer,&mtrlBuffer,
					 0,&numMtrls,&m_pMesh);
if(FAILED(hr)) 
{MessageBox(NULL,"LoadXfile()  D3DXLoadMeshFromX","Error",MB_OK);
return false;}

if(mtrlBuffer!=0 && numMtrls!=0)
{
D3DXMATERIAL* mtrls=(D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();
m_Mtrls=new D3DMATERIAL9[numMtrls];
if(m_Mtrls==NULL) 
{MessageBox(NULL,"LoadXfile()  m_Mtrls","Error",MB_OK);
return false;}

m_pTextures=new IDirect3DTexture9*[numMtrls];
if(m_pTextures==NULL) 
{MessageBox(NULL,"LoadXfile()  m_pTextures","Error",MB_OK);
return false;}


for(DWORD i=0;i<numMtrls;i++)
{
m_Mtrls[i]=mtrls[i].MatD3D;
m_Mtrls[i].Ambient=m_Mtrls[i].Diffuse;
m_pTextures[i]=NULL;

if (mtrls[i].pTextureFilename!=NULL && 
	lstrlen(mtrls[i].pTextureFilename)>0)
{
strtmp1=mtrls[i].pTextureFilename;
strtmp2=strtmp.c_str()+strtmp1;

if(FAILED(D3DXCreateTextureFromFile(m_pRap3d->GetDevice(),
	strtmp2.c_str(),
   &m_pTextures[i])))
{
MessageBox(NULL,"LoadXfile() D3DXCreateTextureFromFile","Error",MB_OK);
return false;

}
}
}


hr = m_pMesh->OptimizeInplace(		
D3DXMESHOPT_ATTRSORT |
D3DXMESHOPT_COMPACT  |
D3DXMESHOPT_VERTEXCACHE,
(DWORD*)adjBuffer->GetBufferPointer(),
0, 0, 0);
if(FAILED(hr)) 
{
MessageBox(NULL,"LoadXfile() OptimizeInplace","Error",MB_OK);
return false;}

adjBuffer->Release();
mtrlBuffer->Release();

}

BYTE* v=0;
m_pMesh->LockVertexBuffer(0,(void**)&v);
hr=D3DXComputeBoundingBox( (D3DXVECTOR3*)v,m_pMesh->GetNumVertices(),
						  D3DXGetFVFVertexSize(m_pMesh->GetFVF()),
						  &vMin,&vMax);

if(FAILED(hr)) 
{
MessageBox(NULL,"LoadXfile() D3DXComputeBoundingBox","Error",MB_OK);
return false;}

return true;

}

//Render Xfile
void RapModel::Render()
{
matWorld=matScale*matInitRotation*matRotation*matPosition;
m_pRap3d->GetDevice()->SetTransform( D3DTS_WORLD, &matWorld );
for (DWORD i=0;i<numMtrls;i++)
{
m_pRap3d->GetDevice()->SetMaterial(&m_Mtrls[i]);
m_pRap3d->GetDevice()->SetTexture(0,m_pTextures[i]);

m_pMesh->DrawSubset(i);

}

}


//Clean Up
bool RapModel::CleanUp()
{
if(m_pMesh!=NULL)
m_pMesh->Release();
if(m_Mtrls!=NULL)
delete[] m_Mtrls;

if(m_pTextures){
for (DWORD i=0;i<numMtrls;i++)
{
if (m_pTextures[i])m_pTextures[i]->Release();
}
delete[] m_pTextures;
}

return true;

}