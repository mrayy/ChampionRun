//
//  MainMenuLayer.cpp
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 10/26/13.
//
//

#include "MainMenuLayer.h"
#include "SceneManager.h"
#include "Helpers.h"
#include "UIEvents.h"
#include "QuestItemWidget.h"
#include "BattleLayer.h"
/*
static const ButtonEventHandler MainMenuEvents[]=
{
	{ "btnStatusBack", (SEL_TouchEvent)&MainMenuLayer::onStatusBackPressed},

	{ "btnRankingBack", (SEL_TouchEvent)&MainMenuLayer::onRankingBackPressed},
};
static const int MainMenuEvents_cnt = sizeof(MainMenuEvents) / sizeof(ButtonEventHandler);
*/

namespace ChampionRun
{

	class CloudsGenerator :public Layer
	{
		struct CloudData
		{
			Node* sprite;
			float distance;
		};
		std::vector<CloudData> m_clouds;

		GLProgram* m_shader;
		int m_timeUniform;
		float m_time;


		float m_speed;

		ParallaxNode* _cloudsLayer;

	public:
		CloudsGenerator()
		{
			this->scheduleUpdate();
			m_time = 0;

			setAccelerometerEnabled(true);
		}

		void onAcceleration(Acceleration* acc, Event* event)
		{
			m_speed = acc->x;
		}

		virtual void update(float dt)
		{
			Layer::update(dt);

			Size winSize = CCDirector::getInstance()->getWinSize();
			for (int i = 0; i<m_clouds.size(); ++i)
			{
				Point pos = _cloudsLayer->convertToWorldSpace(m_clouds[i].sprite->getPosition());
				float width = m_clouds[i].sprite->getContentSize().width*m_clouds[i].sprite->getScaleX()*0.5;
				if (pos.x>winSize.width + width)
				{
					_cloudsLayer->incrementOffset(Point(-pos.x - width, 0), m_clouds[i].sprite);

				}
			}

			_cloudsLayer->setPosition(_cloudsLayer->getPosition() + Point(200, 0)*dt);
			m_time += dt;

			if (m_shader)
			{
				m_shader->use();
				glUniform1f(m_timeUniform, m_time);
			}
			Acceleration acc;
			acc.x = rand01();
			acc.y = rand01();
			acc.z = rand01();

			//   m_accNode->OnAcceleration(&acc);

		}

		virtual bool init()
		{
			if (!CCNode::init())
				return  false;
			Size winSize = CCDirector::getInstance()->getWinSize();
			//  CCSpriteBatchNode* cloudBatch=CCSpriteBatchNode::create("Menu/Cloud.png");
			//  addChild(cloudBatch);
			if (false)
			{
				std::string shaderPath = FileUtils::getInstance()->fullPathFromRelativeFile("Clouds.vsh", "");

				unsigned long pSize = 0;
				std::string shaderSrc = (char*)FileUtils::getInstance()->getFileData(shaderPath.c_str(), "r", &pSize);
				GLProgram* shaderProgram = new GLProgram();
				char* str = (char*)shaderSrc.c_str();
				str[shaderSrc.length()] = 0;
				shaderProgram->initWithVertexShaderByteArray(str, ccPositionTextureColor_frag);
				shaderProgram->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
				shaderProgram->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);

				shaderProgram->link();
				shaderProgram->updateUniforms();
				m_timeUniform = shaderProgram->getUniformLocationForName("u_time");
				this->getPositionX();

				m_shader = shaderProgram;
			}
			else
				m_shader = NULL;

			_cloudsLayer = ParallaxNode::create();
			addChild(_cloudsLayer);
			for (int i = 0; i < 10; ++i)
			{
				CloudData cloud;
				cloud.sprite = CCSprite::create("Scenes/img/MainMenu/Cloud.png");
				int zOrder = randRange(0, 4);
				cloud.distance = zOrder;
				cloud.sprite->setScale((cloud.distance + 1) / 10 + 1);
				//sprite->setPosition(Point(randRange(-50, winSize.width+50),100+randRange(-100, 300)));
				if (m_shader)
					cloud.sprite->setShaderProgram(m_shader);

				m_clouds.push_back(cloud);
				_cloudsLayer->addChild(cloud.sprite, zOrder, Point(0.01*(zOrder + 1), 0), Point(randRange(-50, winSize.width + 50), winSize.height - randRange(0, winSize.height*2.0f / 3.0f)));
			}

			return true;
		}


		// implement the "static node()" method manually
		CREATE_FUNC(CloudsGenerator);
	};


	COMMON_LAYER_LOADER_BEGIN(CloudsGenerator, LayerLoader);
	COMMON_LAYER_LOADER_END();

	class MenuEnemy :public Node
	{
	protected:
		enum class EStatus
		{
			EIdle,
			EEnter,
			EAttack,
			EDie
		};

		EStatus m_status;
		armature::Armature* m_entity;
	public:
		MenuEnemy()
		{}

		virtual bool init(Node* parent)
		{
			if (!CCNode::init())
				return  false;
			m_status = EStatus::EEnter;

			this->scheduleUpdate();
			//Node*node=SceneManager::instance()->LoadNode("Yusha");
			// addChild(node);
			parent->addChild(this);
			m_entity = SceneManager::instance()->LoadArmature("Skeleton");
			m_entity->setAnchorPoint(Point(0.5, 0));
			addChild(m_entity);
			setScaleX(-1);
			m_status = EStatus::EIdle;

			return true;
		}

		void Start()
		{
			m_status = EStatus::EEnter;
			Size winSize = Director::getInstance()->getWinSize();
			Point p = this->convertToWorldSpace(Point(winSize.width, 0));
			setPositionX(-p.x + m_entity->getContentSize().width*abs(m_entity->getScaleX()));
			m_entity->getAnimation()->play("run");

		}
		bool IsDead()
		{
			return m_status == EStatus::EIdle;
		}
		void Kill()
		{
			m_entity->getAnimation()->play("dead");

			m_status = EStatus::EDie;
		}
		void update(float dt)
		{
			Node::update(dt);
			Point pos;

			switch (m_status)
			{
			case MenuEnemy::EStatus::EEnter:
				pos = getPosition();
				if (pos.x > m_entity->getContentSize().width*m_entity->getScaleX() / 2)
				{
					pos.x -= 300 * dt;
					setPosition(pos);
				}
				else
				{
					pos.x = m_entity->getContentSize().width*m_entity->getScaleX() / 2;
					setPosition(pos);
					m_status = EStatus::EAttack;
					m_entity->getAnimation()->play("attack");
				}
				break;
			case MenuEnemy::EStatus::EAttack:
				break;
			case MenuEnemy::EStatus::EDie:
				if (m_entity->getAnimation()->getIsComplete() == true)
				{
					setVisible(true);
					m_status = EStatus::EIdle;
				}
				break;
			default:
				break;
			}
		}

		// implement the "static node()" method manually
		static MenuEnemy* create(Node* parent)
		{
			MenuEnemy* ret = new MenuEnemy();
			if (ret && ret->init(parent))
				return ret;
			delete ret;
			return NULL;
		}
	};

	class MenuAvatar :public Node
	{
	protected:
		enum class EStatus
		{
			EEnter,
			EIdle,
			EAttackStart,
			EAttacking,
			EStartGame
		};

		EStatus m_status;
		armature::Armature* m_hero;
		MenuEnemy* m_enemy;
	public:
		MenuAvatar()
		{
			m_hero = 0;
		}

		virtual bool init(Node* parent)
		{
			if (!CCNode::init())
				return  false;
			m_status = EStatus::EEnter;

			this->scheduleUpdate();
			parent->addChild(this);
			m_hero = SceneManager::instance()->LoadArmature("Yusha");
			m_hero->setAnchorPoint(Point(0.5, 0));

			addChild(m_hero);

			m_enemy = new MenuEnemy();
			m_enemy->init(parent);
			m_enemy->setVisible(false);
			Start();
			return true;
		}

		void Start()
		{
			m_status = EStatus::EEnter;
			Point p = this->convertToWorldSpace(Point(0, 0));
			setPositionX(-p.x - m_hero->getContentSize().width*abs(m_hero->getScaleX()));
			m_hero->getAnimation()->play("run");

		}

		void PlayStart()
		{
			m_hero->getAnimation()->play("victory");
			if (!m_enemy->IsDead())
				m_enemy->Kill();
		}
		bool IsReady()
		{
			return m_status != EStatus::EEnter;
		}

		void update(float dt)
		{
			Node::update(dt);
			Point pos;

			switch (m_status)
			{
			case MenuAvatar::EStatus::EEnter:
				pos = getPosition();
				if (pos.x < 0)
				{
					pos.x += 300 * dt;
					setPosition(pos);
				}
				else
				{
					m_status = EStatus::EIdle;
					m_hero->getAnimation()->play("stand");
				}
				break;
			case MenuAvatar::EStatus::EIdle:
				if (rand01() > 0.999 && m_enemy->IsDead())
				{
					m_status = EStatus::EAttackStart;
					m_enemy->Start();
					m_enemy->setVisible(true);
				}
				break;
			case MenuAvatar::EStatus::EAttackStart:
			{
													  float dist = abs(m_enemy->getPositionX() - getPositionX());
													  if (dist < m_hero->getContentSize().width*abs(m_hero->getScaleX()))
													  {
														  m_hero->getAnimation()->play("attack");
														  m_status = EStatus::EAttacking;
													  }

			}
				break;
			case MenuAvatar::EStatus::EAttacking:
				if (rand01() > 0.995)
				{
					m_status = EStatus::EIdle;
					m_enemy->Kill();
					m_hero->getAnimation()->play("stand");
				}
				break;
			case MenuAvatar::EStatus::EStartGame:
				break;
			default:
				break;
			}
		}

		// implement the "static node()" method manually
		static MenuAvatar* create(Node* parent)
		{
			MenuAvatar* ret = new MenuAvatar();
			if (ret && ret->init(parent))
				return ret;
			delete ret;
			return NULL;
		}
	};


	MainMenuLayer::MainMenuLayer()
	{
		m_yusha = 0;
	}
	MainMenuLayer::~MainMenuLayer()
	{
		delete m_mainMenuHandler;
	}
	bool MainMenuLayer::init()
	{
		if (!CCLayer::init())
			return false;

		m_started = false;
		Size sz = Director::getInstance()->getWinSize();
		Node* screen = (Node*)extension::SceneReader::getInstance()->createNodeWithSceneFile("MainMenuScreen.json", this);
		screen->setAnchorPoint(Point(0, 0));
		addChild(screen);

		m_mainMenuHandler = new ChampionRun::UIMainMenuHandler();
		m_mainMenuHandler->init();
		m_mainMenuHandler->SetListener(this);
		//m_statusUI = CCUIHELPER->createWidgetFromJsonFile("ui/StatusMenuUI.ExportJson", this);
		//m_rankingUI = CCUIHELPER->createWidgetFromJsonFile("ui/RankingMenuUI.ExportJson", this);

		m_UILayer = extension::UILayer::create();
		addChild(m_UILayer, 10);

		m_mainMenuHandler->Push(0, m_UILayer);
		/*

		m_UILayer->addWidget(m_mainUI);

		m_mainUI->retain();
		m_statusUI->retain();
		m_rankingUI->retain();
		*/
		this->setAccelerometerEnabled(true);
		return true;
	}
	void MainMenuLayer::OnNodeLoaded(Node* node)
	{
		if (node->GetName() == "")
			return;

		CCLOG("Node loaded:%s", node->GetName().c_str());
		if (node->GetName() == "Avatar")
		{
			m_yusha = MenuAvatar::create(node);
		}
		else if (node->GetName() == "Clouds")
		{
			CloudsGenerator* generator = CloudsGenerator::create();
			node->addChild(generator);
		}
	}
	void MainMenuLayer::onAcceleration(Acceleration* acc, Event* event)
	{

	}
	void MainMenuLayer::registerLoader()
	{
		SceneManager::instance()->registerLoader(MainMenuLayerLoader::loader());
		SceneManager::instance()->registerLoader(CloudsGeneratorLoader::loader());
	}

	void MainMenuLayer::switchToBattle()
	{
		Director::getInstance()->replaceScene(TransitionFade::create(5, BattleLayer::scene()));
	}

	void MainMenuLayer::OnStartPress()
	{
		if (m_started || !m_yusha->IsReady())
			return;
		m_yusha->PlayStart();

		switchToBattle();


	}
	void MainMenuLayer::switchToNextScreen()
	{
	}

	/*
	void MainMenuLayer::onStatusBackPressed(Object* sender, TouchEventType event)
	{

	if (event == TouchEventType::TOUCH_EVENT_ENDED)
	{
	m_UILayer->removeWidget(m_statusUI);
	m_UILayer->addWidget(m_mainUI);
	}
	}
	void MainMenuLayer::onRankingBackPressed(Object* sender, TouchEventType event)
	{
	if (event == TouchEventType::TOUCH_EVENT_ENDED)
	{
	m_UILayer->removeWidget(m_rankingUI);
	m_UILayer->addWidget(m_mainUI);
	}
	}*/
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	cocos2d::Scene* MainMenuLayer::scene()
	{

		// 'scene' is an autorelease object
		//Scene *scene = SceneManager::instance()->LoadScene("MainMenuScene");
		// return the scene
		Scene* scene = new Scene();
		MainMenuLayer* layer = new MainMenuLayer();
		layer->init();
		scene->addChild(layer);
		return scene;
	}
}
