#ifndef __RaptorMission_H__
#define __RaptorMission_H__

class Rap3d;
class RapModel;
class RapBillBoard;
class Rap2d;
class RapTexManager;
class RapAniBoard;
class RaptorMission
{
private:
Rap3d *m_pRap3d;
RapModel* rapmdl;
RapModel* SpaceShip1;

RapTexManager* TexMan;
RapAniBoard* anibd;

Rap2d* rap2d;
public:


IDirect3DTexture9* m_pTexture1;
IDirect3DTexture9* m_pTexture2;
HWND window;
RaptorMission(Rap3d* rap3d):m_pRap3d(rap3d){};
RaptorMission(){};
~RaptorMission(){};
void SetEngine(Rap3d* rap3d){m_pRap3d=rap3d;};
void enter();
float time();
void update(float timeDelta=0.0f);
void UpdateLogic(float timeDelta=0.0f);
void UpdateFrame(float timeDelta=0.0f);

};

#endif 