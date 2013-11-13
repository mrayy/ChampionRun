

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




namespace ChampionRun
{
	enum class EQuestType
	{

	};
class CQuestDescription
{
protected:
	std::string m_name;
	std::string m_desc;

public:
	CQuestDescription(){}
	virtual~CQuestDescription(){}
};

}


#endif
