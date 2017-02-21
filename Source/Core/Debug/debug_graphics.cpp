#include "debug_graphics.h"

namespace Hikari
{
	void DebugGraphics::DrawDebugLine(World* arg_world, Ogre::Vector3 arg_start, Ogre::Vector3 arg_end, Ogre::ColourValue arg_colour, float arg_lifetime)
	{
		Ogre::SceneManager* sceneMgr = arg_world->GetSceneManager();
		Ogre::ManualObject* manualObject = sceneMgr->createManualObject("manual1");
		Ogre::SceneNode* manualObjectNode = sceneMgr->getRootSceneNode()->createChildSceneNode("manual1_node");

		Ogre::MaterialPtr manualObjectMaterial = Ogre::MaterialManager::getSingleton().create("manual1Material", "General");
		manualObjectMaterial->setReceiveShadows(false);
		manualObjectMaterial->getTechnique(0)->setLightingEnabled(true);
		manualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(arg_colour);
		manualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(arg_colour);
		manualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(arg_colour);
		//myManualObjectMaterial->dispose();

		manualObject->begin("manual1Material", Ogre::RenderOperation::OT_LINE_LIST);
		manualObject->position(arg_start);
		manualObject->position(arg_end);
		
		manualObject->end();

		manualObjectNode->attachObject(manualObject);
	}

	void DebugGraphics::DrawDebugPoints(World* arg_world, std::vector<Ogre::Vector3> arg_points, Ogre::Real arg_pointsize, Ogre::ColourValue arg_colour, float arg_lifetime)
	{
		Ogre::SceneManager* sceneMgr = arg_world->GetSceneManager();
		Ogre::ManualObject* manualObject = sceneMgr->createManualObject("manual1");
		Ogre::SceneNode* manualObjectNode = sceneMgr->getRootSceneNode()->createChildSceneNode("manual1_node");

		Ogre::MaterialPtr manualObjectMaterial = Ogre::MaterialManager::getSingleton().create("manual1Material", "General");
		manualObjectMaterial->setReceiveShadows(false);
		manualObjectMaterial->getTechnique(0)->setLightingEnabled(true);
		manualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(arg_colour);
		manualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(arg_colour);
		manualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(arg_colour);
		manualObjectMaterial->getTechnique(0)->getPass(0)->setPointSize(arg_pointsize);
		//myManualObjectMaterial->dispose();

		manualObject->begin("manual1Material", Ogre::RenderOperation::OT_POINT_LIST);
		for (Ogre::Vector3 point : arg_points)
		{
			manualObject->position(point);
		}

		manualObject->end();

		manualObjectNode->attachObject(manualObject);
	}

}
