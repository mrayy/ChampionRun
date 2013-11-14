

/********************************************************************
	created:	2013/11/13
	created:	13:11:2013   18:50
	filename: 	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\proj.win32\CQuestDescription.h
	file path:	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\proj.win32
	file base:	CQuestDescription
	file ext:	h
	author:		MHD Yamen Saraiji
	
	purpose:	
*********************************************************************/

#ifndef __CQuestDescription__
#define __CQuestDescription__


#include "libs/tinyxml2.h"
#include <string>


namespace ChampionRun
{
	enum class EQuestType
	{
		Run,
		Explore,
		FightBoss,
		Dungeon
	};
class CQuestDescription
{
protected:
	std::string m_name;
	std::string m_desc;
	EQuestType m_type;
	int m_requiredLevel;
public:
	CQuestDescription(){}
	virtual~CQuestDescription(){}


	const std::string& GetName()const{ return m_name; }
	const std::string& GetDescription()const{ return m_desc; }
	EQuestType GetType()const{ return m_type; }
	int GetRequiredLevel()const{ return m_requiredLevel; }

	bool LoadXML(const tinyxml2::XMLElement* e)
	{
		const tinyxml2::XMLElement* elem;
		elem = e->FirstChildElement("Name");
		if (!elem)
			return false;

		m_name = elem->GetText();
		elem = e->FirstChildElement("Desc");
		if (!elem)
			return false;
		m_desc = elem->GetText();

		elem = e->FirstChildElement("Type");
		if (!elem)
			return false;
		std::string type = elem->GetText();
		if (type == "Run")
			m_type = EQuestType::Run;
		else if (type == "Explore")
			m_type = EQuestType::Explore;
		else if (type == "Boss")
			m_type = EQuestType::FightBoss;
		else if (type == "Dungeon")
			m_type = EQuestType::Dungeon;
		else return false;

		return true;
	}
};

}


#endif
