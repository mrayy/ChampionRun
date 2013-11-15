
#include "UIBattleAttack.h"
#include "Helpers.h"

namespace ChampionRun
{

	UIBattleAttack::UIBattleAttack()
	{
		m_time = 0;
		m_power = 0;
	}
	UIBattleAttack::~UIBattleAttack()
	{
	}

	void UIBattleAttack::init(IBattleAttackListener* l)
	{
		m_listener = l;
		m_UILayer = extension::UILayer::create();
		UIWidget*widget = CCUIHELPER->createWidgetFromJsonFile("UI/BattleAttackUI.ExportJson", 0);

		m_UILayer->addWidget(widget);

		UIButton* attackbtn = dynamic_cast<UIButton*>(widget->getChildByName("PushBtn"));
		m_powerGadget = dynamic_cast<UIImageView*>(widget->getChildByName("PowerGadget"));
		m_timeRing = dynamic_cast<UIImageView*>(widget->getChildByName("TimeRing"));

		attackbtn->addTouchEventListener(this, (SEL_TouchEvent)&UIBattleAttack::OnAttackPressed);
	}
	void UIBattleAttack::OnAttackPressed(Object* sender, TouchEventType e)
	{
		if (e == TouchEventType::TOUCH_EVENT_ENDED)
		{
			//m_power += m_power;
			m_listener->OnAttackPressed();
		}
	}


	void UIBattleAttack::SetPower(float p)
	{
		m_power = p;
		if (m_power > 1)m_power = 1;
		if (m_power < 0)m_power = 0;
		m_powerGadget->setScale(m_power);
	}
	void UIBattleAttack::SetTime01(float t)
	{
		m_time = t;
		float t_angle = m_time*90.0f;
		if (t_angle>90)
			t_angle = 90;
		m_timeRing->setRotation(90 - t_angle);
	}
}


