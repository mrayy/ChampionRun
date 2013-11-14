
/********************************************************************
	created:	2013/11/14
	created:	14:11:2013   9:50
	filename: 	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes\CItem.h
	file path:	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes
	file base:	CItem
	file ext:	h
	author:		MHD Yamen Saraiji
	
	purpose:	
*********************************************************************/

#ifndef __CItem__
#define __CItem__

#include "libs/tinyxml2.h"



namespace ChampionRun
{
	enum class EItemType
	{
		Consumable,
		Weapon,
		Armour,
		Pet,
		Magic
	};
class CItem
{
protected:
	std::string m_name;
	EItemType m_type;
public:
	CItem(){}
	virtual~CItem(){}
	void LoadXML(tinyxml2::XMLElement* e){}
};

}


#endif
