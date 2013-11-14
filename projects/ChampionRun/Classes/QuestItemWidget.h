

/********************************************************************
	created:	2013/11/13
	created:	13:11:2013   18:49
	filename: 	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\proj.win32\QuestItemWidget.h
	file path:	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\proj.win32
	file base:	QuestItemWidget
	file ext:	h
	author:		MHD Yamen Saraiji
	
	purpose:	
*********************************************************************/

#ifndef __QuestItemWidget__
#define __QuestItemWidget__

#include "cocos-ext.h"
#include "CQuestDescription.h"


namespace cocos2d
{
	USING_NS_CC_EXT;

	class QuestItemWidget;

	class IUIQuestEventListener
	{
	public:
		virtual void OnQuestSelected(QuestItemWidget* quest){}
	};

class QuestItemWidget:public UIWidget
{
protected:
	const ChampionRun::CQuestDescription* m_desc;
	UIImageView* m_questIcon;
	UILabel* m_questName;

	Layout* m_panelRoot;

	IUIQuestEventListener* m_listener;
	void onQuestPressed(Object* pSender, TouchEventType event);

public:
	QuestItemWidget();
	virtual~QuestItemWidget();
	bool init();
	void SetDesc(const ChampionRun::CQuestDescription* desc);
	const ChampionRun::CQuestDescription* GetDesc(){ return m_desc; }
	void SetListener(IUIQuestEventListener* l){ m_listener = l; }

	void SetSelected(bool selected);

	static QuestItemWidget* create()
	{
		QuestItemWidget* ret = new QuestItemWidget();
		if (ret && ret->init())
			return ret;
		delete ret;
		return 0;
	}
};

}


#endif
