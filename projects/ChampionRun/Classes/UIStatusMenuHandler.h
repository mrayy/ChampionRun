

/********************************************************************
	created:	2013/11/14
	created:	14:11:2013   11:19
	filename: 	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes\UIStatusMenuHandler.h
	file path:	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes
	file base:	UIStatusMenuHandler
	file ext:	h
	author:		MHD Yamen Saraiji
	
	purpose:	
*********************************************************************/

#ifndef __UIStatusMenuHandler__
#define __UIStatusMenuHandler__



#include "IUIHandler.h"


namespace ChampionRun
{

class UIStatusMenuHandler :public IUIHandler
{
protected:
public:
	UIStatusMenuHandler();
	virtual~UIStatusMenuHandler();

	virtual void init();

	virtual void SetPanel(UIWidget* panel);

	void OnWidgetLoaded(UIWidget* widget);


	void onBackPressed(Object* pSender, TouchEventType event);
};

}


#endif
