#include "CParticleSystem.h"

#define NUMBER_PARTICLES 1000 // 預設一次取得 1000 個 Particles

USING_NS_CC;

CParticleSystem::CParticleSystem()
{
	_fGravity = 0;
	_bEmitterOn = false;
}

void CParticleSystem::setEmitter(bool bEm)
{
	_bEmitterOn = bEm;
}

void CParticleSystem::isColorRandom(bool bCr) {
	_bRandomOn = bCr;
}

void CParticleSystem::init(cocos2d::Layer &inlayer)
{
	_iFree = NUMBER_PARTICLES;
	_iInUsed = 0;

	_pParticles = new CParticle[NUMBER_PARTICLES]; // 取得所需要的 particle 空間
	 // 讀入儲存多張圖片的 plist 檔
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("particletexture.plist");
	for (int i = 0; i < NUMBER_PARTICLES; i++) {
		_pParticles[i].setParticle("flare.png", inlayer);
		_FreeList.push_front(&_pParticles[i]);
	}
	r = g = b = 255;
}

void CParticleSystem::doStep(float dt)
{
	CParticle *get;
	list <CParticle *>::iterator it;
	if (_bEmitterOn) { // 根據 Emitter 設定的相關參數，產生相對應的分子
		// 先計算在累加
		_color = Color3B(64 + rand() % 128, 64 + rand() % 128, 64 + rand() % 128);

		int n = (int)(_fElpasedTime * _iNumParticles); // 到目前為止應該產生的分子個數
		if (n > _iGenParticles) {  // 產生的分子個數不足，產生到 n 個分子
			for (int i = 0; i < n - _iGenParticles; i++) {
				// 根據 Emitter 的相關參數，設定所產生分子的參數

				if (_iFree != 0) {
					if (_iEmitterType == 0) {
						get = _FreeList.front();
						get->setBehavior(EMITTER_DEFAULT);
						get->setColor(_color);
						get->setVelocity(_fVelocity);
						get->setLifetime(_fLifeTime);
						get->setGravity(_fGravity);
						get->setOpacity(_fOpacity);//set Opacity
						get->setSpin(_fSpin);//set spin
						get->setPosition(_emitterPt);
						get->setSize(0.125f);
						get->setWind(_fWind);
						get->setSpread(_fSpread); 
						if (!_bRandomOn) { get->setColor(Color3B(r, g, b)); }
						// 根據 _fSpread 與 _vDir 產生方向
						float t = (rand() % 1001) / 1000.0f; // 產生介於 0 到 1 間的數
						t = _fSpread - t * _fSpread * 2; //  產生的角度，轉成弧度
						t = (_fDir + t)* M_PI / 180.0f;
						Vec2 vdir(cosf(t), sinf(t));
						get->setDirection(vdir);
						_FreeList.pop_front();
						_InUsedList.push_front(get);
						_iFree--; _iInUsed++;
					}
					else if (_iEmitterType == 1) {
						get = _FreeList.front();
						get->setBehavior(EMITTER_ONE);	
						get->setColor(_color);
						if (!_bRandomOn) { get->setColor(Color3B(r, g, b)); }
						get->setLifetime(_fLifeTime);
						get->setPosition(_emitterPt);
						get->setSize(0.125f);
						setParticles(200);
						// 根據 _fSpread 與 _vDir 產生方向
						_fSpread = 30.0f;
						_fDir = 90.0f;
						float t = (rand() % 1001) / 1000.0f; // 產生介於 0 到 1 間的數
						t = _fSpread - t * _fSpread * 2; //  產生的角度，轉成弧度
						t = (_fDir + t)* M_PI / 180.0f;
						Vec2 vdir(cosf(t), sinf(t));
						get->setDirection(vdir);
						_FreeList.pop_front();
						_InUsedList.push_front(get);
						_iFree--; _iInUsed++;
					}
					else if (_iEmitterType == 2) {
						get = _FreeList.front();
						get->setBehavior(EMITTER_TWO);
						get->setColor(_color);
						if (!_bRandomOn) { get->setColor(Color3B(r, g, b)); }
						get->setLifetime(_fLifeTime);
						get->setPosition(_emitterPt);
						get->setSize(0.125f);
						setParticles(200);
						_fSpread = 30.0f;		
						float dir = (int)(_fElpasedTime * 1000) % 360;
						_fDir = dir;						
						// 根據 _fSpread 與 _vDir 產生方向						
						float t = (rand() % 1001) / 1000.0f; // 產生介於 0 到 1 間的數
						t = _fSpread - t * _fSpread * 2; //  產生的角度，轉成弧度
						t = (_fDir + t)* M_PI / 180.0f;
						Vec2 vdir(cosf(t), sinf(t));
						get->setDirection(vdir);
						_FreeList.pop_front();
						_InUsedList.push_front(get);
						_iFree--; _iInUsed++;
	
					}
					else if (_iEmitterType == 3) {
						get = _FreeList.front();
						get->setBehavior(EMITTER_THREE);
						get->setColor(_color);
						if (!_bRandomOn) { get->setColor(Color3B(r, g, b)); }
						get->setVelocity(4.0f);
						get->setLifetime(7.0f);						
						get->setPosition(_emitterPt);
						get->setSize(0.125f);
						setParticles(100);
						
						_fSpread = 20.0f;
						_fDir = 300.0f;
						// 根據 _fSpread 與 _vDir 產生方向
						float t = (rand() % 1001) / 1000.0f; // 產生介於 0 到 1 間的數
						t = _fSpread - t * _fSpread * 2; //  產生的角度，轉成弧度
						t = (_fDir + t)* M_PI / 180.0f;
						Vec2 vdir(cosf(t), sinf(t));
						get->setDirection(vdir);
						_FreeList.pop_front();
						_InUsedList.push_front(get);
						_iFree--; _iInUsed++;
					}
					else if (_iEmitterType == 4) {
						get = _FreeList.front();
						get->setBehavior(EMITTER_FOUR);
						Point pos = Point((int)(_fElpasedTime * 100) % 1000 + position, (int)(_fElpasedTime * 500) % 1000);
						get->setColor(_color);
						if (!_bRandomOn) { get->setColor(Color3B(r, g, b)); }
						get->setVelocity(8.4f);
						get->setLifetime(3.5f);
						get->setPosition(_emitterPt+ pos);
						get->setSize(0.125f);
						setParticles(100);

						_fSpread = 10.0f;
						_fDir = 85.0f;
						// 根據 _fSpread 與 _vDir 產生方向
						float t = (rand() % 1001) / 1000.0f; // 產生介於 0 到 1 間的數
						t = _fSpread - t * _fSpread * 2; //  產生的角度，轉成弧度
						t = (_fDir + t)* M_PI / 180.0f;
						Vec2 vdir(cosf(t), sinf(t));
						get->setDirection(vdir);
						_FreeList.pop_front();
						_InUsedList.push_front(get);
						_iFree--; _iInUsed++;
					}
				}
			}
			_iGenParticles = n; // 目前已經產生 n 個分子
			
			
		}
		
		if (_fElpasedTime >= 1.0f) {
			_fElpasedTime -= 1.0f;
			if (_iGenParticles >= _iNumParticles) _iGenParticles -= _iNumParticles;
			else _iGenParticles = 0;
		}
		_fElpasedTime += dt;
	}
	else if (_bSpark) {
		_fSparkTimer += dt;
		_sparkPos=Point(0,0);//sparkpos
		int n = (int)(_fElpasedTime * _iNumParticles); // 到目前為止應該產生的分子個數
		if (n > _iGenParticles) {  // 產生的分子個數不足，產生到 n 個分子
			for (int i = 0; i < n - _iGenParticles; i++) {
				if (_iFree != 0) {
					if (_iSparkPart == 1) {
						get = _FreeList.front();
						_color = Color3B(64 + rand() % 128, 64 + rand() % 128, 64 + rand() % 128);
						Point pos=	Point((int)(_fSparkTimer * 100) % 1000 + position, (int)(_fSparkTimer * 500) % 1000 );
						get->setBehavior(EMITTER_SPARK);
						get->setColor(_color);
						if (!_bRandomOn) { get->setColor(Color3B(r, g, b)); }
						get->setPosition(pos);				get->setLifetime(0.8f);
						get->setSize(0.5f);					setParticles(100);
						_fGravity = 0.0f;					_fSpread = 0.1f;
						_fDir = 90.0f;						setRot(15.0f);
						// 根據 _fSpread 與 _vDir 產生方向						
						float t = (rand() % 1001) / 1000.0f; // 產生介於 0 到 1 間的數
						t = _fSpread - t * _fSpread * 2; //  產生的角度，轉成弧度
						t = (_fDir + t)* M_PI / 180.0f;
						Vec2 vdir(cosf(t), sinf(t));		get->setDirection(vdir);
						if (_fSparkTimer > 1) {
							_iSparkPart = 2;				_sparkPos = pos;
						}
						_FreeList.pop_front();
						_InUsedList.push_front(get);		_iFree--;_iInUsed++;
					}
					if (_iSparkPart == 2) {
						if (_iFree > 100) {
							for (int i = 0; i < 100; i++) {			
								get = _FreeList.front();
								_color = Color3B(64 + rand() % 128, 64 + rand() % 128, 64 + rand() % 128);
								get->setBehavior(EXPLOSION);			
								get->setColor(_color);
								if (!_bRandomOn) { get->setColor(Color3B(r, g, b)); }
								get->setPosition(_sparkPos);							
								get->setRot(i*3.6f);					get->setGravity(-10.0f);			
								_FreeList.pop_front();
								_InUsedList.push_front(get);			_iFree--; _iInUsed++;							
							}
							_bSpark = false;							_iSparkPart = 4;	position = random(80, 600);
						}								
					}
				}
			}
			// 根據 Emitter 的相關參數，設定所產生分子的參數
			_iGenParticles = n; // 目前已經產生 n 個分子
		}

		if (_fElpasedTime >= 1.0f) {
			_fElpasedTime -= 1.0f;
			if (_iGenParticles >= _iNumParticles) _iGenParticles -= _iNumParticles;
			else _iGenParticles = 0;
		}
		_fElpasedTime += dt;
	}
	if (_iInUsed != 0) { // 有分子需要更新時
		for (it = _InUsedList.begin(); it != _InUsedList.end(); ) {
			if ((*it)->doStep(dt)) { // 分子生命週期已經到達
									 // 將目前這一個節點的內容放回 _FreeList
				_FreeList.push_front((*it));
				it = _InUsedList.erase(it); // 移除目前這一個, 
				_iFree++; _iInUsed--;
			}
			else it++;
		}
	}
	
}


void CParticleSystem::setSpread(float fSpread)
{
	_fSpread = fSpread;
}
void CParticleSystem::setGravity(float fGravity)
{
	// 設定目前 particle 是在 inused 的 gravity
	_fGravity = fGravity;
	list <CParticle *>::iterator it;
	if (_iInUsed != 0) { // 有分子需要更新時
		for (it = _InUsedList.begin(); it != _InUsedList.end(); it++) {
			(*it)->setGravity(_fGravity);
		}
	}
}
void CParticleSystem::setSpeed(float fSpeed) {//set speed
	_fVelocity = fSpeed;
}

void CParticleSystem::setSpin(float fSpin) {//set spin //not test
	_fSpin = fSpin;
	list <CParticle *>::iterator it;
	if (_iInUsed != 0) { // 有分子需要更新時
		for (it = _InUsedList.begin(); it != _InUsedList.end(); it++) {
			(*it)->setSpin(_fSpin);
		}
	}
}

void CParticleSystem::setOpacity(float fOpacity) {//set opacity
	_fOpacity = fOpacity;
}
void CParticleSystem::setParticles(int iParticles) {//set particle number
	_iNumParticles = iParticles;
}
void CParticleSystem::setLifetime(float fLifetime) {//set lifetime
	_fLifeTime = fLifetime;
}
void CParticleSystem::setColor( float fRed, float fGreen, float fBlue) {//set red
	r = fRed; g = fGreen; b = fBlue;
	list <CParticle *>::iterator it;
	if (_iInUsed != 0) { // 有分子需要更新時
		for (it = _InUsedList.begin(); it != _InUsedList.end(); it++) {
			(*it)->setColor(Color3B(r, g, b));
		}
	}
}
void CParticleSystem::setPic(const char *pngName,cocos2d::Layer &inlayer) {//set png
	for (int i = 0; i < NUMBER_PARTICLES; i++) {
		
	_pParticles[i].changeParticle(pngName, inlayer);
	}
}
void CParticleSystem::setWind(float fWind) {//set lifetime
	_fWind = fWind;
}
void CParticleSystem::setRot(float fRot) {//set lifetime
	_fRot= fRot;
	list <CParticle *>::iterator it;
	if (_iInUsed != 0) { // 有分子需要更新時
		for (it = _InUsedList.begin(); it != _InUsedList.end(); it++) {
			(*it)->setRot(_fRot);
		}
	}
}
CParticleSystem::~CParticleSystem()
{
	if (_iInUsed != 0) _InUsedList.clear(); // 移除所有的 NODE
	if (_iFree != 0) _FreeList.clear();
	delete[] _pParticles; // 釋放所有取得資源
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("particletexture.plist");
}

void CParticleSystem::onTouchesBegan(const cocos2d::CCPoint &touchPoint)
{
	CParticle *get;
	switch (_iType)
	{
	case STAY_FOR_TWOSECONDS:
		// 從 _FreeList 取得一個分子給放到 _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(STAY_FOR_TWOSECONDS);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			get->setSpin(_fSpin);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case RANDOMS_FALLING :
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(RANDOMS_FALLING);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case FREE_FLY:
		// 從 _FreeList 取得一個分子給放到 _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(FREE_FLY);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case EXPLOSION:
		// 從 _FreeList 取得一個分子給放到 _InUsed
		if (_iFree > 100) {
			for (int i = 0; i < 100; i++) {
				get = _FreeList.front();
				get->setBehavior(EXPLOSION);
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case HEARTSHAPE:
		// 從 _FreeList 取得一個分子給放到 _InUsed
		if (_iFree > 150) {
			for (int i = 0; i < 150; i++) {
				get = _FreeList.front();
				get->setBehavior(HEARTSHAPE);
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case BUTTERFLYSHAPE:
		// 從 _FreeList 取得一個分子給放到 _InUsed
		if (_iFree > 150) {
			for (int i = 0; i < 150; i++) {
				get = _FreeList.front();
				get->setBehavior(BUTTERFLYSHAPE);
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case STARSHAPE:
		// 從 _FreeList 取得一個分子給放到 _InUsed
		if (_iFree > 150) {
			for (int i = 0; i < 150; i++) {
				get = _FreeList.front();
				get->setBehavior(STARSHAPE);
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case SHAPE2:
		// 從 _FreeList 取得一個分子給放到 _InUsed
		if (_iFree > 50) {
			for (int i = 0; i < 50; i++) {
				get = _FreeList.front();
				get->setBehavior(SHAPE2);
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case SHAPE3:
		// 從 _FreeList 取得一個分子給放到 _InUsed
		if (_iFree > 150) {
			for (int i = 0; i < 150; i++) {
				get = _FreeList.front();
				get->setBehavior(SHAPE3);
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// 沒有分子, 所以就不提供
		break;
	}
}

void CParticleSystem::onTouchesMoved(const cocos2d::CCPoint &touchPoint)
{
	CParticle *get;
	switch (_iType)
	{
	case STAY_FOR_TWOSECONDS:
		// 從 _FreeList 取得一個分子給放到 _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(STAY_FOR_TWOSECONDS);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case RANDOMS_FALLING:
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(RANDOMS_FALLING);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case FREE_FLY:
		// 從 _FreeList 取得一個分子給放到 _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(FREE_FLY);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// 沒有分子, 所以就不提供
		break;
	case SHAPE2:
		// 從 _FreeList 取得一個分子給放到 _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(SHAPE2);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// 沒有分子, 所以就不提供
		break;
	
	case SHAPE3:
		// 從 _FreeList 取得一個分子給放到 _InUsed
		if (_iFree > 50) {
			for (int i = 0; i < 50; i++) {
				get = _FreeList.front();
				get->setBehavior(SHAPE3);
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// 沒有分子, 所以就不提供
		break;

	}
}