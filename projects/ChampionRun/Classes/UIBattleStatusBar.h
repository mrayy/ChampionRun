

/********************************************************************
	created:	2013/11/14
	created:	14:11:2013   23:47
	filename: 	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\proj.win32\UIBattleStatusBar.h
	file path:	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\proj.win32
	file base:	UIBattleStatusBar
	file ext:	h
	author:		MHD Yamen Saraiji
	
	purpose:	
*********************************************************************/

#ifndef __UIBattleStatusBar__
#define __UIBattleStatusBar__


#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace ChampionRun
{

	class CBattleCharacter;

class UIBattleStatusBar
{
protected:
	CBattleCharacter* m_character;
	UILayer* m_UILayer;

	UILoadingBar* m_hpBar;
	UILoadingBar* m_epBar;
	UIImageView* m_icon;
	UIImageView* m_weapon;
public:
	UIBattleStatusBar();
	virtual~UIBattleStatusBar();

	void init(CBattleCharacter* c);

	UILayer* GetLayer(){ return m_UILayer; }

	void updateStatus();

};

}


#endif
