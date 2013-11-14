

/********************************************************************
	created:	2013/11/14
	created:	14:11:2013   12:54
	filename: 	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes\BattleLayer.h
	file path:	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes
	file base:	BattleLayer
	file ext:	h
	author:		MHD Yamen Saraiji
	
	purpose:	
*********************************************************************/

#ifndef __BattleLayer__
#define __BattleLayer__


#include <iostream>
#include "CommonLayer.h"
#include "cocos-ext.h"
#include "CBattleCharacter.h"
#include "UIBattleAttack.h"


namespace ChampionRun
{
	class UIBattleStatusBar;
class BattleLayer :public CommonLayer,  public ISceneReaderListener,public IBattleCharacterListener,public IBattleAttackListener
{
protected:
	Node* m_enemyStatusNode;
	Node* m_playerStatusNode;
	Node* m_enemyNode;
	Node* m_playerNode;

	ChampionRun::CBattleCharacter* m_player;
	ChampionRun::CBattleCharacter* m_enemy;

	UIBattleStatusBar* m_playerUI;
	UIBattleStatusBar* m_enemyUI;

	UIBattleAttack* m_attackUI;

	float m_turnTime;
	float m_power;
public:
	BattleLayer();
	virtual~BattleLayer();
	virtual bool init();

	static cocos2d::Scene* scene();

	static void registerLoader();

	void switchToNextScreen();

	void OnNodeLoaded(Node* node);

	void update(float dt);

	void OnAttackPressed();

	virtual void OnDamaged(CBattleCharacter* c, float d);
	virtual void OnAttack(CBattleCharacter* c, float ep, float d);
	virtual void OnDie(CBattleCharacter* c);

	CREATE_FUNC(BattleLayer);
};


}

#endif
