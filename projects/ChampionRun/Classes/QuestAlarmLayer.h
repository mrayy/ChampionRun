

/********************************************************************
created:	2013/11/14
created:	14:11:2013   12:54
filename: 	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes\QuestAlarmLayer.h
file path:	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes
file base:	QuestAlarmLayer
file ext:	h
author:		MHD Yamen Saraiji

purpose:
*********************************************************************/

#ifndef __QuestAlarmLayer__
#define __QuestAlarmLayer__


#include <iostream>
#include "CommonLayer.h"
#include "cocos-ext.h"


namespace ChampionRun
{
	class QuestAlarmLayer :public CommonLayer, public ISceneReaderListener
	{
	protected:
		Sprite* m_alarmIcon;
		float m_time;
	public:
		QuestAlarmLayer();
		virtual~QuestAlarmLayer();
		virtual bool init();

		static cocos2d::Scene* scene();

		static void registerLoader();

		void switchToNextScreen();

		void onTouchesBegan(const std::vector<Touch*>& pTouches, Event *event);


		void OnNodeLoaded(Node* node);

		void update(float dt);

		CREATE_FUNC(QuestAlarmLayer);
	};

}

#endif
