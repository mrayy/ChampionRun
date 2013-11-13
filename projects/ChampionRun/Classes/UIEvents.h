

/********************************************************************
	created:	2013/11/13
	created:	13:11:2013   17:21
	filename: 	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\proj.win32\UIHelpers.h
	file path:	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\proj.win32
	file base:	UIHelpers
	file ext:	h
	author:		MHD Yamen Saraiji
	
	purpose:	
*********************************************************************/

#ifndef __UIHelpers__
#define __UIHelpers__


#include <cocos2d.h>
#include <cocos-ext.h>


struct ButtonEventHandler
{
	std::string name;
	cocos2d::extension::SEL_TouchEvent event;

	static cocos2d::extension::SEL_TouchEvent GetEvent(const std::string &name,const ButtonEventHandler* handlers, int count)
	{
		for (int i = 0; i < count; ++i)
		{
			if (name == handlers[i].name)
				return handlers[i].event;
		}
		return NULL;
	}

};




#endif
