#include <Geode/Geode.hpp>
#include <Geode/modify/GauntletLayer.hpp>

using namespace geode::prelude;

class $modify(GauntletLayer) {
	bool init(GauntletType gauntletType) {
		if (!GauntletLayer::init(gauntletType)) {
			return false;
		}

		auto backgroundSprite = static_cast<CCSprite*>(this->getChildren()->objectAtIndex(0));
		backgroundSprite->setID("gauntlet-background-sprite");

		CCObject* childrenObj;
		CCARRAY_FOREACH(this->getChildren(), childrenObj) {
			if (auto spriteCast = static_cast<CCNode*>(childrenObj)) {
				
			}
		}

		log::debug("Hello from my MenuLayer::init hook! This layer has {} children.", this->getChildrenCount());

		return true;
	}
};