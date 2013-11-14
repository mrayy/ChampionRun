

#include "UIBattleStatusBar.h"
#include "CBattleCharacter.h"


namespace ChampionRun
{

	UIBattleStatusBar::UIBattleStatusBar()
	{
	}
	UIBattleStatusBar::~UIBattleStatusBar()
	{
	}

	void UIBattleStatusBar::init(CBattleCharacter* c)
	{
		m_character = c;
		m_UILayer = extension::UILayer::create();
		UIWidget*widget = CCUIHELPER->createWidgetFromJsonFile("ui/BattleUI.ExportJson", 0);

		Layout* status = dynamic_cast<Layout*>(widget->getChildByName("StatusPanel"));
		status->retain();
		status->removeFromParent();
		widget->release();
		status->setScaleX(c->GetDirSign());

		status->setPosition(Point(0, 0));
		status->setAnchorPoint(Point(0, 1));
		m_UILayer->setPosition(Point(0, 0));
		m_UILayer->setAnchorPoint(Point(0, 1));

		m_UILayer->addWidget(status);

		m_hpBar = dynamic_cast<UILoadingBar*>(status->getChildByName("hpBar"));
		m_epBar = dynamic_cast<UILoadingBar*>(status->getChildByName("epBar"));
		m_icon = dynamic_cast<UIImageView*>(status->getChildByName("FaceIcon"));
		m_weapon = dynamic_cast<UIImageView*>(status->getChildByName("WeaponIcon"));

		m_icon->loadTexture(c->GetIcon().c_str());
	}


	void UIBattleStatusBar::updateStatus()
	{
		m_hpBar->setPercent(100 * m_character->GetHP() / m_character->GetMaxHP());
		m_epBar->setPercent(100 * m_character->GetEP() / m_character->GetMaxEP());
	}

}


