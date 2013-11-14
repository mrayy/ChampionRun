

#include "QuestItemWidget.h"

namespace cocos2d
{
	QuestItemWidget::QuestItemWidget()
	{
		m_listener = 0;
	}
	QuestItemWidget::~QuestItemWidget()
	{
	}
	void QuestItemWidget::onQuestPressed(Object* pSender, TouchEventType event)
	{
		if (event != TouchEventType::TOUCH_EVENT_ENDED)
			return;
		if (m_listener)
			m_listener->OnQuestSelected(this);
	}
	bool QuestItemWidget::init()
	{
		if (!UIWidget::init())
			return false;
		UIWidget* widget = CCUIHELPER->createWidgetFromJsonFile("ui/QuestItemUI.ExportJson", 0);
		if (!widget)
			return false;
		m_panelRoot = dynamic_cast<Layout*>(widget->getChildByName("QuestRoot"));
		m_panelRoot->retain();
		m_panelRoot->removeFromParent();
		widget->release();
		addChild(m_panelRoot);
		ignoreContentAdaptWithSize(false);
		this->setSize(m_panelRoot->getSize());

		m_panelRoot->setTouchEnabled(true);
		m_panelRoot->addTouchEventListener(this, (SEL_TouchEvent)&QuestItemWidget::onQuestPressed);

		m_questIcon = dynamic_cast<UIImageView*>(m_panelRoot->getChildByName("QuestIconImage"));
		m_questName = dynamic_cast<UILabel*>(m_panelRoot->getChildByName("QuestName"));
		SetSelected(false);

		return true;
	}
	void QuestItemWidget::SetDesc(const ChampionRun::CQuestDescription* desc)
	{
		m_desc = desc;
		m_questName->setText(m_desc->GetName().c_str());

		switch (desc->GetType())
		{
		case ChampionRun::EQuestType::Run:
			m_questIcon->loadTexture("icons/quest_running.png", UI_TEX_TYPE_PLIST);
			break;
		case ChampionRun::EQuestType::Explore:
			m_questIcon->loadTexture("icons/quest_advanture.png", UI_TEX_TYPE_PLIST);
			break;
		case ChampionRun::EQuestType::FightBoss:
			m_questIcon->loadTexture("icons/quest_battle.png", UI_TEX_TYPE_PLIST);
			break;
		default:
			break;
		}
	}
	void QuestItemWidget::SetSelected(bool selected)
	{
		if (selected)
		{
			m_panelRoot->setBackGroundColorOpacity(255);
		}
		else
		{
			m_panelRoot->setBackGroundColorOpacity(100);
		}
	}

}
