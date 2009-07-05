/****************************************
Rap3D Engine
File: RapAniBoard.cpp
Desc: BillBoard With Animations
Author: Bill Hsu (C) All Rights Reserved
http://www.graptor.com
MSN/Email: bill@graptor.com
*****************************************/
#include "Rap3d.h"
#include "RapBillBoard.h"
#include "RapTexManager.h"
#include "RapAniBoard.h"
#include <fstream>

void RapAniBoard::init()
{
if (m_pRap3d==NULL) MessageBox(NULL,"SetEngine Please","Error",MB_OK);
if (m_pTexMan==NULL) MessageBox(NULL,"SetTexManager Please","Error",MB_OK);

m_pBlBd=new RapBillBoard;
m_pBlBd->SetEngine(m_pRap3d);

dwLastTime=timeGetTime();
TexList.clear();
}

void RapAniBoard::LoadAni(std::string FileName,D3DCOLOR alpha)
{
TexList.clear();
std::ifstream in(FileName.c_str());
in>>times;
in>>interval;
in>>iCount;
std::string str;
for (int i=0;i<iCount;++i)
{
in>>str;
m_pTexMan->LoadTex(str,"AniBoardTex-"+str,alpha);
TexList.push_back("AniBoardTex-"+str);
}

}

void RapAniBoard::Render(D3DCOLOR Color)
{

if (iTimesCount<times||times==0)
{
m_pBlBd->SetTexture(m_pTexMan->GetTex(TexList[iRenderCount]));
m_pBlBd->Render(NULL,Color);

DWORD currTime  = timeGetTime();
DWORD timeDelta = currTime - dwLastTime;



if (timeDelta>=interval)
{
++iRenderCount;
dwLastTime = currTime;
}


if (iRenderCount==iCount)
{
++iTimesCount;
iRenderCount=0;
}

}

}


void RapAniBoard::CloseDown()
{
TexList.clear();
if(m_pBlBd!=NULL)
{
m_pBlBd->CloseDown();
m_pBlBd=NULL;
}
}



