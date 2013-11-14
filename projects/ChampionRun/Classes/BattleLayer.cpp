

#include "BattleLayer.h"
#include "UIBattleStatusBar.h"

namespace ChampionRun
{

	BattleLayer::BattleLayer()
	{

	}
	BattleLayer::~BattleLayer()
	{

	}
	bool BattleLayer::init()
	{

		if (!CCLayer::init())
			return false;

		m_turnTime = 0;
		m_power = 0;

		Size sz = Director::getInstance()->getWinSize();
		Node* screen = (Node*)extension::SceneReader::getInstance()->createNodeWithSceneFile("Battle.json", this);
		screen->setAnchorPoint(Point(0, 0));
		addChild(screen);


		{
			m_player = new ChampionRun::CBattleCharacter();
			m_player->init("Yusha", "ui/chars/Yusha_icon_normal.png",this);
			m_player->SetDirection(ChampionRun::ECharacterDirection::Right);

			m_enemy = new ChampionRun::CBattleCharacter();
			m_enemy->init("Gyojin", "ui/chars/Gyojin_icon_normal.png", this);
			m_enemy->SetDirection(ChampionRun::ECharacterDirection::Left);

			m_playerNode->addChild(m_player->GetNode());
			m_enemyNode->addChild(m_enemy->GetNode());

			m_player->Attack(m_enemy);
		}
		{
			m_attackUI = new UIBattleAttack();
			m_attackUI->init(this);

			screen->addChild(m_attackUI->GetLayer(), 10);
		}
		{
			m_enemyUI = new UIBattleStatusBar();
			m_enemyUI->init(m_enemy);
			m_enemyStatusNode->addChild(m_enemyUI->GetLayer(), 10);
		}
		{
			m_playerUI = new UIBattleStatusBar();
			m_playerUI->init(m_player);
			m_playerStatusNode->addChild(m_playerUI->GetLayer(), 10);
		}

		scheduleUpdate();


		return true;
	}

	cocos2d::Scene* BattleLayer::scene()
	{

		Scene* scene = new Scene();
		BattleLayer* layer = new BattleLayer();
		layer->init();
		scene->addChild(layer);
		return scene;

	}

	void BattleLayer::registerLoader()
	{

	}

	void BattleLayer::switchToNextScreen()
	{

	}
	void BattleLayer::OnAttackPressed()
	{
		m_power += 0.1;
		if (m_power > 1)
			m_power = 1;

		m_player->Attack(m_enemy);
	}

	void BattleLayer::OnNodeLoaded(Node* node)
	{
		if (node->GetName() == "")
			return;
		if (node->GetName() == "EnemyStatus")
		{
			m_enemyStatusNode = node;
		}
		else if (node->GetName() == "PlayerStatus")
		{
			m_playerStatusNode = node;
		}
		else if (node->GetName() == "EnemyPosition")
		{
			m_enemyNode = node;
		}
		else if (node->GetName() == "PlayerPosition")
		{
			m_playerNode = node;
		}
	}


	void BattleLayer::update(float dt)
	{
		const float totalTime = 10;
		m_player->update(dt);
		m_enemy->update(dt);

		m_power -= 0.4*dt;

		if (m_power < 0)m_power = 0;

		m_player->SetPower(m_power);
		m_turnTime += dt;
		float t = m_turnTime / totalTime;
		if (t >= 1)
		{
			t = 1;
		}
		m_attackUI->SetTime01(t);
		m_attackUI->SetPower(m_power);

	}


	void BattleLayer::OnDamaged(CBattleCharacter* c, float d)
	{
		m_playerUI->updateStatus();
		m_enemyUI->updateStatus();

	}
	void BattleLayer::OnAttack(CBattleCharacter* c, float ep, float d)
	{
		m_playerUI->updateStatus();
		m_enemyUI->updateStatus();
	}
	void BattleLayer::OnDie(CBattleCharacter* c)
	{
		m_playerUI->updateStatus();
		m_enemyUI->updateStatus();
	}
}

