/****************************************
Rap3D Engine
File: RapModel.h
Desc: Model Ctrl
Author: Bill Hsu (C) All Rights Reserved
http://www.graptor.com
MSN/Email: bill@graptor.com
*****************************************/
#ifndef __RapModel_H__
#define __RapModel_H__

class Rap3d;

class RapModel
{
private:
Rap3d* m_pRap3d;
ID3DXMesh* m_pMesh;
D3DMATERIAL9* m_Mtrls;
IDirect3DTexture9** m_pTextures;
DWORD numMtrls;
D3DXMATRIXA16 matWorld,matPosition,matScale;
D3DXMATRIXA16 matRotation,matRotationX,matRotationY,matRotationZ;
D3DXMATRIXA16 matInitRotation;
public:

float PosX,PosY,PosZ;//Get Model Position here
float RotX,RotY,RotZ;//Get Model Rotation here
float ScaX,ScaY,ScaZ;//Get Scale here

D3DXVECTOR3 vMin;//for Bounding Box min vector
D3DXVECTOR3 vMax;//for Bounding Box max vector

void init()
{
PosX=0.0f;PosY=0.0f;PosZ=0.0f;
RotX=0.0f;RotY=0.0f;RotZ=0.0f;
ScaX=1.0f;ScaY=1.0f;ScaZ=1.0f;

D3DXMatrixTranslation(&matPosition,0.0f,0.0f,0.0f);
D3DXMatrixRotationX( &matRotationX,0.0f);
D3DXMatrixRotationY( &matRotationY,0.0f);
D3DXMatrixRotationZ( &matRotationZ,0.0f);
matRotation=matRotationX*matRotationY*matRotationZ;
matInitRotation=matRotationX*matRotationY*matRotationZ;
D3DXMatrixScaling(&matScale,1.0f,1.0f,1.0f);
vMin=D3DXVECTOR3(FLT_MAX,FLT_MAX,FLT_MAX);
vMax=D3DXVECTOR3(-FLT_MAX,-FLT_MAX,-FLT_MAX);
SetPosition(0.0f,0.0f,0.0f);
}

RapModel()
{
init();
}
RapModel(Rap3d* rap3d):m_pRap3d(rap3d)
{
init();
}
~RapModel(){CleanUp();}
void SetEngine(Rap3d* rap3d){m_pRap3d=rap3d;}
bool LoadXfile(const TCHAR* filename);
void Render();
//Set model position
void SetPosition(float posX=0.0f,float posY=0.0f,float posZ=0.0f)
{
PosX=posX;
PosY=posY;
PosZ=posZ;
D3DXMatrixTranslation(&matPosition,PosX,PosY,PosZ);

}

//Rotate model
void Rotate(float rotX=0.0f,float rotY=0.0f,float rotZ=0.0f)
{
RotX=rotX;
RotY=rotY;
RotZ=rotZ;
D3DXMatrixRotationX( &matRotationX,RotX);
D3DXMatrixRotationY( &matRotationY,RotY);
D3DXMatrixRotationZ( &matRotationZ,RotZ);
matRotation=matRotationX*matRotationY*matRotationZ;
}

void InitRotate(float rotX=0.0f,float rotY=0.0f,float rotZ=0.0f)
{
D3DXMATRIXA16 matRotationX,matRotationY,matRotationZ;

D3DXMatrixRotationX( &matRotationX,rotX);
D3DXMatrixRotationY( &matRotationY,rotY);
D3DXMatrixRotationZ( &matRotationZ,rotZ);
matInitRotation=matRotationX*matRotationY*matRotationZ;
}
//Scale model
void Scale(float scaX=1.0f,float scaY=1.0f,float scaZ=1.0f)
{
ScaX=scaX;
ScaY=scaY;
ScaZ=scaZ;
D3DXMatrixScaling(&matScale,ScaX,ScaY,ScaZ);
}
void GetBoundingBox(D3DXVECTOR3& vmax,D3DXVECTOR3& vmin);
bool CleanUp();

};

#endif