

/********************************************************************
	created:	2013/11/14
	created:	14:11:2013   11:40
	filename: 	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes\CQuestManager.h
	file path:	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes
	file base:	CQuestManager
	file ext:	h
	author:		MHD Yamen Saraiji
	
	purpose:	
*********************************************************************/

#ifndef __CQuestManager__
#define __CQuestManager__

#include "CQuestDescription.h"
#include <vector>

namespace ChampionRun
{

class CQuestManager
{
	static CQuestManager* s_instance;
protected:
	std::vector<CQuestDescription> m_quests;

public:
	CQuestManager(){}
	virtual~CQuestManager(){}

	void init();


	const std::vector<CQuestDescription>& GetAvailableQuests(){ return m_quests; }

	static CQuestManager* instance()
	{
		if (!s_instance)
		{
			s_instance = new CQuestManager();
			s_instance->init();
		}
		return s_instance;
	}
};

}


#endif
