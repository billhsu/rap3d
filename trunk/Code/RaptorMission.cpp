#include"Rap3d.h"
#include "RapModel.h"
#include "RapBillBoard.h"
#include "Rap2d.h"
#include "RapTexManager.h"
#include "RapAniBoard.h"

#include "RaptorMission.h"

#include <stdio.h>


#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0) 
#define KEYUP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1) 

float i=0.0f;
D3DXVECTOR3 vEyePt;
D3DXVECTOR3 vLookatPt;

int Status=0;

void RaptorMission::enter()
{
m_pRap3d->SndCommand("open Res\\Snd\\BG.mp3  alias bkMusic");


TexMan=new RapTexManager;
TexMan->SetEngine(m_pRap3d);
TexMan->LoadTex("Res\\Sprite\\cross.bmp","cross",D3DCOLOR_RGBA(0,0,0,255));

anibd=new RapAniBoard;
anibd->SetEngine(m_pRap3d);
anibd->SetTexManager(TexMan);
anibd->init();
anibd->LoadAni("Expl3\\Expl.RapAni",D3DCOLOR_RGBA(0,0,0,255));
anibd->SetScale(0.5f);
m_pRap3d->ClearScreen();


m_pTexture1=TexMan->GetTex("cross");



rap2d=new Rap2d(m_pRap3d);
rap2d->SetTexture(m_pTexture1);
float width,height;
width=(float)rap2d->GetTexWidth();
height=(float)rap2d->GetTexHeight();

rap2d->SetPosition(400-width/2,300-height/2);



rapmdl=new RapModel;
rapmdl->SetEngine(m_pRap3d);
rapmdl->LoadXfile("Res\\GameScene\\GameScene.X");
rapmdl->Scale(3.0f,3.0f,3.0f);


SpaceShip1=new RapModel;
SpaceShip1->SetEngine(m_pRap3d);
SpaceShip1->LoadXfile("Res\\SpaceFighter01\\SpaceFighter01.x");
SpaceShip1->SetPosition(0.0f,20.0f,100.0f);
SpaceShip1->Scale(0.02f,0.02f,0.02f);
vEyePt=D3DXVECTOR3( 0.0f, 20.0f,0.0f );
vLookatPt=D3DXVECTOR3( 0.0f, 50.0f, 400.0f );

m_pRap3d->SetCamera(vEyePt,vLookatPt);
m_pRap3d->SetFont("Comic Sans MS",16);

rapmdl->Rotate(-D3DX_PI/2,-D3DX_PI/2,0);
m_pRap3d->SndCommand("play bkMusic repeat");



MSG msg;
ZeroMemory(&msg,sizeof(msg));

static float lastTime = (float)timeGetTime(); 

while(msg.message != WM_QUIT)
{
if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
{
TranslateMessage(&msg);
DispatchMessage(&msg);
}
else
{	
float currTime  = (float)timeGetTime();
float timeDelta = currTime - lastTime;

update(timeDelta);

lastTime = currTime;

}
}


}

void RaptorMission::update(float timeDelta)
{
timeDelta*=0.2;
UpdateLogic(timeDelta);

UpdateFrame(timeDelta);

}

void RaptorMission::UpdateLogic(float timeDelta)
{
i=i+timeDelta;
if (i>=178.437f) i=i-178.437f;
else if(KEYDOWN(VK_LEFT)) {SpaceShip1->PosX-=0.5f*timeDelta;Status=1;}
else if(KEYDOWN(VK_RIGHT)) {SpaceShip1->PosX+=0.5f*timeDelta;Status=2;}
else if(KEYDOWN(VK_UP)) {SpaceShip1->PosY+=0.5f*timeDelta;Status=3;}
else if(KEYDOWN(VK_DOWN)) {SpaceShip1->PosY-=0.5f*timeDelta;Status=4;}
else {Status=0;}
}

void RaptorMission::UpdateFrame(float timeDelta)
{
m_pRap3d->Clear(0x00000000);
m_pRap3d->BeginRender();
SpaceShip1->SetPosition(SpaceShip1->PosX,SpaceShip1->PosY,100.0f+i);

vEyePt=D3DXVECTOR3( SpaceShip1->PosX, SpaceShip1->PosY+10.0f,75.0f+i );
vLookatPt=D3DXVECTOR3( SpaceShip1->PosX, SpaceShip1->PosY, 200.0f+i);
anibd->SetPosition(SpaceShip1->PosX, SpaceShip1->PosY, 200.0f+i);
switch(Status)
{
case 0: 
///////////////////////////
SpaceShip1->Rotate(0.0f,0.0f,0.0f);
break;
///////////////////////////
break; 

case 1:
if (SpaceShip1->RotZ<=D3DX_PI/6)
SpaceShip1->Rotate(0.0f,0.0f,SpaceShip1->RotZ+0.02f*timeDelta);
break;

case 2:
if (SpaceShip1->RotZ>=-D3DX_PI/6)
SpaceShip1->Rotate(0.0f,0.0f,SpaceShip1->RotZ-0.02f*timeDelta);
break;

case 3:
if (SpaceShip1->RotX>=-D3DX_PI/6)
SpaceShip1->Rotate(SpaceShip1->RotX-0.02f*timeDelta,0.0f,0.0f);
break;

case 4:
if (SpaceShip1->RotX<=D3DX_PI/6)
SpaceShip1->Rotate(SpaceShip1->RotX+0.02f*timeDelta,0.0f,0.0f);
break;

} 

m_pRap3d->SetCamera(vEyePt,vLookatPt);
rapmdl->Render();
SpaceShip1->Render();
rap2d->Render();
anibd->Render(0xffffffff);
m_pRap3d->DrawText(0.0f,0.0f,"Hello Rap3d",0xffff0000,0);
m_pRap3d->EndRender();
}
