#include "WalkDetectorScene.h"
//#include "BReader.h"
//#include "NodeLoaderLibrary.h"

#include "WalkDetectorNode.h"
#include "WalkTrainingNode.h"

#include "Helpers.h"

#include <SimpleAudioEngine.h>

USING_NS_CC;

namespace ChampionRun
{
	const int TargetSampleCount = 200;

	Scene* WalkDetectorScene::scene()
	{
		// 'scene' is an autorelease object
		Scene *scene = Scene::create();

		// 'layer' is an autorelease object
		WalkDetectorScene *layer = WalkDetectorScene::create();

		// add layer as a child to scene
		scene->addChild(layer);

		// return the scene
		return scene;
	}

	class UserInputDelegate :public TextFieldDelegate
	{
	public:
	};

	// on "init" you need to initialize your instance
	bool WalkDetectorScene::init()
	{
		//////////////////////////////
		// 1. super init first
		if (!Layer::init())
		{
			return false;
		}
		this->setAccelerometerEnabled(true);

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Point origin = Director::getInstance()->getVisibleOrigin();


		m_trainingNode = WalkTrainingNode::create(false, "Yamen");
		m_trainingNode->setContentSize(visibleSize);
		m_trainingNode->setPositionY(25);
		this->addChild(m_trainingNode);

		m_trainingNode->SetDetecting();

		m_stateTxt = LabelTTF::create("State:", "Arial", 24);

		// position the label on the center of the screen
		m_stateTxt->setPosition(Point(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - m_stateTxt->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(m_stateTxt, 1);


		m_mainLayer = Layer::create();
		this->addChild(m_mainLayer);
		m_trainingLayer = Layer::create();
		this->addChild(m_trainingLayer);
		m_detectionLayer = Layer::create();
		this->addChild(m_detectionLayer);
		m_mainLayer->setContentSize(visibleSize);

		{

			Array items;
			items.init();
			items.addObject(MenuItemLabel::create(LabelTTF::create("Training", "Arial", 24), this, menu_selector(WalkDetectorScene::menuTrainingCallback)));
			items.addObject(MenuItemLabel::create(LabelTTF::create("Detect", "Arial", 24), this, menu_selector(WalkDetectorScene::menuDetectCallback)));

			float x = ((MenuItemLabel*)items.getObjectAtIndex(0))->getContentSize().width;
			for (int i = 0; i < items.count(); ++i) {
				MenuItemLabel* itm = (MenuItemLabel*)items.getObjectAtIndex(i);
				Size sz = itm->getContentSize();
				itm->setPosition(Point(x + sz.width / 2, sz.height / 2));
				x += sz.width + 20;
			}

			// create menu, it's an autorelease object
			Menu* pMenu = Menu::createWithArray(&items);

			pMenu->setPosition(CCPointZero);
			m_mainLayer->addChild(pMenu, 1);

			LabelTTF* nameLbl = LabelTTF::create("User Name:", "Arial", 24);
			nameLbl->setPosition(Point(nameLbl->getContentSize().width / 2 + 20, visibleSize.height - 200));
			m_mainLayer->addChild(nameLbl);

			m_userName = extension::EditBox::create(Size(200, nameLbl->getContentSize().height), extension::Scale9Sprite::create("green_edit.png"));
			m_userName->setContentSize(Size(200, m_userName->getContentSize().height));
			m_userName->setAnchorPoint(Point(0, 0.5));
			m_userName->setPosition(Point(nameLbl->getPositionX() + nameLbl->getContentSize().width, visibleSize.height - 200));
			m_mainLayer->addChild(m_userName);
		}

		{

			Array items;
			items.init();
			items.addObject(MenuItemLabel::create(LabelTTF::create("Next", "Arial", 24), this, menu_selector(WalkDetectorScene::menuTrainNextCallback)));
			items.addObject(MenuItemLabel::create(LabelTTF::create("Start", "Arial", 24), this, menu_selector(WalkDetectorScene::menuTrainStartCallback)));
			items.addObject(MenuItemLabel::create(LabelTTF::create("Restart", "Arial", 24), this, menu_selector(WalkDetectorScene::menuTrainRestartCallback)));
			items.addObject(MenuItemLabel::create(LabelTTF::create("Back", "Arial", 24), this, menu_selector(WalkDetectorScene::menuBackCallback)));

			float x = ((MenuItemLabel*)items.getObjectAtIndex(0))->getContentSize().width;
			for (int i = 0; i < items.count(); ++i) {
				MenuItemLabel* itm = (MenuItemLabel*)items.getObjectAtIndex(i);
				Size sz = itm->getContentSize();
				itm->setPosition(Point(x + sz.width / 2, sz.height / 2));
				x += sz.width + 20;
			}
			// create menu, it's an autorelease object
			Menu* pMenu = Menu::createWithArray(&items);
			pMenu->setPosition(CCPointZero);
			m_trainingLayer->addChild(pMenu, 1);
			m_trainingLayer->setVisible(false);


		}
		{

			Array items;
			items.init();
			items.addObject(MenuItemLabel::create(LabelTTF::create("Load", "Arial", 24), this, menu_selector(WalkDetectorScene::menuDetectLoadCallback)));
			items.addObject(MenuItemLabel::create(LabelTTF::create("Back", "Arial", 24), this, menu_selector(WalkDetectorScene::menuBackCallback)));

			float x = ((MenuItemLabel*)items.getObjectAtIndex(0))->getContentSize().width;
			for (int i = 0; i < items.count(); ++i) {
				MenuItemLabel* itm = (MenuItemLabel*)items.getObjectAtIndex(i);
				Size sz = itm->getContentSize();
				itm->setPosition(Point(x + sz.width / 2, sz.height / 2));
				x += sz.width + 20;
			}
			// create menu, it's an autorelease object
			Menu* pMenu = Menu::createWithArray(&items);
			pMenu->setPosition(CCPointZero);
			m_detectionLayer->addChild(pMenu, 1);
			m_detectionLayer->setVisible(false);


			LabelTTF* nameLbl = LabelTTF::create("Load:", "Arial", 24);
			nameLbl->setPosition(Point(nameLbl->getContentSize().width / 2 + 20, visibleSize.height - 200));
			m_detectionLayer->addChild(nameLbl);

			m_networkName = extension::EditBox::create(Size(200, nameLbl->getContentSize().height), extension::Scale9Sprite::create("green_edit.png"));
			m_networkName->setContentSize(Size(200, m_networkName->getContentSize().height));
			m_networkName->setAnchorPoint(Point(0, 0.5));
			m_networkName->setPosition(Point(nameLbl->getPositionX() + nameLbl->getContentSize().width, visibleSize.height - 200));
			m_detectionLayer->addChild(m_networkName);

		}


		this->scheduleUpdate();


		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(100);
		return true;
	}

	void WalkDetectorScene::update(float dt)
	{
		char str[256];
		if (m_trainingNode->IsTraining())
		{
			WalkTrainingNode::EStatus status = m_trainingNode->GetStatus();
			switch (status) {
			case WalkTrainingNode::EIdle:
				sprintf(str, "Idle- %s", m_trainingNode->GetCurrentTrainingLabel().c_str());
				break;
			case WalkTrainingNode::ESampling:
				sprintf(str, "Sampling- %s / %d", m_trainingNode->GetCurrentTrainingLabel().c_str(), m_trainingNode->GetCurrentSamples());
				break;
			case WalkTrainingNode::ETraining:
				sprintf(str, "Training - %f", m_trainingNode->GetError());
				break;
			case WalkTrainingNode::EFinished:
				sprintf(str, "Finished");
				break;
			default:
				break;
			}
			m_stateTxt->setString(str);
		}
		else
		{

			sprintf(str, "Cycle: %s", WalkNodeBase::GetTrainingLabels()[m_trainingNode->GetDetectedCycle()].c_str());
			m_stateTxt->setString(str);
		}
	}

	void WalkDetectorScene::onAcceleration(cocos2d::Acceleration *a, cocos2d::Event *event)
	{
		m_trainingNode->OnAcceleration(a);
		if (m_trainingLayer->isVisible())
		{
			if (m_trainingNode->GetCurrentSamples() == TargetSampleCount && m_trainingNode->GetStatus() == WalkTrainingNode::ESampling)
			{
				m_trainingNode->Stop();
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Done.wav", false);
			}
		}
	}

	void WalkDetectorScene::menuTrainingCallback(Object* pSender)
	{
		m_mainLayer->setVisible(false);
		m_trainingLayer->setVisible(true);
		m_trainingNode->SetTrainingName(m_userName->getText());
		m_trainingNode->SetTraining();
	}
	void WalkDetectorScene::menuDetectCallback(Object* pSender)
	{
		m_mainLayer->setVisible(false);
		m_detectionLayer->setVisible(true);

		m_trainingNode->SetDetecting();
	}


	void WalkDetectorScene::menuTrainNextCallback(Object* pSender)
	{
		if (m_trainingNode->GetStatus() == WalkTrainingNode::ETraining)
			m_trainingNode->EndTraining();
		else if (m_trainingNode->GetCurrentSamples() >= TargetSampleCount)
			m_trainingNode->NextTraining();

	}
	void WalkDetectorScene::menuTrainStartCallback(Object* pSender)
	{
		m_trainingNode->StartTraining();
	}
	void WalkDetectorScene::menuTrainRestartCallback(Object* pSender)
	{
		m_trainingNode->RestartTraining();
	}

	void WalkDetectorScene::menuDetectLoadCallback(Object* pSender)
	{
		m_trainingNode->LoadTraining(FileUtils::getInstance()->getWritablePath() + m_networkName->getText());
	}
	void WalkDetectorScene::menuBackCallback(Object* pSender)
	{
		MenuItem* item = (MenuItem*)pSender;
		item->getParent()->getParent()->setVisible(false);
		m_mainLayer->setVisible(true);

		m_trainingNode->Stop();
	}
}