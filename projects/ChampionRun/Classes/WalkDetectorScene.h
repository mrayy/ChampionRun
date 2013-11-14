#ifndef __WalkDetectorScene_SCENE_H__
#define __WalkDetectorScene_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
namespace cocos2d
{
    
    class WalkTrainingNode;
}
USING_NS_CC;

namespace ChampionRun
{
	class WalkDetectorScene : public cocos2d::Layer
	{
		WalkTrainingNode* m_trainingNode;
		LabelTTF* m_stateTxt;
		extension::EditBox* m_userName;
		extension::EditBox* m_networkName;


		Layer* m_mainLayer;
		Layer* m_trainingLayer;
		Layer* m_detectionLayer;
	public:
		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
		virtual bool init();

		// there's no 'id' in cpp, so we recommend returning the class instance pointer
		static cocos2d::Scene* scene();

		// a selector callback
		void menuTrainingCallback(Object* pSender);
		void menuDetectCallback(Object* pSender);


		void menuTrainNextCallback(Object* pSender);
		void menuTrainStartCallback(Object* pSender);
		void menuTrainRestartCallback(Object* pSender);

		void menuDetectLoadCallback(Object* pSender);

		void menuBackCallback(Object* pSender);

		void onAcceleration(Acceleration* acc, Event* event);

		void update(float dt);

		// implement the "static node()" method manually
		CREATE_FUNC(WalkDetectorScene);
	};
}
#endif // __WalkDetectorScene_SCENE_H__
