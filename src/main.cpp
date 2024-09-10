#include <Geode/Geode.hpp>
#include <Geode/modify/GauntletLayer.hpp>

using namespace geode::prelude;

class $modify(RedesignedGauntletLayer, GauntletLayer) {
	void loadLevelsFinished(CCArray* p0, char const* p1, int p2) {
		GauntletLayer::loadLevelsFinished(p0, p1, p2);

		auto backgroundSprite = static_cast<CCSprite*>(this->getChildren()->objectAtIndex(0));
		backgroundSprite->setID("gauntlet-background-sprite");
		backgroundSprite->setColor(ccc3(255, 0, 0));

		for (int i = 2; i <= 38; i++) { // ok idk why the fuck 38 works but it works
			auto circleSprite = static_cast<CCSprite*>(this->getChildren()->objectAtIndex(i));
			circleSprite->setVisible(false);
		}
	}
};