

/********************************************************************
	created:	2013/11/14
	created:	14:11:2013   11:09
	filename: 	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes\UIMainMenuHandler.h
	file path:	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes
	file base:	UIMainMenuHandler
	file ext:	h
	author:		MHD Yamen Saraiji
	
	purpose:	
*********************************************************************/

#ifndef __UIMainMenuHandler__
#define __UIMainMenuHandler__


#include "IUIHandler.h"
#include "UIQuestMenuHandler.h"
#include "UIStatusMenuHandler.h"
#include "UIRankingMenuHandler.h"

namespace ChampionRun
{
	class IUIMainMenuListener
	{
	public:
		virtual void OnStartPress(){}
	};

class UIMainMenuHandler :public IUIHandler
{
protected:
	UIQuestMenuHandler* m_questHandler;
	UIRankingMenuHandler* m_rankingHandler;
	UIStatusMenuHandler* m_statusHandler;

	IUIMainMenuListener* m_listener;
public:
	UIMainMenuHandler();
	virtual~UIMainMenuHandler();

	void SetListener(IUIMainMenuListener* l){ m_listener = l; }

	virtual void init();

	virtual void SetPanel(UIWidget* panel);

	void OnWidgetLoaded(UIWidget* widget);

	void onKingdomPress(Object* pSender, TouchEventType event);
	void onStatusPress(Object* pSender, TouchEventType event);
	void onQuestPress(Object* pSender, TouchEventType event);
	void onStartPress(Object* pSender, TouchEventType event);
};

}


#endif
