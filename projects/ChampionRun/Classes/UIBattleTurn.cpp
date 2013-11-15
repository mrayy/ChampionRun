

#include "UIBattleTurn.h"


namespace ChampionRun
{
    
	UIBattleTurn::UIBattleTurn()
	{
	}
	UIBattleTurn::~UIBattleTurn()
	{
	}
    
	void UIBattleTurn::init()
	{
		m_UILayer = extension::UILayer::create();
		UIWidget*widget = CCUIHELPER->createWidgetFromJsonFile("UI/TurnUI.ExportJson", 0);
        
		Layout* status = dynamic_cast<Layout*>(widget->getChildByName("TurnPanel"));
		status->retain();
		status->removeFromParent();
		widget->release();
		
        status->setPosition(Point(0, 0));
		status->setAnchorPoint(Point(0.5, 0.5));
		m_UILayer->setPosition(Point(0.5, 0.5));
		m_UILayer->setAnchorPoint(Point(0, 1));
        
		m_UILayer->addWidget(status);
        
		m_turnImage = dynamic_cast<UIImageView*>(status->getChildByName("TurnImg"));
	}
    
    
	void UIBattleTurn::updateStatus()
	{
	}
    
}


