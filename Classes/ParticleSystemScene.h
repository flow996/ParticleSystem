#ifndef __PARTICLESYSTEM_SCENE_H__
#define __PARTICLESYSTEM_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "cparticlesystem.h"
#include "Common/CSwitchButton.h"
#include  "Common/CDraggableSprite.h"


class ParticleSystemScene : public cocos2d::Layer
{
private:
	// ���l���i���㤣�P�Ѽƪ����
	cocos2d::ui::TextBMFont *_GravityBMValue;
	cocos2d::ui::TextBMFont *_SpreadBMValue;
	cocos2d::ui::TextBMFont *_DirectionBMValue;
	cocos2d::ui::TextBMFont *_SpeedBMValue;//speed
	cocos2d::ui::TextBMFont *_SpinBMValue;//spin
	cocos2d::ui::TextBMFont *_OpacityBMValue;//opacity
	cocos2d::ui::TextBMFont *_ParticlesBMValue;//Particles
	cocos2d::ui::TextBMFont *_LifetimeBMValue;//lifetime
	cocos2d::ui::TextBMFont *_RedBMValue;//red
	cocos2d::ui::TextBMFont *_GreenBMValue;//green
	cocos2d::ui::TextBMFont *_BlueBMValue;//blue
	cocos2d::ui::TextBMFont *_WindBMValue;//wind
	cocos2d::ui::TextBMFont *_EmitterTypeBMValue;//wind

	cocos2d::ui::Slider* RedSlider;//slider
	cocos2d::ui::Slider* GreenSlider;
	cocos2d::ui::Slider* BlueSlider;


	// ��ܤ��P�����l���A�A�Φb Emitter �S���}�Ҫ����A
	cocos2d::ui::TextBMFont *_TypeBMValue;

	// For Emitter
	CDraggableSprite *_EmitterSprite;
	bool _bEmitterOn;
	CSwitchButton *_emitterSwitchBtn;
	


public:

	CParticleSystem _ParticleControl;

	~ParticleSystemScene();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	void doStep(float dt);

	cocos2d::EventListenerTouchOneByOne *_listener1;
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //Ĳ�I�}�l�ƥ�
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //Ĳ�I���ʨƥ�
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //Ĳ�I�����ƥ� 

	void GravityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SpreadEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void DirectionEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SpeedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);//speed event
	void SpinEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);//spin event
	void OpacityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);//Opacity event
	void ParticlesEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);//Particles Event
	void LifetimeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);//lifetime Event
	void ColorEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);//red Event
	void ButtonEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);//btn event
	void WindEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);//wind Event
	void FireworkEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);//firework event
	void EmitterTypeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);//emitter type event

	void TypeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);

	void checkBoxTouchEvent(cocos2d::Ref* object, cocos2d::ui::CheckBox::EventType type);
    // implement the "static create()" method manually
    CREATE_FUNC(ParticleSystemScene);
};

#endif // __MAIN_SCENE_H__
