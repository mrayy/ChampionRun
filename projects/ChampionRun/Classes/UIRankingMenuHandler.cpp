

#include "UIRankingMenuHandler.h"

#include "QuestItemWidget.h"
#include "UIEvents.h"

namespace ChampionRun
{

	static const ButtonEventHandler RankingUIEvents[] =
	{
		{ "btnRankingBack", (SEL_TouchEvent)&UIRankingMenuHandler::onBackPressed },

	};
	static const int RankingUIEvents_cnt = sizeof(RankingUIEvents) / sizeof(ButtonEventHandler);

	UIRankingMenuHandler::UIRankingMenuHandler()
	{
	}

	UIRankingMenuHandler::~UIRankingMenuHandler()
	{
	}

	void UIRankingMenuHandler::init()
	{
		SetPanel(CCUIHELPER->createWidgetFromJsonFile("UI/RankingMenuUI.ExportJson", this));

	}
	void UIRankingMenuHandler::onBackPressed(Object* sender, TouchEventType event)
	{

		if (event == TouchEventType::TOUCH_EVENT_ENDED)
		{
			Pop();
		}
	}
	void UIRankingMenuHandler::SetPanel(UIWidget* panel)
	{
		IUIHandler::SetPanel(panel);
	}
	void UIRankingMenuHandler::OnWidgetLoaded(UIWidget* widget)
	{
		if (!widget->getName())
			return;

		std::string name = widget->getName();
		UIButton* btn = dynamic_cast<UIButton*>(widget);
		if (btn)
		{
			SEL_TouchEvent e = ButtonEventHandler::GetEvent(name, RankingUIEvents, RankingUIEvents_cnt);
			if (e)
				btn->addTouchEventListener(this, e);
		}
	}

}
