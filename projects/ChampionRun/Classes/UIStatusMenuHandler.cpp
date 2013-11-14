

#include "UIStatusMenuHandler.h"

#include "QuestItemWidget.h"
#include "UIEvents.h"

namespace ChampionRun
{

	static const ButtonEventHandler StatusUIEvents[] =
	{
		{ "btnStatusBack", (SEL_TouchEvent)&UIStatusMenuHandler::onBackPressed },

	};
	static const int StatusUIEvents_cnt = sizeof(StatusUIEvents) / sizeof(ButtonEventHandler);

	UIStatusMenuHandler::UIStatusMenuHandler()
	{
	}

	UIStatusMenuHandler::~UIStatusMenuHandler()
	{
	}

	void UIStatusMenuHandler::init()
	{
		SetPanel(CCUIHELPER->createWidgetFromJsonFile("ui/StatusMenuUI.ExportJson", this));

	}
	void UIStatusMenuHandler::onBackPressed(Object* sender, TouchEventType event)
	{

		if (event == TouchEventType::TOUCH_EVENT_ENDED)
		{
			Pop();
		}
	}
	void UIStatusMenuHandler::SetPanel(UIWidget* panel)
	{
		IUIHandler::SetPanel(panel);
	}
	void UIStatusMenuHandler::OnWidgetLoaded(UIWidget* widget)
	{
		if (!widget->getName())
			return;

		std::string name = widget->getName();
		UIButton* btn = dynamic_cast<UIButton*>(widget);
		if (btn)
		{
			SEL_TouchEvent e = ButtonEventHandler::GetEvent(name, StatusUIEvents, StatusUIEvents_cnt);
			if (e)
				btn->addTouchEventListener(this, e);
		}
	}

}
