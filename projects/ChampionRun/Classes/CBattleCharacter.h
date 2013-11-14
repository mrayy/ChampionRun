

/********************************************************************
	created:	2013/11/14
	created:	14:11:2013   14:02
	filename: 	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes\CBattleCharacter.h
	file path:	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes
	file base:	CBattleCharacter
	file ext:	h
	author:		MHD Yamen Saraiji
	
	purpose:	
*********************************************************************/

#ifndef __CBattleCharacter__
#define __CBattleCharacter__

#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace ChampionRun
{
	enum class ECharacterDirection
	{
		Left,
		Right
	};

	class CBattleCharacter;
	class IBattleCharacterListener
	{
	public:
		virtual void OnDamaged(CBattleCharacter* c, float d){}
		virtual void OnAttack(CBattleCharacter* c, float ep,float d){}
		virtual void OnDie(CBattleCharacter* c){}
	};
class CBattleCharacter
{
protected:

	enum class ECommandType
	{
		EAttack
	};

	enum class EStatus
	{
		EIdle,
		EWalking,
		EAttacking,
		EDamaged,
		EDie
	};
	enum class EStatusState
	{
		EStarting,
		EUpdating,
		EEnding
	};

	EStatus m_status;
	EStatusState m_statusState;

	ECharacterDirection m_dir;
	EStatus m_targetStatus;
	armature::Armature* m_avatar;
	CBattleCharacter* m_target;
	Node* m_avatarNode;

	IBattleCharacterListener* m_listener;

	float m_maxHP;
	float m_maxEP;
	float m_hp;
	float m_ep;
	float m_armour;
	float m_power;

	std::string m_icon;

	std::list<ECommandType> m_commandQueue;

	bool _isCommandPresented(ECommandType t);

	void _endState();
	void SwitchToState(EStatus st);
	void _UpdateIdle(float dt);
	void _UpdateWalking(float dt);
	void _UpdateAttacking(float dt);
	void _UpdateDamaged(float dt);
	void _UpdateDie(float dt);

	void _doAttack();
public:
	CBattleCharacter();
	virtual~CBattleCharacter();

	void init(const std::string& name, const std::string& icon, IBattleCharacterListener* l);
	armature::Armature* GetAvatar(){ return m_avatar; }
	Node* GetNode(){ return m_avatarNode; }

	void SetDirection(ECharacterDirection dir);
	void Attack(CBattleCharacter* target);
	float GetDirSign(){ return m_dir == ECharacterDirection::Left ? 1 : -1; }

	float GetHP();
	float GetEP();
	float GetMaxHP(){ return m_maxHP; }
	float GetMaxEP(){ return m_maxEP; }
	float GetArmour();
	
	void SetPower(float p);

	bool IsDead(){ return m_hp == 0; }

	void EndTurn();

	float Damage(float amount);

	const std::string& GetIcon();

	void update(float dt);

};

}


#endif
