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
			case GauntletType::Fire: editGauntletSingle("Fire", ccc3(63, 29, 9), ccc3(255, 255, 255), ccc3(255, 169, 57)); break;
			case GauntletType::Ice: editGauntletSingle("Ice", ccc3(8, 68, 83), ccc3(255, 255, 255), ccc3(120, 255, 255)); break;
			case GauntletType::Poison: editGauntletSingle("Poison", ccc3(20, 63, 9), ccc3(255, 255, 255), ccc3(132, 255, 128)); break;
			case GauntletType::Shadow: editGauntletSingle("Shadow", ccc3(46, 19, 45), ccc3(255, 255, 255), ccc3(230, 128, 255)); break;
			case GauntletType::Lava: editGauntletSingle("Lava", ccc3(63, 9, 9), ccc3(255, 255, 255), ccc3(252, 170, 75)); break;
			case GauntletType::Bonus: editGauntletSingle("Bonus", ccc3(30, 54, 85), ccc3(255, 255, 255), ccc3(255, 245, 155)); break;
			case GauntletType::Chaos: editGauntletSingle("Chaos", ccc3(54, 54, 54), ccc3(255, 255, 255), ccc3(126, 68, 68)); break;
			case GauntletType::Demon: editGauntletSingle("Demon", ccc3(29, 29, 29), ccc3(255, 255, 255), ccc3(199, 45, 45)); break;
			case GauntletType::Time: editGauntletSingle("Time", ccc3(10, 8, 117), ccc3(255, 255, 255), ccc3(103, 113, 255)); break;
			case GauntletType::Crystal: editGauntletSingle("Crystal", ccc3(78, 23, 62), ccc3(255, 255, 255), ccc3(244, 190, 255)); break;
			case GauntletType::Magic: editGauntletSingle("Magic", ccc3(25, 13, 59), ccc3(255, 255, 255), ccc3(185, 159, 235)); break;
			case GauntletType::Spike: editGauntletSingle("Spike", ccc3(73, 69, 50), ccc3(255, 255, 255), ccc3(245, 233, 177)); break;
			case GauntletType::Monster: editGauntletSingle("Monster", ccc3(23, 78, 30), ccc3(255, 255, 255), ccc3(59, 160, 39)); break;
			case GauntletType::Doom: editGauntletSingle("Doom", ccc3(48, 36, 33), ccc3(255, 255, 255), ccc3(141, 133, 128)); break;
			case GauntletType::Death: editGauntletSingle("Death", ccc3(22, 22, 22), ccc3(255, 255, 255), ccc3(100, 100, 100)); break;
			case GauntletType::Forest: editGauntletSingle("Forest", ccc3(33, 68, 34), ccc3(255, 255, 255), ccc3(137, 172, 121)); break;
			case GauntletType::Water: editGauntletSingle("Water", ccc3(13, 11, 48), ccc3(255, 255, 255), ccc3(78, 101, 230)); break;
			case GauntletType::Inferno: editGauntletSingle("Inferno", ccc3(43, 12, 41), ccc3(255, 255, 255), ccc3(207, 130, 41)); break;
			case GauntletType::Portal: editGauntletSingle("Portal", ccc3(39, 50, 58), ccc3(255, 255, 255), ccc3(184, 66, 125)); break;
			case GauntletType::Strange: editGauntletSingle("Strange", ccc3(36, 68, 46), ccc3(255, 255, 255), ccc3(180, 125, 190)); break;
			case GauntletType::Fantasy: editGauntletSingle("Fantasy", ccc3(54, 40, 18), ccc3(255, 255, 255), ccc3(151, 201, 85)); break;
			case GauntletType::Mystery: editGauntletSingle("Mystery", ccc3(47, 71, 36), ccc3(255, 255, 255), ccc3(216, 174, 57)); break;
			case GauntletType::Cursed: editGauntletSingle("Cursed", ccc3(46, 14, 43), ccc3(255, 255, 255), ccc3(159, 255, 114)); break;
			case GauntletType::Cyborg: editGauntletSingle("Cyborg", ccc3(50, 50, 50), ccc3(255, 255, 255), ccc3(195, 219, 214)); break;
			case GauntletType::Castle: editGauntletSingle("Castle", ccc3(62, 90, 122), ccc3(255, 255, 255), ccc3(190, 214, 230)); break;
			case GauntletType::World: editGauntletSingle("World", ccc3(76, 77, 165), ccc3(255, 255, 255), ccc3(154, 231, 90)); break;
			case GauntletType::Galaxy: editGauntletSingle("Galaxy", ccc3(40, 26, 44), ccc3(255, 255, 255), ccc3(249, 75, 255)); break;
			case GauntletType::Universe: editGauntletSingle("Universe", ccc3(23, 1, 36), ccc3(255, 255, 255), ccc3(255, 94, 0)); break;
			case GauntletType::Discord: editGauntletSingle("Discord", ccc3(31, 35, 75), ccc3(255, 255, 255), ccc3(88, 101, 212)); break;
			case GauntletType::Split: editGauntletSingle("Split Gauntlet", ccc3(50, 50, 50), ccc3(255, 255, 255), ccc3(255, 90, 192)); break;
		}

		m_fields->m_loaded = true;
		log::debug("{}", static_cast<int>(m_gauntletType));
	}

	void editGauntletSingle(const std::string& title, ccColor3B bgColor, ccColor3B outlineTextColor, ccColor3B titleColor) {
		auto gauntletOutlineText = CCLabelBMFont::create(std::string(title + " Gauntlet").c_str(), "GR_OxygeneFontOutline.fnt"_spr);

		auto gauntletTitleText = static_cast<CCLabelBMFont*>(this->getChildByID("title-shadow"));
		if (!gauntletTitleText) return;

		// ----- Colors ----- //
		m_backgroundSprite->setColor(bgColor);
		gauntletOutlineText->setColor(outlineTextColor);
		gauntletTitleText->setColor(titleColor);

		// ----- Font Edits ----- //
		gauntletOutlineText->setID("title-Highlight"_spr);
		gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
		gauntletOutlineText->setScale(0.750);
		gauntletOutlineText->setPosition(283.38, 290);

		this->addChild(gauntletOutlineText);
	}
};
