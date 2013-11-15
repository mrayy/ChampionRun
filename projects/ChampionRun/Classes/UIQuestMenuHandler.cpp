
#include "UIQuestMenuHandler.h"

#include "QuestItemWidget.h"
#include "UIEvents.h"
#include "CQuestManager.h"

namespace ChampionRun
{

	static const ButtonEventHandler QuestUIEvents[] =
	{
		{ "btnQuestBack", (SEL_TouchEvent)&UIQuestMenuHandler::onQuestBackPressed },
		{ "btnQuestConfirm", (SEL_TouchEvent)&UIQuestMenuHandler::onQuestConfirmPressed },

	};
	static const int QuestUIEvents_cnt = sizeof(QuestUIEvents) / sizeof(ButtonEventHandler);

	UIQuestMenuHandler::UIQuestMenuHandler()
	{
		m_selectedQuest = 0;
	}

	UIQuestMenuHandler::~UIQuestMenuHandler()
	{
	}

	void UIQuestMenuHandler::init()
	{
		SetPanel(CCUIHELPER->createWidgetFromJsonFile("UI/QuestMenuUI.ExportJson", this));

	}
	void UIQuestMenuHandler::onQuestBackPressed(Object* sender, TouchEventType event)
	{

		if (event == TouchEventType::TOUCH_EVENT_ENDED)
		{
			Pop();
		}
	}
	void UIQuestMenuHandler::onQuestConfirmPressed(Object* sender, TouchEventType event)
	{

		if (event == TouchEventType::TOUCH_EVENT_ENDED)
			CCLOG("onQuestConfirmPressed\n");
	}

	void UIQuestMenuHandler::SetPanel(UIWidget* panel)
	{
		IUIHandler::SetPanel(panel);
		m_questList = dynamic_cast<UIScrollView*>(m_panel->getChildByName("qstQuestList"));
		m_questDesc = dynamic_cast<UILabel*>(m_panel->getChildByName("qstDescription"));

		const std::vector<CQuestDescription>& quests = CQuestManager::instance()->GetAvailableQuests();
		for (int i = 0; i < quests.size(); ++i)
		{
			QuestItemWidget*label = QuestItemWidget::create();
			label->SetDesc(&quests[i]);
			label->setAnchorPoint(Point(0, 0));
			/*label->setFontSize(24);
			label->setText("This is a text");*/
			label->setPosition(Point(0, i*label->getSize().height));
			label->SetListener(this);
			m_questList->addChild(label);
		}
	}
	void UIQuestMenuHandler::OnWidgetLoaded(UIWidget* widget)
	{
		if (!widget->getName())
			return;

		std::string name = widget->getName();
		/*if (name == "RootQuest")
		{
			SetPanel(widget);
		}*/
		UIButton* btn = dynamic_cast<UIButton*>(widget);
		if (btn)
		{
			SEL_TouchEvent e = ButtonEventHandler::GetEvent(name, QuestUIEvents, QuestUIEvents_cnt);
			if (e)
				btn->addTouchEventListener(this, e);
		}
	}
	void UIQuestMenuHandler::OnQuestSelected(QuestItemWidget* quest)
	{
		if (m_selectedQuest)
			m_selectedQuest->SetSelected(false);
		m_questDesc->setText(quest->GetDesc()->GetDescription().c_str());
		m_selectedQuest = quest;
		m_selectedQuest->SetSelected(true);
	}

}