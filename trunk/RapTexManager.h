/****************************************
Rap3D Engine
File: RapTexManager.h
Desc: Manage Texture
Author: Bill Hsu (C) All Rights Reserved
http://www.graptor.com
MSN/Email: bill@graptor.com
*****************************************/
#ifndef __RapTexManager_H__
#define __RapTexManager_H__

#include <map>
#include <string>
#include <iostream>

class Rap3d;

class RapTexManager

{
private:
IDirect3DTexture9* m_pTexture;

typedef std::map<std::string, IDirect3DTexture9*> TexMap;
typedef TexMap::iterator TexMapIter;

TexMap TexManager;
TexMapIter iter;
int iCount;

public:

Rap3d *m_pRap3d;

RapTexManager():iCount(0){};
~RapTexManager(){CloseDown();}

void SetEngine(Rap3d *pRap3d)
{
m_pRap3d=pRap3d;
}

void LoadTex(std::string FileName,std::string TexName="",D3DCOLOR alpha=NULL);

IDirect3DTexture9* GetTex(std::string TexName);
int GetTexNum(){return iCount;}
void Remove(std::string TexName);

void CloseDown();

};

#endif