/****************************************
Rap3D Engine
File: RapAniBoard.h
Desc: BillBoard With Animations
Author: Bill Hsu (C) All Rights Reserved
http://www.graptor.com
MSN/Email: bill@graptor.com
*****************************************/
#ifndef __RapAniBoard_H__
#define __RapAniBoard_H__

#include <string>
#include <iostream>
#include<vector>
class Rap3d;
class RapBillBoard;
class RapTexManager;


class RapAniBoard
{
private:
Rap3d *m_pRap3d;
RapBillBoard *m_pBlBd;
RapTexManager *m_pTexMan;
DWORD dwLastTime;
DWORD interval;
int times;
int iCount;

int iRenderCount;
int iTimesCount;

std::vector<std::string> TexList;

public:
RapAniBoard():times(1),iRenderCount(0),iTimesCount(0){}
~RapAniBoard(){CloseDown();}
void init();
void SetEngine(Rap3d *pRap3d){m_pRap3d=pRap3d;}
void SetTexManager(RapTexManager *pTexMan){m_pTexMan=pTexMan;}

void SetPosition(float x=0.0f,float y=0.0f,float z=0.0f)
{
m_pBlBd->SetPosition(x,y,z);
}

void SetScale(float scale)
{
m_pBlBd->SetScale(scale);
}



void LoadAni(std::string FileName,D3DCOLOR alpha=NULL);
void Render(D3DCOLOR Color=0xffffffff);

void CloseDown();

};

#endif
