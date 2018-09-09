#include "ParticleSystemScene.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

Scene* ParticleSystemScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ParticleSystemScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

ParticleSystemScene::~ParticleSystemScene()
{
	this->removeAllChildren();
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

// on "init" you need to initialize your instance
bool ParticleSystemScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);

	// For Emitter
	_EmitterSprite = CDraggableSprite::create();
	_EmitterSprite->setSpriteInfo("emittericon.png", Point(-125.0f + visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	_EmitterSprite->setVisible(false);
	_bEmitterOn = false;
	this->addChild(_EmitterSprite, 5);

	auto emiterpos = (Sprite *)(rootNode->getChildByName("emitterpos"));
	Point loc = emiterpos->getPosition();
	emiterpos->setVisible(false);
	_emitterSwitchBtn = CSwitchButton::create();
	_emitterSwitchBtn->setButtonInfo("emitteroff.png", "emitteron.png", "emittertd.png", loc);
	this->addChild(_emitterSwitchBtn, 2);

	// Particle Control System
	// �̦n���覡�O�A�H�U�� Slider �ھڳo�̪��]�w�ȡA��ܥX���T���ƭȻP��m
	_ParticleControl.init(*this);
	_ParticleControl._emitterPt = _EmitterSprite->getLoc();
	_ParticleControl._fDir = 90.0;
	_ParticleControl._iNumParticles = 100;
	_ParticleControl._iGenParticles = 0;
	_ParticleControl._fSpread = 180.0f;
	_ParticleControl._fVelocity = 2.0f;	 // ���l�����}�t��
	_ParticleControl._fLifeTime = 3.5f;	 // ���l���s���ɶ�
	_ParticleControl._fSpin = 0.0f;
	_ParticleControl._fGravity = 0.0f;
	_ParticleControl._fElpasedTime = 0;
	_ParticleControl._fOpacity = 255.0f;
	_ParticleControl._color=Color3B (255,255,255);

	_ParticleControl.setType(STAY_FOR_TWOSECONDS); // ���l�B�ʪ����A�A�w�]�� 0
	_ParticleControl._windDir = Point(0, 0); // ���d�ҨS����@�����\��

	// ���l���i�վ�Ѽƪ����ʶb
	// Slider of Gravity
	auto *GravitySlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Gravity"));
	GravitySlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::GravityEvent, this));
	GravitySlider->setMaxPercent(100); 	// �N 0 �� 100 ������ -10 �� 10 ����
	_GravityBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("GravityBMFont");

	// Slider of Spread
	auto *SpreadSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Spread"));
	SpreadSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::SpreadEvent, this));
	SpreadSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 180 ����
	_SpreadBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("SpreadBMFont");

	// Slider of Direction
	auto *DirectionSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Direction"));
	DirectionSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::DirectionEvent, this));
	DirectionSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 360 ����
	_DirectionBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("DirectionBMFont");


	// Slider of Type
	auto *TypeSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Type"));
	TypeSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::TypeEvent, this));
	TypeSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 360 ����
	_TypeBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("TypeBMFont");

	// Slider of speed
	auto *SpeedSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Speed"));
	SpeedSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::SpeedEvent, this));
	SpeedSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 40 ����
	_SpeedBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("SpeedBMFont");

	// Slider of spin
	auto *SpinSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Spin"));
	SpinSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::SpinEvent, this));
	SpinSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 360 ����
	_SpinBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("SpinBMFont");

	// Slider of opacity
	auto *OpacitySlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Opacity"));
	OpacitySlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::OpacityEvent, this));
	OpacitySlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 255 ����
	_OpacityBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("OpacityBMFont");

	// Slider of particles
	auto *ParticlesSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Particles"));
	ParticlesSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::ParticlesEvent, this));
	ParticlesSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 200 ����
	_ParticlesBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("ParticlesBMFont");

	// Slider of lifetime
	auto *LifetimeSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Lifetime"));
	LifetimeSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::LifetimeEvent, this));
	LifetimeSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 7 ����
	_LifetimeBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("LifetimeBMFont");

	// Slider of red
	RedSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Red"));
	RedSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::ColorEvent, this));
	RedSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 255 ����
	_RedBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("RedBMFont");

	// Slider of green
	GreenSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Green"));
	GreenSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::ColorEvent, this));
	GreenSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 255 ����
	_GreenBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("GreenBMFont");

	// Slider of blue
	BlueSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Blue"));
	BlueSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::ColorEvent, this));
	BlueSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 255 ����
	_BlueBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("BlueBMFont");

	// Slider of wind
	auto *WindSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Wind"));
	WindSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::WindEvent, this));
	WindSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 255 ����
	_WindBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("WindBMFont");

	// Slider of emitter type
	auto *EmitterTypeSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_EmitterType"));
	EmitterTypeSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::EmitterTypeEvent, this));
	EmitterTypeSlider->setMaxPercent(100); 	// �N 0 �� 100 ������ 0 �� 255 ����
	_EmitterTypeBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("EmitterTypeBMFont");

	//btn of bubble
	Button *BubbleButton = dynamic_cast<Button*>(rootNode->getChildByName("Button_Bubble"));
	BubbleButton->addTouchEventListener(CC_CALLBACK_2(ParticleSystemScene::ButtonEvent, this));

	//btn of circle
	Button *CircleButton = dynamic_cast<Button*>(rootNode->getChildByName("Button_Circle"));
	CircleButton->addTouchEventListener(CC_CALLBACK_2(ParticleSystemScene::ButtonEvent, this));

	//btn of flare
	Button *FlareButton = dynamic_cast<Button*>(rootNode->getChildByName("Button_Flare"));
	FlareButton->addTouchEventListener(CC_CALLBACK_2(ParticleSystemScene::ButtonEvent, this));

	//btn of comet
	Button *CometButton = dynamic_cast<Button*>(rootNode->getChildByName("Button_Comet"));
	CometButton->addTouchEventListener(CC_CALLBACK_2(ParticleSystemScene::ButtonEvent, this));

	//btn of cloud
	Button *CloudButton = dynamic_cast<Button*>(rootNode->getChildByName("Button_Cloud"));
	CloudButton->addTouchEventListener(CC_CALLBACK_2(ParticleSystemScene::ButtonEvent, this));

	//btn of Firework
	Button *FireworkButton = dynamic_cast<Button*>(rootNode->getChildByName("Button_Firework"));
	FireworkButton->addTouchEventListener(CC_CALLBACK_2(ParticleSystemScene::FireworkEvent, this));

	CheckBox *checkBox = dynamic_cast<CheckBox*>(rootNode->getChildByName("Colorcheck"));
	checkBox->addEventListener(CC_CALLBACK_2(ParticleSystemScene::checkBoxTouchEvent, this));

	_listener1 = EventListenerTouchOneByOne::create();	//�Ыؤ@�Ӥ@��@���ƥ��ť��
	_listener1->onTouchBegan = CC_CALLBACK_2(ParticleSystemScene::onTouchBegan, this);		//�[�JĲ�I�}�l�ƥ�
	_listener1->onTouchMoved = CC_CALLBACK_2(ParticleSystemScene::onTouchMoved, this);		//�[�JĲ�I���ʨƥ�
	_listener1->onTouchEnded = CC_CALLBACK_2(ParticleSystemScene::onTouchEnded, this);		//�[�JĲ�I���}�ƥ�

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);	//�[�J��Ыت��ƥ��ť��
	this->schedule(CC_SCHEDULE_SELECTOR(ParticleSystemScene::doStep));

    return true;
}

void ParticleSystemScene::doStep(float dt)
{
	_ParticleControl.doStep(dt);
}

bool ParticleSystemScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//Ĳ�I�}�l�ƥ�
{
	Point touchLoc = pTouch->getLocation();
	//��� Emitter �ɡA�i�즲�ӹϦ�
	if( _bEmitterOn ) _EmitterSprite->touchesBegan(touchLoc);
	// �S����� Emitter�A�ӥB�S�����b Emitter �������s�W�A�~�� touch �i�H�I����ܤ��l
	if ( !_emitterSwitchBtn->touchesBegan(touchLoc) && !_bEmitterOn ) _ParticleControl.onTouchesBegan(touchLoc);
	return true;
}

void  ParticleSystemScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //Ĳ�I���ʨƥ�
{
	Point touchLoc = pTouch->getLocation();	
	if (_bEmitterOn) {
		if (_EmitterSprite->touchesMoved(touchLoc)) // ���ʨç�s Emitter ����m
			_ParticleControl._emitterPt = _EmitterSprite->getLoc();
	}
	// �S����� Emitter�A�ӥB�S�����b Emitter �������s�W�A�~�� touch �i�H�I����ܤ��l
	if ( !_emitterSwitchBtn->touchesMoved(touchLoc) && !_bEmitterOn ) _ParticleControl.onTouchesMoved(touchLoc);
}

void  ParticleSystemScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //Ĳ�I�����ƥ� 
{
	Point touchLoc = pTouch->getLocation();
	if (_bEmitterOn) {
		if( _EmitterSprite->touchesEnded(touchLoc) ) 
			_ParticleControl._emitterPt = _EmitterSprite->getLoc();
	}
	// �I�b Emitter �������ϥܤW�A�i�楲�n�����A����
	if (_emitterSwitchBtn->touchesEnded(touchLoc))
	{
		_bEmitterOn = _emitterSwitchBtn->getStatus();
		if ( _bEmitterOn ) { // ��� Emitter �ϥ�
			_EmitterSprite->setVisible(true);			
		}
		else { // ���� Emitter �ϥ�
			_EmitterSprite->setVisible(false);
		}
		_ParticleControl.setEmitter(_bEmitterOn); // ��s����t�Τ��� Emitter ���A
	}
	
}

void ParticleSystemScene::GravityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		float fGravity = (-50.0f + percent) / 5.0f;
		_GravityBMValue->setString(StringUtils::format("%2.1f", fGravity));
		_ParticleControl.setGravity(fGravity);
	}
}

void ParticleSystemScene::SpreadEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		float fSpread = percent*1.8f; // 0 �� 180 ����
		_SpreadBMValue->setString(StringUtils::format("%2.1f", fSpread));
		_ParticleControl.setSpread(fSpread);
	}
}

void ParticleSystemScene::DirectionEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		float fDir = percent*3.6f; // 0 �� 360 ����
		_DirectionBMValue->setString(StringUtils::format("%2.1f", fDir));
		_ParticleControl._fDir = fDir;
	}
}


void ParticleSystemScene::TypeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		int iType = percent/10; // 0 �� 360 ����
		_TypeBMValue->setString(StringUtils::format("%2d", iType));
		_ParticleControl.setType(iType);
	}
}

//speed event
void ParticleSystemScene::SpeedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		float fSpeed = percent /2.5f; // 0 �� 40 ����
		_SpeedBMValue->setString(StringUtils::format("%2.1f", fSpeed));
		_ParticleControl.setSpeed(fSpeed);
	}
}

//spin event
void ParticleSystemScene::SpinEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		float fSpin = percent * 3.6f; // 0 �� 360 ����
		_SpinBMValue->setString(StringUtils::format("%2.1f", fSpin));
		_ParticleControl.setSpin(fSpin);
	}
}
//opacity event
void ParticleSystemScene::OpacityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		float fOpacity = percent * 2.55f; // 0 �� 255 ����
		_OpacityBMValue->setString(StringUtils::format("%2.1f", fOpacity));
		_ParticleControl.setOpacity (fOpacity);
	}
}
//particles event
void ParticleSystemScene::ParticlesEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		int iParticles = percent * 2; // 0 �� 200 ����
		_ParticlesBMValue->setString(StringUtils::format("%3d", iParticles));
		_ParticleControl.setParticles(iParticles);
	}
}
//lifetime event
void ParticleSystemScene::LifetimeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		float fLifetime = percent *0.07f; // 0 �� 7 ����
		_LifetimeBMValue->setString(StringUtils::format("%2.1f", fLifetime));
		_ParticleControl.setLifetime(fLifetime);
	}
}
//color event
void ParticleSystemScene::ColorEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		
		int percent1 = RedSlider->getPercent();
		int maxPercent1 = RedSlider->getMaxPercent();
		float fRed = percent1 *2.55f; // 0 �� 255 ����
		_RedBMValue->setString(StringUtils::format("%2.0f", fRed));

		
		int percent2 =GreenSlider->getPercent();
		int maxPercent2 = GreenSlider->getMaxPercent();
		float fGreen = percent2 *2.55f; // 0 �� 255 ����
		_GreenBMValue->setString(StringUtils::format("%2.0f", fGreen));

		
		int percent3 = BlueSlider->getPercent();
		int maxPercent3 = BlueSlider->getMaxPercent();
		float fBlue = percent3 *2.55f; // 0 �� 255 ����
		_BlueBMValue->setString(StringUtils::format("%2.0f", fBlue));
		_ParticleControl.setColor(fRed, fGreen, fBlue);

		
	}
}
//lifetime event
void ParticleSystemScene::WindEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		float fWind =(-50.0f+ percent)/50.0f; // -1 �� 1 ����
		_WindBMValue->setString(StringUtils::format("%2.1f", fWind));
		_ParticleControl.setWind(fWind);
	}
}
//emitter type event
void ParticleSystemScene::EmitterTypeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		int iType = percent / 20 ; // 0 �� 5 ����
		_EmitterTypeBMValue->setString(StringUtils::format("%2d", iType));
		_ParticleControl.setEmitterType(iType);
	}
}
//btn event
void ParticleSystemScene::ButtonEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type) {
	const char *pngName;
		if (type == Widget::TouchEventType::BEGAN){
			Button* btn = dynamic_cast<Button*>(pSender);
			string btnName= btn->getName();
			if (btnName == "Button_Bubble") {
				pngName = "bubble.png";
			}
			else if (btnName == "Button_Circle") {
				pngName = "circle.png";
			}
			else if (btnName == "Button_Flare") {
				pngName = "flare.png";
			}
			else if (btnName == "Button_Comet") {
				pngName = "raindrop.png";
			}
			else if (btnName == "Button_Cloud") {
				pngName = "cloud.png";
			}
			_ParticleControl.setPic(pngName,*this);
	}
}

void ParticleSystemScene::FireworkEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::BEGAN) {
		_ParticleControl.setPic("spark.png", *this);
		_ParticleControl._bSpark = true;
		_ParticleControl._iSparkPart = 1;
		_ParticleControl._fSparkTimer = 0.0f;
	}
}

void ParticleSystemScene::checkBoxTouchEvent(cocos2d::Ref* object, cocos2d::ui::CheckBox::EventType type) {
	bool _bRand;
	switch (type) {
	case CheckBox::EventType::SELECTED:
		CCLOG("Selected");
		_bRand = true; 
		break;
	case CheckBox::EventType::UNSELECTED:
		CCLOG("Unselected");
		_bRand = false; 
		break;
	}
	_ParticleControl.isColorRandom(_bRand);
}