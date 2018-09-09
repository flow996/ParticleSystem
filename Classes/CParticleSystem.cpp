#include "CParticleSystem.h"

#define NUMBER_PARTICLES 1000 // �w�]�@�����o 1000 �� Particles

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

	_pParticles = new CParticle[NUMBER_PARTICLES]; // ���o�һݭn�� particle �Ŷ�
	 // Ū�J�x�s�h�i�Ϥ��� plist ��
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
	if (_bEmitterOn) { // �ھ� Emitter �]�w�������ѼơA���ͬ۹��������l
		// ���p��b�֥[
		_color = Color3B(64 + rand() % 128, 64 + rand() % 128, 64 + rand() % 128);

		int n = (int)(_fElpasedTime * _iNumParticles); // ��ثe�������Ӳ��ͪ����l�Ӽ�
		if (n > _iGenParticles) {  // ���ͪ����l�ӼƤ����A���ͨ� n �Ӥ��l
			for (int i = 0; i < n - _iGenParticles; i++) {
				// �ھ� Emitter �������ѼơA�]�w�Ҳ��ͤ��l���Ѽ�

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
						// �ھ� _fSpread �P _vDir ���ͤ�V
						float t = (rand() % 1001) / 1000.0f; // ���ͤ��� 0 �� 1 ������
						t = _fSpread - t * _fSpread * 2; //  ���ͪ����סA�ন����
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
						// �ھ� _fSpread �P _vDir ���ͤ�V
						_fSpread = 30.0f;
						_fDir = 90.0f;
						float t = (rand() % 1001) / 1000.0f; // ���ͤ��� 0 �� 1 ������
						t = _fSpread - t * _fSpread * 2; //  ���ͪ����סA�ন����
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
						// �ھ� _fSpread �P _vDir ���ͤ�V						
						float t = (rand() % 1001) / 1000.0f; // ���ͤ��� 0 �� 1 ������
						t = _fSpread - t * _fSpread * 2; //  ���ͪ����סA�ন����
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
						// �ھ� _fSpread �P _vDir ���ͤ�V
						float t = (rand() % 1001) / 1000.0f; // ���ͤ��� 0 �� 1 ������
						t = _fSpread - t * _fSpread * 2; //  ���ͪ����סA�ন����
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
						// �ھ� _fSpread �P _vDir ���ͤ�V
						float t = (rand() % 1001) / 1000.0f; // ���ͤ��� 0 �� 1 ������
						t = _fSpread - t * _fSpread * 2; //  ���ͪ����סA�ন����
						t = (_fDir + t)* M_PI / 180.0f;
						Vec2 vdir(cosf(t), sinf(t));
						get->setDirection(vdir);
						_FreeList.pop_front();
						_InUsedList.push_front(get);
						_iFree--; _iInUsed++;
					}
				}
			}
			_iGenParticles = n; // �ثe�w�g���� n �Ӥ��l
			
			
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
		int n = (int)(_fElpasedTime * _iNumParticles); // ��ثe�������Ӳ��ͪ����l�Ӽ�
		if (n > _iGenParticles) {  // ���ͪ����l�ӼƤ����A���ͨ� n �Ӥ��l
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
						// �ھ� _fSpread �P _vDir ���ͤ�V						
						float t = (rand() % 1001) / 1000.0f; // ���ͤ��� 0 �� 1 ������
						t = _fSpread - t * _fSpread * 2; //  ���ͪ����סA�ন����
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
			// �ھ� Emitter �������ѼơA�]�w�Ҳ��ͤ��l���Ѽ�
			_iGenParticles = n; // �ثe�w�g���� n �Ӥ��l
		}

		if (_fElpasedTime >= 1.0f) {
			_fElpasedTime -= 1.0f;
			if (_iGenParticles >= _iNumParticles) _iGenParticles -= _iNumParticles;
			else _iGenParticles = 0;
		}
		_fElpasedTime += dt;
	}
	if (_iInUsed != 0) { // �����l�ݭn��s��
		for (it = _InUsedList.begin(); it != _InUsedList.end(); ) {
			if ((*it)->doStep(dt)) { // ���l�ͩR�g���w�g��F
									 // �N�ثe�o�@�Ӹ`�I�����e��^ _FreeList
				_FreeList.push_front((*it));
				it = _InUsedList.erase(it); // �����ثe�o�@��, 
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
	// �]�w�ثe particle �O�b inused �� gravity
	_fGravity = fGravity;
	list <CParticle *>::iterator it;
	if (_iInUsed != 0) { // �����l�ݭn��s��
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
	if (_iInUsed != 0) { // �����l�ݭn��s��
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
	if (_iInUsed != 0) { // �����l�ݭn��s��
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
	if (_iInUsed != 0) { // �����l�ݭn��s��
		for (it = _InUsedList.begin(); it != _InUsedList.end(); it++) {
			(*it)->setRot(_fRot);
		}
	}
}
CParticleSystem::~CParticleSystem()
{
	if (_iInUsed != 0) _InUsedList.clear(); // �����Ҧ��� NODE
	if (_iFree != 0) _FreeList.clear();
	delete[] _pParticles; // ����Ҧ����o�귽
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("particletexture.plist");
}

void CParticleSystem::onTouchesBegan(const cocos2d::CCPoint &touchPoint)
{
	CParticle *get;
	switch (_iType)
	{
	case STAY_FOR_TWOSECONDS:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
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
		else return;// �S�����l, �ҥH�N������
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
		else return;// �S�����l, �ҥH�N������
		break;
	case FREE_FLY:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(FREE_FLY);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case EXPLOSION:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
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
		else return;// �S�����l, �ҥH�N������
		break;
	case HEARTSHAPE:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
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
		else return;// �S�����l, �ҥH�N������
		break;
	case BUTTERFLYSHAPE:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
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
		else return;// �S�����l, �ҥH�N������
		break;
	case STARSHAPE:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
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
		else return;// �S�����l, �ҥH�N������
		break;
	case SHAPE2:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
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
		else return;// �S�����l, �ҥH�N������
		break;
	case SHAPE3:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
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
		else return;// �S�����l, �ҥH�N������
		break;
	}
}

void CParticleSystem::onTouchesMoved(const cocos2d::CCPoint &touchPoint)
{
	CParticle *get;
	switch (_iType)
	{
	case STAY_FOR_TWOSECONDS:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(STAY_FOR_TWOSECONDS);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
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
		else return;// �S�����l, �ҥH�N������
		break;
	case FREE_FLY:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(FREE_FLY);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case SHAPE2:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setBehavior(SHAPE2);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	
	case SHAPE3:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
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
		else return;// �S�����l, �ҥH�N������
		break;

	}
}