
#include "CQuestManager.h"
#include "libs/tinyxml2.h"
#include "cocos2d.h"

namespace ChampionRun
{

	CQuestManager* CQuestManager::s_instance = 0;
void CQuestManager::init()
{
	tinyxml2::XMLDocument doc;
	std::string path = cocos2d::FileUtils::getInstance()->fullPathForFilename("CR_Quests.xml");
	if (doc.LoadFile(path.c_str()) == tinyxml2::XML_NO_ERROR)
	{
		const tinyxml2::XMLElement* quests = doc.FirstChildElement("Quests");
		if (quests)
		{
			const tinyxml2::XMLElement* q = quests->FirstChildElement("Quest");
			CQuestDescription quest;

			while (q)
			{
				if (quest.LoadXML(q))
				{
					m_quests.push_back(quest);
				}
				q = q->NextSiblingElement("Quest");
			}
		}
	}
}


}

