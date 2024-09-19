#include <Geode/Geode.hpp>
#include <Geode/modify/GauntletLayer.hpp>

using namespace geode::prelude;

class $modify(RedesignedGauntletLayer, GauntletLayer) {
	void loadLevelsFinished(CCArray* p0, char const* p1, int p2) {
		GauntletLayer::loadLevelsFinished(p0, p1, p2);

		auto backgroundSprite = static_cast<CCSprite*>(this->getChildren()->objectAtIndex(0));
		backgroundSprite->setID("gauntlet-background-sprite");
		backgroundSprite->setColor(ccc3(51, 16, 16));

		// this is the shadow text for whatever fuckall reason
		auto gauntletTitleText = static_cast<CCLabelBMFont*>(this->getChildByIDRecursive("title"));
		gauntletTitleText->setFntFile("GR_OxygeneFont.fnt"_spr);
		gauntletTitleText->setColor(ccc3(0, 0, 0));
		gauntletTitleText->setScale(0.50);
		gauntletTitleText->setPositionY(287);
		gauntletTitleText->setPositionX(286.50);
		
		// and this is the actual title text like what dude
		auto gauntletShadowText = static_cast<CCLabelBMFont*>(this->getChildByIDRecursive("title-shadow"));
		gauntletShadowText->setFntFile("GR_OxygeneFont.fnt"_spr);
		gauntletShadowText->setColor(ccc3(255, 255, 255));
		gauntletShadowText->setScale(0.50);
		gauntletShadowText->setPositionY(290);
		gauntletShadowText->setPositionX(284.50);

		// for (int i = 2; i <= 38; i++) { // ok idk why the fuck 38 works but it works
			// auto circleSprite = static_cast<CCSprite*>(this->getChildren()->objectAtIndex(i));
			// circleSprite->setVisible(false);
		// }


	}
};