#include <Geode/Geode.hpp>
#include <Geode/modify/GauntletLayer.hpp>

using namespace geode::prelude;

class $modify(RedesignedGauntletLayer, GauntletLayer) {
	struct Fields {
		bool m_loaded = false;
	};
	bool init(GauntletType p0) {
		if(!GauntletLayer::init(p0))
			return false;

		if(this->m_levels != nullptr && !m_fields->m_loaded)
			editGauntlets();

		return true;
	}

	void loadLevelsFinished(CCArray* p0, char const* p1, int p2) {
		GauntletLayer::loadLevelsFinished(p0, p1, p2);

		if(!m_fields->m_loaded)
			editGauntlets();
	}
	void editGauntlets() {
	// this is the shadow text for whatever fuckall reason
	auto gauntletShadowText = static_cast<CCLabelBMFont*>(this->getChildByID("title"));
	if (!gauntletShadowText) return;

	gauntletShadowText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
	gauntletShadowText->setColor(ccc3(0, 0, 0));
	gauntletShadowText->setScale(0.750);
	gauntletShadowText->setPosition(286.50, 287);

	// and this is the actual title text like what dude
	auto gauntletTitleText = static_cast<CCLabelBMFont*>(this->getChildByID("title-shadow"));
	if (!gauntletTitleText) return;

	gauntletTitleText->setFntFile("GR_OxygeneFont.fnt"_spr);
	gauntletTitleText->setColor(ccc3(255, 255, 255));
	gauntletTitleText->setScale(0.750);
	gauntletTitleText->setPosition(284.50, 290);

		switch(m_gauntletType) {
			default: break;
			case GauntletType::Fire: editGauntletSingle("Fire", ccc3(63, 29, 9), ccc3(255, 255, 255), ccc3(255, 255, 0), ccc3(255, 136, 0)); break;
			case GauntletType::Ice: editGauntletSingle("Ice", ccc3(8, 68, 83), ccc3(255, 255, 255), ccc3(0, 255, 255), ccc3(0, 174, 255)); break;
			case GauntletType::Poison: editGauntletSingle("Poison", ccc3(20, 63, 9), ccc3(255, 255, 255), ccc3(229, 255, 0), ccc3(80, 179, 0)); break;
			case GauntletType::Shadow: editGauntletSingle("Shadow", ccc3(46, 19, 45), ccc3(255, 255, 255), ccc3(255, 255, 132), ccc3(168, 214, 0)); break;
			case GauntletType::Lava: editGauntletSingle("Lava", ccc3(63, 9, 9), ccc3(255, 255, 255), ccc3(255, 209, 56), ccc3(255, 51, 0)); break;
			case GauntletType::Bonus: editGauntletSingle("Bonus", ccc3(30, 54, 85), ccc3(255, 255, 255), ccc3(255, 241, 20), ccc3(133, 59, 0)); break;
			case GauntletType::Chaos: editGauntletSingle("Chaos", ccc3(33, 12, 6), ccc3(255, 255, 255), ccc3(255, 145, 0), ccc3(167, 49, 28)); break;
			case GauntletType::Demon: editGauntletSingle("Demon", ccc3(29, 29, 29), ccc3(255, 255, 255), ccc3(200, 45, 45), ccc3(99, 3, 3)); break;
			case GauntletType::Time: editGauntletSingle("Time", ccc3(17, 69, 128), ccc3(255, 255, 255), ccc3(64, 252, 200), ccc3(17, 114, 90)); break;
			case GauntletType::Crystal: editGauntletSingle("Crystal", ccc3(51, 2, 31), ccc3(255, 255, 255), ccc3(248, 223, 255), ccc3(243, 138, 255)); break;
			case GauntletType::Magic: editGauntletSingle("Magic", ccc3(14, 16, 51), ccc3(255, 255, 255), ccc3(77, 250, 255), ccc3(36, 52, 145)); break;
			case GauntletType::Spike: editGauntletSingle("Spike", ccc3(73, 69, 50), ccc3(255, 255, 255), ccc3(245, 233, 177), ccc3(173, 161, 46)); break;
			case GauntletType::Monster: editGauntletSingle("Monster", ccc3(23, 78, 30), ccc3(255, 255, 255), ccc3(65, 214, 35), ccc3(8, 110, 13)); break;
			case GauntletType::Doom: editGauntletSingle("Doom", ccc3(48, 36, 33), ccc3(255, 255, 255), ccc3(141, 133, 128), ccc3(75, 69, 60)); break;
			case GauntletType::Death: editGauntletSingle("Death", ccc3(22, 22, 22), ccc3(255, 255, 255), ccc3(100, 100, 100), ccc3(48, 48, 48)); break;
			case GauntletType::Forest: editGauntletSingle("Forest", ccc3(33, 68, 34), ccc3(255, 255, 255), ccc3(148, 255, 98), ccc3(61, 165, 20)); break;
			case GauntletType::Water: editGauntletSingle("Water", ccc3(13, 11, 48), ccc3(255, 255, 255), ccc3(78, 212, 230), ccc3(18, 80, 151)); break;
			case GauntletType::Inferno: editGauntletSingle("Inferno", ccc3(70, 24, 54), ccc3(255, 255, 255), ccc3(255, 223, 67), ccc3(208, 58, 0)); break;
			case GauntletType::Portal: editGauntletSingle("Portal", ccc3(31, 49, 77), ccc3(255, 255, 255), ccc3(255, 50, 140), ccc3(146, 13, 95)); break;
			case GauntletType::Strange: editGauntletSingle("Strange", ccc3(42, 52, 3), ccc3(255, 255, 255), ccc3(203, 134, 255), ccc3(112, 59, 117)); break;
			case GauntletType::Fantasy: editGauntletSingle("Fantasy", ccc3(75, 58, 30), ccc3(255, 255, 255), ccc3(185, 255, 92), ccc3(73, 126, 38)); break;
			case GauntletType::Mystery: editGauntletSingle("Mystery", ccc3(75, 51, 1), ccc3(255, 255, 255), ccc3(255, 233, 23), ccc3(255, 146, 0)); break;
			case GauntletType::Cursed: editGauntletSingle("Cursed", ccc3(46, 14, 43), ccc3(255, 255, 255), ccc3(81, 255, 0), ccc3(8, 121, 4)); break;
			case GauntletType::Cyborg: editGauntletSingle("Cyborg", ccc3(50, 50, 50), ccc3(255, 255, 255), ccc3(182, 228, 237), ccc3(63, 88, 123)); break;
			case GauntletType::Castle: editGauntletSingle("Castle", ccc3(62, 90, 122), ccc3(255, 255, 255), ccc3(190, 214, 230), ccc3(105, 119, 136)); break;
			case GauntletType::World: editGauntletSingle("World", ccc3(35, 37, 175), ccc3(255, 255, 255), ccc3(122, 233, 31), ccc3(54, 109, 33)); break;
			case GauntletType::Galaxy: editGauntletSingle("Galaxy", ccc3(40, 26, 44), ccc3(255, 255, 255), ccc3(255, 180, 255), ccc3(181, 9, 149)); break;
			case GauntletType::Universe: editGauntletSingle("Universe", ccc3(36, 70, 105), ccc3(255, 255, 255), ccc3(255, 252, 104), ccc3(255, 1, 136)); break;
			case GauntletType::Discord: editGauntletSingle("Discord", ccc3(44, 47, 51), ccc3(255, 255, 255), ccc3(88, 101, 212), ccc3(35, 41, 99)); break;
			case GauntletType::Split: editGauntletSingle("Split", ccc3(62, 63, 86), ccc3(255, 255, 255), ccc3(109, 110, 151), ccc3(255, 110, 237)); break;
		}

		m_fields->m_loaded = true;
		log::debug("{}", static_cast<int>(m_gauntletType));
	}

	void editGauntletSingle(const std::string& title, ccColor3B bgColor, ccColor3B outlineColor, ccColor3B titleColor, ccColor3B highlightColor) {
		auto gauntletOutlineText = CCLabelBMFont::create(std::string(title + " Gauntlet").c_str(), "GR_OxygeneFontOutline.fnt"_spr);
		auto gauntletHighlightText = CCLabelBMFont::create(std::string(title + " Gauntlet").c_str(), "GR_OxygeneFontHighlight.fnt"_spr);

		auto gauntletTitleText = static_cast<CCLabelBMFont*>(this->getChildByID("title-shadow"));
		if (!gauntletTitleText) return;

		auto gauntletShadowText = static_cast<CCLabelBMFont*>(this->getChildByID("title"));
		if (!gauntletShadowText) return;

		// Colors //
		m_backgroundSprite->setColor(bgColor);
		gauntletOutlineText->setColor(outlineColor);
		gauntletTitleText->setColor(titleColor);
		gauntletHighlightText->setColor(highlightColor);

		// Text Edits //

		// Highlights //
			gauntletHighlightText->setID("title-Highlight");
			gauntletHighlightText->setFntFile("GR_OxygeneFontHighlight.fnt"_spr);
			gauntletHighlightText->setScale(0.75);
			gauntletHighlightText->setPosition(286.25, 290);

		// Outline //
			gauntletOutlineText->setID("title-Outline"_spr);
			gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
			gauntletOutlineText->setScale(0.75);
			gauntletOutlineText->setPosition(283.38, 290);

		// Title //
			gauntletTitleText->setString(std::string(title + " Gauntlet").c_str());

		// Shadow //
			gauntletShadowText->setString(std::string(title + " Gauntlet").c_str());
		
		this->addChild(gauntletOutlineText);
		this->addChild(gauntletHighlightText);
		
		gauntletHighlightText->setZOrder(37);
	}
};
