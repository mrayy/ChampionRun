//
//  SceneManager.cpp
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 10/26/13.
//
//

#include "SceneManager.h"
#include "cocos-ext.h"
#include "CommonLayer.h"


#include "SplashLayer.h"
#include "MainMenuLayer.h"

#include "libs\tinyxml2.h"

USING_NS_CC;

SceneManager* SceneManager::s_instance=0;

SceneManager::SceneManager()
{
 
    m_loaders=extension::NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
    m_loaders->registerDefaultNodeLoaders();
    //m_loaders->registerCCNodeLoader("SplashScene", cocos2d::extension::CCNodeLoader *pCCNodeLoader);

    
}
void SceneManager::Init()
{
	tinyxml2::XMLDocument doc;
	std::string path = FileUtils::getInstance()->fullPathForFilename("CR_settings.xml");
	if (doc.LoadFile(path.c_str()) == tinyxml2::XML_NO_ERROR)
	{
		const tinyxml2::XMLElement* armatures = doc.FirstChildElement("Armatures");
		if (armatures)
			InitArmaturesXML(armatures);
	}
	s_instance->registerDefaults();

}
void SceneManager::InitArmatures(const std::string& desc)
{
	tinyxml2::XMLDocument doc;
	std::string path = FileUtils::getInstance()->fullPathForFilename(desc);
	if (doc.LoadFile(path.c_str()) != tinyxml2::XML_NO_ERROR)
		return;

	const tinyxml2::XMLElement* root= doc.FirstChildElement("Armatures");
	if (!root)
		return;
	InitArmaturesXML(root);
}
void SceneManager::InitArmaturesXML(const tinyxml2::XMLElement* root)
{
	ArmatureProperties props;
	const tinyxml2::XMLElement* elem= root->FirstChildElement("Armature");
	while (elem)
	{
		if (props.Load(elem))
		{
			armature::ArmatureDataManager::getInstance()->addArmatureFileInfo(props.path.c_str());
			m_armatures[props.name] = props;
		}
		elem = elem->NextSiblingElement("Armature");
	}

}

armature::Armature* SceneManager::LoadArmature(const std::string& name)
{
	ArmatureMap::iterator it = m_armatures.find(name);
	if (it == m_armatures.end())
		return 0;
	armature::Armature* ret = armature::Armature::create(name.c_str());
	ret->setScaleX(it->second.scale.width);
	ret->setScaleY(it->second.scale.height);
	return ret;
}


void SceneManager::registerDefaults()
{
    SplashLayer::registerLoader();
    MainMenuLayer::registerLoader();
}
cocos2d::Node* SceneManager::LoadNode(const std::string& scene)
{
    extension::CCBReader reader(m_loaders);
    m_loaders->retain();
    
    return reader.readNodeGraphFromFile(scene.c_str());
}
void SceneManager::registerLoader(CommonLayerLoader* loader)
{
    m_loaders->registerNodeLoader(loader->GetName().c_str(), loader->GetLoader());
}

cocos2d::Scene* SceneManager::LoadScene(const std::string& scene)
{
    extension::CCBReader reader(m_loaders);
    m_loaders->retain();

    return reader.createSceneWithNodeGraphFromFile(scene.c_str());
}

