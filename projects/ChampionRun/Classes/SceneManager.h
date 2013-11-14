//
//  SceneManager.h
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 10/26/13.
//
//

#ifndef __ChampionRun__SceneManager__
#define __ChampionRun__SceneManager__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>

USING_NS_CC;

namespace ChampionRun
{
	class CommonLayerLoader;
	struct ArmatureProperties
	{
		std::string name;
		std::string path;
		Size scale;

		bool Load(const tinyxml2::XMLElement* e)
		{
			const tinyxml2::XMLElement* elem;
			elem = e->FirstChildElement("Name");
			if (!elem)
				return false;

			name = elem->GetText();
			elem = e->FirstChildElement("Path");
			if (!elem)
				return false;
			path = elem->GetText();

			elem = e->FirstChildElement("Scale");
			if (!elem)
				return false;

			sscanf(elem->GetText(), "%f,%f", &scale.width, &scale.height);
			return true;

		}
	};
	class SceneManager
	{
		static SceneManager* s_instance;
		extension::NodeLoaderLibrary* m_loaders;
		typedef std::map<std::string, extension::CCBSelectorResolver*> ResolversMap;
		typedef std::map<std::string, ArmatureProperties> ArmatureMap;
		ResolversMap m_resolvers;
		ArmatureMap m_armatures;
	public:


		SceneManager();

		void InitArmatures(const std::string& desc);
		void InitArmaturesXML(const tinyxml2::XMLElement* elem);

		extension::armature::Armature* LoadArmature(const std::string& name);

		void Init();

		cocos2d::Scene* LoadScene(const std::string& scene);
		cocos2d::Node* LoadNode(const std::string& scene);

		void registerLoader(CommonLayerLoader* loader);

		void registerDefaults();

		static SceneManager* instance()
		{
			if (s_instance == NULL)
			{
				s_instance = new SceneManager();
				s_instance->Init();
			}

			return s_instance;
		}
	};
}

#endif /* defined(__ChampionRun__SceneManager__) */
