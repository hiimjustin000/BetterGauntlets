#include <Geode/Geode.hpp>
#include <Geode/modify/GauntletLayer.hpp>

using namespace geode::prelude;

class $modify(RedesignedGauntletLayer, GauntletLayer) {
	void loadLevelsFinished(CCArray* p0, char const* p1, int p2) {
		GauntletLayer::loadLevelsFinished(p0, p1, p2);

		auto backgroundSprite = static_cast<CCSprite*>(this->getChildByIDRecursive("background"));

		// this is the shadow text for whatever fuckall reason
		auto gauntletShadowText = static_cast<CCLabelBMFont*>(this->getChildByIDRecursive("title"));
			gauntletShadowText->setFntFile("GR_OxygeneFont.fnt"_spr);
			gauntletShadowText->setColor(ccc3(0, 0, 0));
			gauntletShadowText->setScale(0.50);
			gauntletShadowText->setPosition(286.50, 287);
		
		// and this is the actual title text like what dude
		auto gauntletTitleText = static_cast<CCLabelBMFont*>(this->getChildByIDRecursive("title-shadow"));
			gauntletTitleText->setFntFile("GR_OxygeneFont.fnt"_spr);
			gauntletTitleText->setColor(ccc3(255, 255, 255));
			gauntletTitleText->setScale(0.50);
			gauntletTitleText->setPosition(284.50, 290);
		
		// heres the part where jay tries adding the highlight (spoiler: its failing horribly lol)
		auto gauntletHighlightText = static_cast<CCLabelBMFont*>(this->getChildByIDRecursive("gauntletHighlightText"));
			gauntletHighlightText->setFntFile("GR_OxygeneFont.fnt"_spr);
			gauntletHighlightText->setColor(ccc3(255, 0, 0));
			gauntletHighlightText->setScale(0.50);
			gauntletHighlightText->setPosition(284.50, 290);

		if (this->m_gauntletType == GauntletType::Fire) {
			auto gauntletHLText = CCLabelBMFont::create("Fire Gauntlet", "GR_OxygeneFontHighlight.fnt"_spr);
				backgroundSprite->setColor(ccc3(63, 9, 9));
				this->addChild(gauntletHLText);
		}
	}
};