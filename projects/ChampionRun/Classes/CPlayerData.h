
/********************************************************************
	created:	2013/11/14
	created:	14:11:2013   9:49
	filename: 	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes\CPlayerData.h
	file path:	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes
	file base:	CPlayerData
	file ext:	h
	author:		MHD Yamen Saraiji
	
	purpose:	
*********************************************************************/

#ifndef __CPlayerData__
#define __CPlayerData__

#include "libs/tinyxml2.h"



namespace ChampionRun
{

class CPlayerData
{
protected:
	std::string m_name;
	int m_level;
	int m_hp;
	int m_ep;
public:
	CPlayerData(){}
	virtual~CPlayerData(){}

	void LoadXML(tinyxml2::XMLElement* e){}
};

}


#endif
