
#include "UIMainMenuHandler.h"

#include "UIEvents.h"


namespace ChampionRun
{

	static const ButtonEventHandler MainMenuUIEvents[] =
	{
		{ "btnQuest", (SEL_TouchEvent)&UIMainMenuHandler::onQuestPress },
		{ "btnStatus", (SEL_TouchEvent)&UIMainMenuHandler::onStatusPress },
		{ "btnKingdom", (SEL_TouchEvent)&UIMainMenuHandler::onKingdomPress },
		{ "btnStart", (SEL_TouchEvent)&UIMainMenuHandler::onStartPress }
	};
	static const int MainMenuUIEvents_cnt = sizeof(MainMenuUIEvents) / sizeof(ButtonEventHandler);

	UIMainMenuHandler::UIMainMenuHandler()
	{
	}

	UIMainMenuHandler::~UIMainMenuHandler()
	{
		delete m_questHandler;
		delete m_statusHandler;
		delete m_rankingHandler;
	}

	void UIMainMenuHandler::init()
	{
		SetPanel(CCUIHELPER->createWidgetFromJsonFile("ui/MainMenuUI.ExportJson", this));
		m_questHandler = new UIQuestMenuHandler();
		m_questHandler->init();
		m_statusHandler= new UIStatusMenuHandler();
		m_statusHandler->init();

		m_rankingHandler = new UIRankingMenuHandler();
		m_rankingHandler->init();
	}
	void UIMainMenuHandler::onKingdomPress(Object* pSender, TouchEventType event)
	{

		if (event == TouchEventType::TOUCH_EVENT_ENDED)
		{
			m_root->removeWidget(m_panel);
			m_rankingHandler->Push(this, m_root);
		}
	}
	void UIMainMenuHandler::onStatusPress(Object* pSender, TouchEventType event)
	{

		if (event == TouchEventType::TOUCH_EVENT_ENDED)
		{
			m_root->removeWidget(m_panel);
			m_statusHandler->Push(this, m_root);
		}
	}
	void UIMainMenuHandler::onQuestPress(Object* pSender, TouchEventType event)
	{

		if (event == TouchEventType::TOUCH_EVENT_ENDED)
		{
			m_root->removeWidget(m_panel);
			m_questHandler->Push(this, m_root);
		}

	}
	void UIMainMenuHandler::onStartPress(Object* sender, TouchEventType event)
	{

		if (event == TouchEventType::TOUCH_EVENT_ENDED)
		{
			if (m_listener)
				m_listener->OnStartPress();
			//m_yusha->PlayStart();
		}
	}

	void UIMainMenuHandler::SetPanel(UIWidget* panel)
	{
		IUIHandler::SetPanel(panel);
	}
	void UIMainMenuHandler::OnWidgetLoaded(UIWidget* widget)
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
			SEL_TouchEvent e = ButtonEventHandler::GetEvent(name, MainMenuUIEvents, MainMenuUIEvents_cnt);
			if (e)
				btn->addTouchEventListener(this, e);
		}
	}

}