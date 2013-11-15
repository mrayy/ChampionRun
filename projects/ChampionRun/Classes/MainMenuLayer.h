//
//  MainMenuLayer.h
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 10/26/13.
//
//

#ifndef __ChampionRun__MainMenuLayer__
#define __ChampionRun__MainMenuLayer__

#include <iostream>
#include "CommonLayer.h"
#include "cocos-ext.h"
#include "UIMainMenuHandler.h"

namespace ChampionRun
{

	class MenuAvatar;
	class MainMenuLayer :public CommonLayer, public ChampionRun::IUIMainMenuListener, public ISceneReaderListener
	{
	protected:
        static Scene* s_scene;
        static MainMenuLayer* s_layer;
		MenuAvatar* m_yusha;
		bool m_started;
		UILayer* m_UILayer;
		ChampionRun::UIMainMenuHandler* m_mainMenuHandler;

		void switchToBattle();
	public:

		MainMenuLayer();
		virtual~MainMenuLayer();

		virtual bool init();

		// there's no 'id' in cpp, so we recommend returning the class instance pointer
		static cocos2d::Scene* scene();

		static void registerLoader();

		void switchToNextScreen();

		void OnNodeLoaded(Node* node);

		void onAcceleration(Acceleration* acc, Event* event);

        void Reset();
        
		virtual void OnStartPress();
        
        static MainMenuLayer* GetLayer(){return s_layer;}

		// implement the "static node()" method manually
		CREATE_FUNC(MainMenuLayer);

	};

	COMMON_LAYER_LOADER_BEGIN(MainMenuLayer, LayerLoader);
	COMMON_LAYER_LOADER_END();
}

#endif /* defined(__ChampionRun__MainMenuLayer__) */
