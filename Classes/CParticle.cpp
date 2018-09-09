#include <cmath>
#include "CParticle.h"


// 根據重力與時間計算 delta time 之間的位移差量 再轉成螢幕的位移
// 假設 2.5 秒讓一個分子從螢幕最上方移動到最下方, 也就是移動 720 PIXEL
// 720 PIXEL = 0.5*9.8*2.5*2.5 m => 1M = 23.5102 PIXEL
// 因為Y 軸往下為負, 所以重力要加上負號, 代表方向

#define FALLING_TIME 2.5f
#define MAX_HEIGHT 720.0f
#define PIXEL_PERM (2.0f*MAX_HEIGHT/(9.8f*FALLING_TIME*FALLING_TIME))
#define GRAVITY_Y(t,dt,g) ((g)*(t+0.5f*(dt)))  //已經經過 t 秒後，再經過 dt 時間內落下距離
#define WIND_X(t, dt, g) ((g)*(t + 0.5f*(dt)))
#define LIFE_NOISE(f) ((f)*(1.0f-(rand()%2001/1000.0f)))
//#define INTENSITY(f)  ( (f) >= 255 ? 255 : (f) )

inline int INTENSITY(float f) {
	if (f >= 255) return(255);
	else if (f <= 0) return(0);
	else return((int)f);
}

USING_NS_CC;

CParticle::CParticle()
{
	_fGravity = 0;
}


bool CParticle::doStep(float dt)
{
	float cost, sint;
	switch (_iType) {
	case STAY_FOR_TWOSECONDS:
		if (!_bVisible && _fElapsedTime >= _fDelayTime ) {
			_fElapsedTime = _fElapsedTime - _fDelayTime; // 重新開始計時
			_bVisible = true;
			_Particle->setVisible(_bVisible);
			_Particle->setColor(_color);
			_Particle->setPosition(_Pos);
		}
		else if (_fElapsedTime> _fLifeTime) {
			_bVisible = false;
			_Particle->setVisible(_bVisible);
			return true; // 分子生命週期已經結束
		}
		else {
			sint = sinf(M_PI*_fElapsedTime / _fLifeTime);
			cost = cosf(M_PI_2*_fElapsedTime / _fLifeTime);
			_Particle->setScale(1 + sint * 2);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(_color);
			//gravity
			float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
			_Pos.y += (_Direction.y  * _fVelocity + tt) * dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);
			//spin
			float degree = _Particle->getRotation();
			degree += dt *_fSpin; // 計算 dt 時間內轉動的角度量，並累加到目前的角度中
			_Particle->setRotation(degree);

		}
		break;
	case RANDOMS_FALLING:
		if (!_bVisible && _fElapsedTime >= _fDelayTime) {
			_fElapsedTime = _fElapsedTime - _fDelayTime; // 重新開始計時
			_bVisible = true;
			_Particle->setVisible(_bVisible);
			_Particle->setColor(_color);
			_Particle->setPosition(_Pos);
		}
		else if (_fElapsedTime > _fLifeTime) {
			_bVisible = false;
			_Particle->setVisible(_bVisible);
			return true; // 分子生命週期已經結束
		}
		else {
			sint = sinf(M_PI*_fElapsedTime / _fLifeTime);
			cost = cosf(M_PI_2*_fElapsedTime / _fLifeTime);
			_Particle->setScale(1 + sint * 1.25f);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(_color);
			_Pos.x += _Direction.x * _fVelocity * dt * PIXEL_PERM;
			float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
			_Pos.y += (_Direction.y * _fVelocity + tt)* dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);

		}
		break;
	case FREE_FLY:
		if (!_bVisible && _fElapsedTime >= _fDelayTime) {
			_fElapsedTime = _fElapsedTime - _fDelayTime; // 重新開始計時
			_bVisible = true;
			_Particle->setVisible(_bVisible);
			_Particle->setColor(_color);
			_Particle->setPosition(_Pos);
		}
		else if (_fElapsedTime > _fLifeTime) {
			_bVisible = false;
			_Particle->setVisible(_bVisible);
			return true; // 分子生命週期已經結束
		}
		else {
			sint = sinf(M_PI*_fElapsedTime / _fLifeTime);
			cost = cosf(M_PI_2*_fElapsedTime / _fLifeTime);
			_Particle->setScale(1 + sint * 2);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(_color);
			_Pos.x += _Direction.x * _fVelocity * dt * PIXEL_PERM;
			float tt = GRAVITY_Y(_fElapsedTime, dt,_fGravity);
			_Pos.y += (_Direction.y * _fVelocity + tt)* dt * PIXEL_PERM;
			//_Pos.y += _Direction.y * _fVelocity * dt;
			_Particle->setPosition(_Pos);
		}
		break;
	case EXPLOSION:
		if (!_bVisible && _fElapsedTime >= _fDelayTime) {
			_fElapsedTime = _fElapsedTime - _fDelayTime; // 重新開始計時
			_bVisible = true;
			_Particle->setVisible(_bVisible);
			_Particle->setColor(_color);
			_Particle->setPosition(_Pos);
		}
		else if (_fElapsedTime > _fLifeTime) {
			_bVisible = false;
			_Particle->setVisible(_bVisible);
			return true; // 分子生命週期已經結束
		}
		else {
			sint = sinf(M_PI*_fElapsedTime / _fLifeTime);
			cost = cosf(M_PI_2*_fElapsedTime / _fLifeTime);
			_Particle->setScale(1.25 + sint*2.0);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(_color);
			_Pos.x += _Direction.x * cost * _fVelocity * dt * PIXEL_PERM;
			float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
			_Pos.y += (_Direction.y * cost * _fVelocity + tt)* dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);
		}
		break;
	case HEARTSHAPE:
	case BUTTERFLYSHAPE:
	case STARSHAPE:
	case SHAPE2:
	case SHAPE3:
		if (!_bVisible && _fElapsedTime >= _fDelayTime) {
			_fElapsedTime = _fElapsedTime - _fDelayTime; // 重新開始計時
			_bVisible = true;
			_Particle->setVisible(_bVisible);
			_Particle->setColor(_color);
			_Particle->setPosition(_Pos);
		}
		else if (_fElapsedTime > _fLifeTime) {
			_bVisible = false;
			_Particle->setVisible(_bVisible);
			return true; // 分子生命週期已經結束
		}
		else {
			// 根據心型公式，計算每一個分子的終止位置
			sint = sinf(M_PI*_fElapsedTime / _fLifeTime);
			cost = cosf(M_PI_2*_fElapsedTime / _fLifeTime);
			_Particle->setScale(1.25 + (1 - cost)*2.0);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(_color);
			_Pos.x += _Direction.x * cost * _fVelocity * dt * PIXEL_PERM;
			float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
			_Pos.y += (_Direction.y * cost * _fVelocity + tt)* dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);
		}
		break;
	case EMITTER_DEFAULT:
		if (!_bVisible && _fElapsedTime >= _fDelayTime) {
			_fElapsedTime = _fElapsedTime - _fDelayTime; // 重新開始計時
			_bVisible = true;
			_Particle->setVisible(_bVisible);
			_Particle->setColor(_color);
			_Particle->setPosition(_Pos);
		}
		else if (_fElapsedTime > _fLifeTime) {
			_bVisible = false;
			_Particle->setVisible(_bVisible);
			return true; // 分子生命週期已經結束
		}
		else {
			sint = sinf(M_PI*_fElapsedTime / _fLifeTime);
			cost = cosf(M_PI_2*_fElapsedTime / _fLifeTime);
			_Particle->setScale(_fSize + sint * 1.5f );
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(_color);
			//gravity
			_Pos.x += _Direction.x * _fVelocity * dt * PIXEL_PERM;
			float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
			_Pos.y += (_Direction.y * _fVelocity + tt)* dt * PIXEL_PERM;
			//wind
			float ww = WIND_X(_fElapsedTime, dt, _fWind);
			_Pos.x += (_Direction.x * _fVelocity +10*sinf(ww) )*dt * PIXEL_PERM;
			//_Pos.y += _Direction.y * _fVelocity*ww* dt * PIXEL_PERM;

			_Particle->setPosition(_Pos);
			//spin
			float degree = _Particle->getRotation();
			degree += dt *_fSpin; // 計算 dt 時間內轉動的角度量，並累加到目前的角度中
			_Particle->setRotation(degree);
		}
		break;
	case EMITTER_ONE:
	case EMITTER_TWO:
	case EMITTER_THREE:
	case EMITTER_SPARK:
	case EMITTER_FOUR:
		if (!_bVisible && _fElapsedTime >= _fDelayTime) {
			_fElapsedTime = _fElapsedTime - _fDelayTime; // 重新開始計時
			_bVisible = true;
			_Particle->setVisible(_bVisible);
			_Particle->setColor(_color);
			_Particle->setPosition(_Pos);
		}
		else if (_fElapsedTime > _fLifeTime) {
			_bVisible = false;
			_Particle->setVisible(_bVisible);
			return true; // 分子生命週期已經結束
		}
		else {
			sint = sinf(M_PI*_fElapsedTime / _fLifeTime);
			cost = cosf(M_PI_2*_fElapsedTime / _fLifeTime);
			_Particle->setScale(_fSize + sint * 1.5f);
			_Particle->setOpacity(_fOpacity * cost);
			_Particle->setColor(_color);
			//gravity
			_Pos.x += _Direction.x * _fVelocity * dt * PIXEL_PERM;
			float tt = GRAVITY_Y(_fElapsedTime, dt, _fGravity);
			_Pos.y += (_Direction.y * _fVelocity + tt)* dt * PIXEL_PERM;
			//wind
			float ww = WIND_X(_fElapsedTime, dt, _fWind);
			_Pos.x += (_Direction.x * _fVelocity + 10 * sinf(ww))*dt * PIXEL_PERM;
			_Particle->setPosition(_Pos);
			//spin
			float degree = _Particle->getRotation();
			degree += dt *_fSpin; // 計算 dt 時間內轉動的角度量，並累加到目前的角度中
			_Particle->setRotation(degree);
		}
		break;
	}
	// 累加時間
	_fElapsedTime += dt;
	return false;
}


void CParticle::setBehavior(int iType)
{
	float t;
	_iType = iType;
	switch (_iType) {
	case STAY_FOR_TWOSECONDS:
		_fVelocity = 0;
		_fLifeTime = 2.5f + LIFE_NOISE(0.15f);
		_fIntensity = 1;
		_fOpacity = 255;
		_fSpin = 0;
		_fSize = 1;
		_color = Color3B(64 + rand() % 128, 64 + rand() % 128, 64 + rand() % 128);
		_fElapsedTime = 0;
		_fDelayTime = 0;
		_fGravity = 0;
		_Particle->setOpacity(255);
		_Particle->setScale(_fSize);
		break;
	case RANDOMS_FALLING:
		_fVelocity = 5.0f + rand() % 10 / 10.0f; // 單位 M/Sec
		_Direction.x = 0;
		_Direction.y = -1;
		_fLifeTime = 3.0f + LIFE_NOISE(0.15f);
		_fIntensity = 1;
		_fOpacity = 255;
		_fSpin = 0;
		_fSize = 1;
		_color = Color3B(128 + rand() % 128, 128 + rand() % 128, 128 + rand() % 128);
		_fElapsedTime = 0;
		_fDelayTime = 0;
		_fGravity = 0;
		break;
	case FREE_FLY:
		_fVelocity = 5.0f + rand() % 10 / 10.0f; // 單位 M/Sec
		t = 2.0f * M_PI * (rand() % 1000) / 1000.0f;
		_Direction.x = cosf(t);
		_Direction.y = sinf(t);
		_fLifeTime = 3.0f + LIFE_NOISE(0.15f);
		_fIntensity = 1;
		_fOpacity = 255;
		_fSpin = 0;
		_fSize = 1;
		_color = Color3B(128 + rand() % 128, 128 + rand() % 128, 128 + rand() % 128);
		_fElapsedTime = 0;
		_fDelayTime = 0;
		_fGravity = 0;
		break;
	case EXPLOSION:
		_fVelocity = 15.0f + rand() % 10 / 10.0f;
		t = 2.0f * M_PI * (rand() % 1000) / 1000.0f;
		_Direction.x = cosf(t);
		_Direction.y = sinf(t);
		_fLifeTime = 1.5f + LIFE_NOISE(0.15f);
		_fIntensity = 1;
		_fOpacity = 255;
		_fSpin = 0;
		_fSize = 1;
		_color = Color3B(64 + rand() % 128, 64 + rand() % 128,64 + rand() % 128);
		//_color = Color3B(255, 255, 255);
		_fElapsedTime = 0;
		_fDelayTime = rand() % 100 / 1000.0f;
		_fGravity = 0;
		break;
	case HEARTSHAPE:
		_fVelocity = 1.0f;
		t = 2.0f * M_PI * (rand() % 1000) / 1000.0f;
		float sint, cost, cos2t, cos3t, cos4t, sin12t;
		sint = sinf(t);  cost = cosf(t); cos2t = cosf(2*t); cos3t = cosf(3 * t); cos4t = cosf(4 * t);
		sin12t = sin(t/12.0f);
		_Direction.x = 16*sint*sint*sint;
		_Direction.y = 13*cost - 5*cos2t - 2*cos3t - cos4t;
		_fLifeTime = 1.5f + LIFE_NOISE(0.15f);
		_fIntensity = 1;
		_fOpacity = 255;
		_fSpin = 0;
		_fSize = 1;
		_color = Color3B(128 + rand() % 128, 128 + rand() % 128, 128 + rand() % 128);
		//_color = Color3B(255, 255, 255);
		_fElapsedTime = 0;
		_fDelayTime = rand() % 100 / 1000.0f;
		_fGravity = 0;
		break;
	case BUTTERFLYSHAPE:
		_fVelocity = 6.5f;
		t = 2.0f * M_PI * (rand() % 1000) / 1000.0f;
		sint = sinf(t);  cost = cosf(t); cos4t = cosf(4 * t); sin12t = sin(t / 12.0f);
		_Direction.x = sint*(expf(cost) - 2 * cos4t - powf(sin12t, 5));
		_Direction.y = cost*(expf(cost) - 2 * cos4t - powf(sin12t, 5));
		_fLifeTime = 1.5f + LIFE_NOISE(0.15f);
		_fIntensity = 1;
		_fOpacity = 255;
		_fSpin = 0;
		_fSize = 1;
		_color = Color3B(128 + rand() % 128, 128 + rand() % 128, 128 + rand() % 128);
		//_color = Color3B(255, 255, 255);
		_fElapsedTime = 0;
		_fDelayTime = rand() % 100 / 1000.0f;
		_fGravity = 0;
		break;
	case STARSHAPE:
		_fVelocity = 8.5f;
		t = 2.0f * M_PI * (rand() % 1000) / 1000.0f;
		sint = sinf(t);  cost = cosf(t); 
		_Direction.x = sint*sint*sint*cost * 4;
		_Direction.y = cost*cost*cost*sint * 4;
		_fLifeTime = 1.5f + LIFE_NOISE(0.15f);
		_fIntensity = 1;
		_fOpacity = 255;
		_fSpin = 0;
		_fSize = 1;
		_color = Color3B(128 + rand() % 128, 128 + rand() % 128, 128 + rand() % 128);
		//_color = Color3B(255, 255, 255);
		_fElapsedTime = 0;
		_fDelayTime = rand() % 100 / 1000.0f;
		_fGravity = 0;
		break;
	case SHAPE2:
		_fVelocity =6.5f;
		t = 2.0f * M_PI * (rand() % 1000) / 1000.0f;
		sint = sinf(t);  cost = cosf(t);
		_Direction.x = sint*sint*sint*cost * 8;
		_Direction.y = cost*cost*sint*sint*cost*cost * 6;
		_fLifeTime = 1.5f + LIFE_NOISE(0.15f);
		_fIntensity = 1;
		_fOpacity = 255;
		_fSpin = 0;
		_fSize = 1;
		_color = Color3B(128 + rand() % 128, 128 + rand() % 128, 128 + rand() % 128);
		//_color = Color3B(255, 255, 255);
		_fElapsedTime = 0;
		_fDelayTime = rand() % 100 / 1000.0f;
		_fGravity = -10.0f;
		break;
	case SHAPE3:
		_fVelocity = 10.0f;
		t = 2.0f * M_PI * (rand() % 1000) / 1000.0f;
		sint = sinf(t);  cost = cosf(t);
		_Direction.x = cost*sint*cost * 8+ sint*sint*sint;
		_Direction.y = 4.0f*sint*sint*cost;
		_fLifeTime = 1.5f + LIFE_NOISE(0.15f);
		_fIntensity = 1;
		_fOpacity = 255;
		_fSpin = 30.0f;
		_fSize = 1;
		_color = Color3B(128 + rand() % 128, 128 + rand() % 128, 128 + rand() % 128);
		//_color = Color3B(255, 255, 255);
		_fElapsedTime = 0;
		_fDelayTime = rand() % 100 / 1000.0f;
		_fGravity = 10.0f;
		break;
	case EMITTER_DEFAULT:
		_fIntensity = 1;
		_fOpacity = 255;
		_fSize = 1;
		_color = Color3B(rand() % 128, rand() % 128, 128 + rand() % 128);
		_fElapsedTime = 0;
		_fDelayTime = 0;
		_fSpread = 180.0f;
		_Particle->setScale(_fSize);
	
		break;
	case EMITTER_ONE:
		_fIntensity = 1;
		_fOpacity = 255;
		_fSize = 1;
		_color = Color3B(rand() % 128, rand() % 128, 128 + rand() % 128);
		_fElapsedTime = 0;
		_fDelayTime = 0;
		_Particle->setScale(_fSize);
		_fSpin = 0.0f;
		_fGravity = -10.0f;
		_fWind = -0.0f;
		_fVelocity = 6.0f;
	
		break;
	case EMITTER_TWO:
		_fIntensity = 1;
		_fOpacity = 255;
		_fSize = 1;
		_color = Color3B(rand() % 128, rand() % 128, 128 + rand() % 128);
		_fElapsedTime = 0;
		_fDelayTime = 0;
		_Particle->setScale(_fSize);
		_fSpin = 0.0f;
		_fGravity = 0.0f;
		_fWind = 0.0f;
		_fVelocity = 10.0f;
		break;
	case EMITTER_THREE:
		_fIntensity = 1;
		_fOpacity = 230;
		_fSize = 1;
		_color = Color3B(145,84,255);
		_fElapsedTime = 0;
		_fDelayTime = 0;
		_Particle->setScale(_fSize);
		_fSpin = 0.0f;
		_fGravity = -10.0f;
		_fWind = 0.6f;
		_fVelocity = 4.0f;
		_fLifeTime = 7.0f;
		break;
	case EMITTER_SPARK:
		_fIntensity = 1;
		_fOpacity = 255;
		_fSize = 1;
		_fElapsedTime = 0;
		_fDelayTime = 0;
		_Particle->setScale(_fSize);
		_fSpin = 0.0f;
		_fGravity = -10.0f;
		_fWind = -0.0f;
		_fVelocity = 3.2f;
		_fLifeTime = 0.4f;
		break;
	case EMITTER_FOUR:
		_fIntensity = 1;
		_fOpacity = 255;
		_fSize = 1;
		_color = Color3B(255, 255, 50);
		_fElapsedTime = 0;
		_fDelayTime = 0;
		_Particle->setScale(_fSize);
		_fSpin = 170.0f;
		_fGravity = -2.4f;
		_fWind = 0.4f;
		_fVelocity = 8.4f;
		_fLifeTime = 3.5f;
		break;
	}
}
void CParticle::setLifetime(const float lt) {
	_fLifeTime = lt + LIFE_NOISE(0.15f);;
}


void CParticle::setParticle(const char *pngName, cocos2d::Layer &inlayer)
{
	_Particle = Sprite::createWithSpriteFrameName(pngName);
	_Particle->setPosition(Point(rand() % 1024, rand() % 768));
	_Particle->setOpacity(255);
	_Particle->setColor(Color3B::WHITE);
	_bVisible = false;
	_Particle->setVisible(false);
	_iType = 0;
	//BlendFunc blendfunc = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};  
	BlendFunc blendfunc = { GL_SRC_ALPHA, GL_ONE };
	_Particle->setBlendFunc(blendfunc);
	inlayer.addChild(_Particle, 1);
}
void CParticle::changeParticle(const char *pngName, cocos2d::Layer &inlayer)
{
	inlayer.removeChild(_Particle, 1);
	_Particle = Sprite::createWithSpriteFrameName(pngName);
	_Particle->setPosition(Point(rand() % 1024, rand() % 768));
	_Particle->setOpacity(255);
	_Particle->setColor(Color3B::WHITE);
	_bVisible = false;
	_Particle->setVisible(false);
	_iType = 0;
	//BlendFunc blendfunc = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};  
	BlendFunc blendfunc = { GL_SRC_ALPHA, GL_ONE };
	_Particle->setBlendFunc(blendfunc);
	inlayer.addChild(_Particle, 1);
}

void CParticle::setVisible()
{
	_bVisible = true;
	_Particle->setVisible(_bVisible);
}

void CParticle::setPosition(const cocos2d::Point &inPos) {
	_Pos = inPos;
};

void CParticle::setGravity(const float fGravity)
{
	_fGravity = fGravity;
}
void CParticle::setSpin(const float fSpin)
{
	_fSpin = fSpin;
}
void CParticle::setOpacity(const float fOpacity)
{
	_fOpacity = fOpacity;
}
void CParticle::setWind(const float fWind)
{
	_fWind = fWind;
}
void CParticle::setSpread(const float fSpread)
{
	_fSpread = fSpread;
}
