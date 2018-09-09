#ifndef __CPARTICLE_SYSTEM_H__
#define __CPARTICLE_SYSTEM_H__

#include "cocos2d.h"
#include "CParticle.h"
#include <list>

using namespace std;


class CParticleSystem
{
private:
	CParticle* _pParticles;
	list<CParticle*> _FreeList;
	list<CParticle*> _InUsedList;
	int _iFree;	// �i�Ϊ�  Particle �Ӽ�
	int _iInUsed;  // ���b�ϥΪ� Particle �Ӽ�
	int _iType;  // �ثe������l�B�ʼҦ��O���@�ث��A
	int _iEmitterType;
	bool _bEmitterOn; // Emitter �O�_���
	bool _bRandomOn;
	bool _bCheck;		//�^�ǭ�
public:
	// Emitter �]�w�������Ѽ�
	cocos2d::Point _emitterPt;	// Emitter ����m	
	float   _fDir;				// Emitter ���Q�g��V�A0 �� 360�סA�f�ɰw��V����
	int		_iNumParticles;		// �C�������ͪ����l�Ӽ�
	int     _iGenParticles;		// ��ثe����Ҳ��ͪ����l�Ӽ�(�H�C�����)
	float	_fSpread;			// 0 �� 180 �סA�w�]�� 180 
	float   _fVelocity;			// ���l�����}�t��
	float   _fLifeTime;			// ���l���s���ɶ�
	float	_fSpin;				// ���l������q degree/sec
	float   _fGravity;			// Gravity
	float   _fOpacity;			// Opacity
	float   _fRot;				// Rotation
	float	r, g, b;
	cocos2d::Point _sparkPos;
	float _fSparkTimer;
	cocos2d::Color3B _color;
	float   _fElpasedTime;		// �g�L�h�֮ɶ��A�H�����A�@�����ͤ��l���p��̾�
	cocos2d::Point _windDir;	// ������V�A���d�ҨS����@
	float _fWind;				// wind
	int position = 300;			// Firework born point.x
	bool colorchange = 0;		// keep user's color change per particle
	CParticleSystem();
	~CParticleSystem();
	void init(cocos2d::Layer &inlayer);
	void doStep(float dt);
	void setEmitter(bool bEm);
	void setType(int type) { _iType = type; }
	void setEmitterType(int type) { _iEmitterType = type; }//set emitter type
 //   void onTouchesEnded(const cocos2d::CCPoint &touchPoint);
    void onTouchesBegan(const cocos2d::CCPoint &touchPoint);
    void onTouchesMoved(const cocos2d::CCPoint &touchPoint);

	void setSpread(float fSpread);
	void setGravity(float fGravity);
	void setSpeed(float fSpeed);
	void setSpin(float fSpin);
	void setOpacity(float fOpacity);
	void setParticles(int iParticles);
	void setLifetime(float fLifetime);
	void setColor( float fRed, float fGreen, float fBlue);
	void setPic(const char *pngName, cocos2d::Layer &layer);
	void setWind(float fWind);
	bool _bSpark;
	int _iSparkPart;
	void setRot(float fRot);
	void isColorRandom(bool bCr);
	void setFlag(bool iCR);
	void readingColorFlag();
};

#endif