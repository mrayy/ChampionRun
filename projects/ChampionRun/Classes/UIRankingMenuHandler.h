

/********************************************************************
	created:	2013/11/14
	created:	14:11:2013   11:19
	filename: 	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes\UIRankingMenuHandler.h
	file path:	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes
	file base:	UIRankingMenuHandler
	file ext:	h
	author:		MHD Yamen Saraiji
	
	purpose:	
*********************************************************************/

#ifndef __UIRankingMenuHandler__
#define __UIRankingMenuHandler__



#include "IUIHandler.h"


namespace ChampionRun
{

class UIRankingMenuHandler :public IUIHandler
{
protected:
public:
	UIRankingMenuHandler();
	virtual~UIRankingMenuHandler();

	virtual void init();

	virtual void SetPanel(UIWidget* panel);

	void OnWidgetLoaded(UIWidget* widget);


	void onBackPressed(Object* pSender, TouchEventType event);
};

}


#endif
