#include <Geode/Geode.hpp>
#include <Geode/modify/GauntletLayer.hpp>

using namespace geode::prelude;

class $modify(RedesignedGauntletLayer, GauntletLayer) {
	void loadLevelsFinished(CCArray* p0, char const* p1, int p2) {
		GauntletLayer::loadLevelsFinished(p0, p1, p2);

		auto backgroundSprite = static_cast<CCSprite*>(this->getChildByIDRecursive("background"));
		backgroundSprite->setColor(ccc3(51, 16, 16));

		auto gauntletTitleText = static_cast<CCLabelBMFont*>(this->getChildByIDRecursive("title"));
		gauntletTitleText->setFntFile("GR_OxygeneFont.fnt"_spr);
		gauntletTitleText->setColor(ccc3(0, 0, 0));
		gauntletTitleText->setScale(0.50);
		
		auto gauntletShadowText = static_cast<CCLabelBMFont*>(this->getChildByIDRecursive("title-shadow"));
		gauntletShadowText->setFntFile("GR_OxygeneFont.fnt"_spr);
		gauntletShadowText->setColor(ccc3(255, 255, 255));
		gauntletShadowText->setScale(0.50);

		// for (int i = 2; i <= 38; i++) { // ok idk why the fuck 38 works but it works
			// auto circleSprite = static_cast<CCSprite*>(this->getChildren()->objectAtIndex(i));
			// circleSprite->setVisible(false);
		// }


	}
};