



#include "QuestAlarmLayer.h"

#include "MainMenuLayer.h"
#include "SplashLayer.h"


namespace ChampionRun
{
QuestAlarmLayer::QuestAlarmLayer()
{

}
QuestAlarmLayer::~QuestAlarmLayer()
{

}
bool QuestAlarmLayer::init()
{

	if (!CCLayer::init())
		return false;

	Size sz = Director::getInstance()->getWinSize();
	Node* screen = (Node*)extension::SceneReader::getInstance()->createNodeWithSceneFile("Scenes/QuestAlarm.json", this);
	screen->setAnchorPoint(Point(0, 0));
	addChild(screen);
	m_time = 0;
	scheduleUpdate();
	this->setTouchEnabled(true);
	this->setContentSize(sz);

	return true;
}

cocos2d::Scene* QuestAlarmLayer::scene()
{

	Scene* scene = new Scene();
	QuestAlarmLayer* layer = new QuestAlarmLayer();
	layer->init();
	scene->addChild(layer);

	return scene;

}

void QuestAlarmLayer::registerLoader()
{

}

void QuestAlarmLayer::switchToNextScreen()
{
	Director::getInstance()->replaceScene(TransitionFade::create(2, SplashLayer::scene()));
}

void QuestAlarmLayer::onTouchesBegan(const std::vector<Touch*>& pTouches, Event *event)
{
	Layer::onTouchesBegan(pTouches, event);
	switchToNextScreen();
}
void QuestAlarmLayer::update(float dt)
{
	float op = 255 * abs(sin(m_time));
	m_time += dt;
	m_alarmIcon->setOpacity(op);
}

void QuestAlarmLayer::OnNodeLoaded(Node* node)
{
	if (node->GetName() == "")
		return;
	if (node->GetName() == "AlarmIcon")
	{
		ComRender* comp = dynamic_cast<ComRender*>(node->getComponent("CCSprite"));
		m_alarmIcon = dynamic_cast<Sprite*>(comp->getNode());
	}
}
}





