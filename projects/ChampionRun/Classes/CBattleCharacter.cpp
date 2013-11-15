

#include "CBattleCharacter.h"
#include "SceneManager.h"

namespace ChampionRun
{
	const float CharacterSpeed = 300;
#define sign(x)(x>=0?1:-1)
	CBattleCharacter::CBattleCharacter()
	{
		m_armour = 1.6;
		m_maxHP= m_hp = 100;
		m_maxEP= m_ep = 100;

		m_status = EStatus::EIdle;
		m_statusState = EStatusState::EStarting;

		m_dir = ECharacterDirection::Left;
		m_power = 0;
	}
	CBattleCharacter::~CBattleCharacter()
	{
	}

	void CBattleCharacter::SwitchToState(EStatus st)
	{
		m_statusState = EStatusState::EEnding;
		m_targetStatus = st;
	}

	void CBattleCharacter::init(const std::string& name, const std::string& icon, IBattleCharacterListener*l)
	{
		m_icon = icon;
		m_listener = l;
		m_avatar = SceneManager::instance()->LoadArmature(name);
		m_avatar->setAnchorPoint(Point(0.5, 0));
		m_avatarNode = Node::create();
		m_avatarNode->addChild(m_avatar);
		Size sz = m_avatar->getContentSize();
		sz.width *= abs(m_avatar->getScaleX());
		sz.height *= abs(m_avatar->getScaleY());
		m_avatarNode->setContentSize(sz);
	}
	void CBattleCharacter::SetDirection(ECharacterDirection dir)
	{
		m_dir = dir;
		m_avatarNode->setScaleX(GetDirSign());
	}
	void CBattleCharacter::Attack(CBattleCharacter* target)
	{
		if (m_status == EStatus::EAttacking || _isCommandPresented(ECommandType::EAttack))
			return;
		m_commandQueue.push_back(ECommandType::EAttack);
		m_target = target;
		SwitchToState(EStatus::EWalking);
	}

	float CBattleCharacter::GetHP()
	{
		return m_hp;
	}
	float CBattleCharacter::GetEP()
	{
		return m_ep;
	}

	float CBattleCharacter::GetArmour()
	{
		return m_armour;
	}
	void CBattleCharacter::SetPower(float p)
	{
		m_power = p;
	}


	float CBattleCharacter::Damage(float amount)
	{
		float d = amount / m_armour;
		m_hp -= d;
		if (m_hp <= 0)
		{
			if (m_listener)
				m_listener->OnDie(this);
			m_hp = 0;
			SwitchToState(EStatus::EDie);
		}
		else
		{
			if (m_listener)
				m_listener->OnDamaged(this, d);
			if (m_status != EStatus::EDamaged)
			{
				SwitchToState(EStatus::EDamaged);
			}
		}

		return d;

	}
	void CBattleCharacter::EndTurn()
	{
		m_target = 0;
		SwitchToState(EStatus::EWalking);
	}

	const std::string& CBattleCharacter::GetIcon()
	{
		return m_icon;
	}
	bool CBattleCharacter::_isCommandPresented(CBattleCharacter::ECommandType t)
	{
		std::list<ECommandType>::iterator it = m_commandQueue.begin();
		for (; it != m_commandQueue.end(); ++it)
		{
			if ((*it)== t)
				return true;
		}
		return false;
	}
	void CBattleCharacter::_endState()
	{
		m_status = m_targetStatus;
		m_statusState = EStatusState::EStarting;
	}

	void CBattleCharacter::_doAttack()
	{
		float d = 30 * m_power;
		float e = 10 * m_power;
		m_target->Damage(d);
		m_ep -= e;
		if (m_listener)
			m_listener->OnAttack(this, e, d);
	}

	void CBattleCharacter::_UpdateIdle(float dt)
	{
		switch (m_statusState)
		{
		case EStatusState::EStarting:
			m_avatar->getAnimation()->play("stand");
			m_statusState = EStatusState::EUpdating;
			break;
		case EStatusState::EUpdating:
			break;
		case EStatusState::EEnding:
			_endState();
			break;
		default:
			break;
		}
	}
	void CBattleCharacter::_UpdateWalking(float dt)
	{
		if (!m_target)
			return;
		float targetX = 0;
		float minDist = 0;

		if (m_target)
		{
			Node* target = m_target->GetNode();
			targetX = target->convertToWorldSpace(target->getPosition()).x;
			minDist = m_avatarNode->getContentSize().width + m_target->GetNode()->getContentSize().width;
			minDist /= 4;
		}
		float pos = m_avatarNode->convertToWorldSpace(Point(0,0)).x;
		float dp;
		dp = pos - targetX;
		float dx = CharacterSpeed*dt*sign(dp);

		switch (m_statusState)
		{
		case EStatusState::EStarting:
			m_avatar->getAnimation()->play("run");
			m_statusState = EStatusState::EUpdating;
			break;
		case EStatusState::EUpdating:
			//dp = pos - targetX;
			if (pos-dx<= minDist+targetX)
			{
				dx=pos-(minDist+targetX);
				m_statusState = EStatusState::EEnding;
			}
			dx *= GetDirSign();
			m_avatarNode->setPositionX(m_avatarNode->getPositionX() + dx);

			break;
		case EStatusState::EEnding:
			if (m_target)
				SwitchToState(EStatus::EAttacking);
			else 
				SwitchToState(EStatus::EIdle);
			_endState();
			break;
		default:
			break;
		}
	}
	void CBattleCharacter::_UpdateAttacking(float dt)
	{
		if (!m_target || m_target->IsDead())
		{
			if (m_statusState == EStatusState::EStarting)
			{
				if (!m_commandQueue.empty())
					m_commandQueue.erase(m_commandQueue.begin());
			}
			m_target = 0;
			m_targetStatus = EStatus::EWalking;
			_endState();
			return;
		}
		switch (m_statusState)
		{
		case EStatusState::EStarting:
			m_avatar->getAnimation()->play("attack");
			if (!m_commandQueue.empty())
				m_commandQueue.erase(m_commandQueue.begin());
			_doAttack();
			m_statusState = EStatusState::EUpdating;
			break;
		case EStatusState::EUpdating:
			if (m_avatar->getAnimation()->getIsComplete())
				m_statusState = EStatusState::EEnding;
			break;
		case EStatusState::EEnding:
		//	EndTurn();
			SwitchToState(EStatus::EIdle);
			_endState();
			break;
		default:
			break;
		}
	}
	void CBattleCharacter::_UpdateDamaged(float dt)
	{
		switch (m_statusState)
		{
		case EStatusState::EStarting:
			m_avatar->getAnimation()->play("damage");
			m_statusState = EStatusState::EUpdating;
			break;
		case EStatusState::EUpdating:
			if (m_avatar->getAnimation()->getIsComplete())
				m_statusState = EStatusState::EEnding;
			break;
		case EStatusState::EEnding:
			SwitchToState(EStatus::EIdle);
			_endState();
			break;
		default:
			break;
		}
	}
	void CBattleCharacter::_UpdateDie(float dt)
	{
		switch (m_statusState)
		{
		case EStatusState::EStarting:
			m_avatar->getAnimation()->play("dead");
			m_statusState = EStatusState::EUpdating;
			break;
		case EStatusState::EUpdating:
			if (m_avatar->getAnimation()->getIsComplete())
				m_statusState = EStatusState::EEnding;
			break;
		case EStatusState::EEnding:
			//_endState();
			break;
		default:
			break;
		}

	}
	void CBattleCharacter::update(float dt)
	{
		switch (m_status)
		{
		case EStatus::EIdle:
			_UpdateIdle(dt);
			break;;
		case EStatus::EWalking:
			_UpdateWalking(dt);
			break;;
		case EStatus::EAttacking:
			_UpdateAttacking(dt);
			break;;
		case EStatus::EDamaged:
			_UpdateDamaged(dt);
			break;;
		case EStatus::EDie:
			_UpdateDie(dt);
			break;;
		default:
			break;
		}
	}


}

