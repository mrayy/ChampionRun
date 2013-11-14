

/********************************************************************
	created:	2013/11/14
	created:	14:11:2013   10:38
	filename: 	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes\UIQuestMenuHandler.h
	file path:	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes
	file base:	UIQuestMenuHandler
	file ext:	h
	author:		MHD Yamen Saraiji
	
	purpose:	
*********************************************************************/

#ifndef __UIQuestMenuHandler__
#define __UIQuestMenuHandler__


#include "IUIHandler.h"
#include "QuestItemWidget.h"

namespace ChampionRun
{

class UIQuestMenuHandler :public IUIHandler,public IUIQuestEventListener
{
protected:
	UIScrollView* m_questList;
	UILabel* m_questDesc;
	QuestItemWidget* m_selectedQuest;
public:
	UIQuestMenuHandler();
	virtual~UIQuestMenuHandler();

	virtual void init();

	virtual void SetPanel(UIWidget* panel);

	void OnWidgetLoaded(UIWidget* widget);


	void onQuestBackPressed(Object* pSender, TouchEventType event);
	void onQuestConfirmPressed(Object* pSender, TouchEventType event);

	virtual void OnQuestSelected(QuestItemWidget* quest);

};

}


#endif
