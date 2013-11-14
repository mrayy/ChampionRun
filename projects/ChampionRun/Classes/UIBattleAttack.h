

/********************************************************************
	created:	2013/11/15
	created:	15:11:2013   0:39
	filename: 	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\proj.win32\UIBattleAttack.h
	file path:	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\proj.win32
	file base:	UIBattleAttack
	file ext:	h
	author:		MHD Yamen Saraiji
	
	purpose:	
*********************************************************************/

#ifndef __UIBattleAttack__
#define __UIBattleAttack__



#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace ChampionRun
{
	class IBattleAttackListener
	{
	public:
		virtual void OnAttackPressed(){}
	};
	class UIBattleAttack:public Object
	{
	protected:
		UILayer* m_UILayer;
		IBattleAttackListener* m_listener;

		UIImageView* m_powerGadget;
		UIImageView* m_timeRing;

		float m_time;
		float m_power;
	public:
		UIBattleAttack();
		virtual~UIBattleAttack();

		void init(IBattleAttackListener* l);

		UILayer* GetLayer(){ return m_UILayer; }

		void OnAttackPressed(Object* sender, TouchEventType e);

		void SetPower(float p);
		void SetTime01(float t);
	};
}


#endif
