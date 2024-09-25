#include <Geode/modify/GauntletLayer.hpp>

using namespace geode::prelude;

#ifdef GEODE_IS_WINDOWS
#include <geode.custom-keybinds/include/Keybinds.hpp>

using namespace keybinds;

#endif

class $modify(RedesignedGauntletLayer, GauntletLayer) {
	struct Fields {
		bool m_loaded = false;
	};

	#ifdef GEODE_IS_WINDOWS
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) {
				callback();
			}
			return ListenerResult::Propagate;
		}, id);
	}

	void gauntletLevel(int desiredLevel) {
		if (const auto gauntletLevel = getChildByIDRecursive("levels-menu")->getChildByIDRecursive(fmt::format("level-{}", desiredLevel))) {
			auto gauntletSprite = getChildOfType<GauntletSprite>(gauntletLevel, 0);
			if (!gauntletSprite) return;
			for (auto node : CCArrayExt<CCNode*>(gauntletSprite->getChildren())) {
				if (typeinfo_cast<CCSpriteGrayscale*>(node)) return;
			}
			GauntletLayer::onLevel(gauntletLevel);
		}
	}
	#endif

	bool init(GauntletType p0) {
		if (!GauntletLayer::init(p0))
			return false;

		#ifdef GEODE_IS_WINDOWS
		this->defineKeybind("first-gauntlet-level"_spr, [this]() {
			RedesignedGauntletLayer::gauntletLevel(1); // default: numrow 1
		});
		this->defineKeybind("second-gauntlet-level"_spr, [this]() {
			RedesignedGauntletLayer::gauntletLevel(2); // default: numrow 2
		});
		this->defineKeybind("third-gauntlet-level"_spr, [this]() {
			RedesignedGauntletLayer::gauntletLevel(3); // default: numrow 3
		});
		this->defineKeybind("fourth-gauntlet-level"_spr, [this]() {
			RedesignedGauntletLayer::gauntletLevel(4); // default: numrow 4
		});
		this->defineKeybind("fifth-gauntlet-level"_spr, [this]() {
			RedesignedGauntletLayer::gauntletLevel(5); // default: numrow 5
		});
		#endif

		if (this->m_levels != nullptr && !m_fields->m_loaded)
			editGauntlets();

		return true;
	}

	void loadLevelsFinished(CCArray* p0, char const* p1, int p2) {
		GauntletLayer::loadLevelsFinished(p0, p1, p2);

		if (m_fields->m_loaded) return;

		editGauntlets();

	}
	void editGauntlets() {

	auto winSizeX = CCDirector::sharedDirector()->getWinSize().width;
	auto winSizeY = CCDirector::sharedDirector()->getWinSize().height;

	// this is the shadow text for whatever fuckall reason
	auto gauntletShadowText = static_cast<CCLabelBMFont*>(this->getChildByID("title"));
	if (!gauntletShadowText) return;

	gauntletShadowText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
	gauntletShadowText->setColor(ccc3(0, 0, 0));
	gauntletShadowText->setScale(0.750);
	gauntletShadowText->setPositionX(winSizeX / 2 + 1);
	gauntletShadowText->setPositionY(winSizeY - 32.5);

	// and this is the actual title text like what dude
	auto gauntletTitleText = static_cast<CCLabelBMFont*>(this->getChildByID("title-shadow"));
	if (!gauntletTitleText) return;

	gauntletTitleText->setFntFile("GR_OxygeneFont.fnt"_spr);
	gauntletTitleText->setColor(ccc3(255, 255, 255));
	gauntletTitleText->setScale(0.750);
	gauntletTitleText->setPositionX(winSizeX / 2);
	gauntletTitleText->setPositionY(winSizeY - 30);

	switch(m_gauntletType) {
		default: break;
	
	// Active Gauntlets
		case GauntletType::Fire: editGauntletSingle("Fire", ccc3(63, 29, 9), ccc3(255, 255, 255), ccc3(255, 255, 0), ccc3(231, 79, 0)); break;
		case GauntletType::Ice: editGauntletSingle("Ice", ccc3(8, 68, 83), ccc3(255, 255, 255), ccc3(192, 236, 255), ccc3(0, 174, 255)); break;
		case GauntletType::Poison: editGauntletSingle("Poison", ccc3(20, 63, 9), ccc3(255, 255, 255), ccc3(229, 255, 0), ccc3(80, 179, 0)); break;
		case GauntletType::Shadow: editGauntletSingle("Shadow", ccc3(46, 19, 45), ccc3(255, 255, 255), ccc3(177, 1, 255), ccc3(59, 0, 141)); break;
		case GauntletType::Lava: editGauntletSingle("Lava", ccc3(63, 9, 9), ccc3(255, 255, 255), ccc3(255, 209, 56), ccc3(255, 51, 0)); break;
		case GauntletType::Bonus: editGauntletSingle("Bonus", ccc3(30, 54, 85), ccc3(255, 255, 255), ccc3(255, 241, 20), ccc3(226, 102, 0)); break;
		case GauntletType::Chaos: editGauntletSingle("Chaos", ccc3(33, 12, 6), ccc3(255, 255, 255), ccc3(255, 145, 0), ccc3(255, 18, 0)); break;
		case GauntletType::Demon: editGauntletSingle("Demon", ccc3(29, 29, 29), ccc3(255, 255, 255), ccc3(202, 81, 81), ccc3(99, 3, 3)); break;
		case GauntletType::Time: editGauntletSingle("Time", ccc3(17, 69, 128), ccc3(255, 255, 255), ccc3(64, 252, 200), ccc3(17, 114, 90)); break;
		case GauntletType::Crystal: editGauntletSingle("Crystal", ccc3(51, 2, 31), ccc3(255, 255, 255), ccc3(248, 223, 255), ccc3(246, 58, 218)); break;
		case GauntletType::Magic: editGauntletSingle("Magic", ccc3(14, 16, 51), ccc3(255, 255, 255), ccc3(77, 250, 255), ccc3(36, 52, 145)); break;
		case GauntletType::Spike: editGauntletSingle("Monster", ccc3(23, 58, 28), ccc3(255, 255, 255), ccc3(65, 214, 35), ccc3(8, 110, 13)); break;
		case GauntletType::Doom: editGauntletSingle("Doom", ccc3(48, 36, 33), ccc3(255, 255, 255), ccc3(141, 133, 128), ccc3(75, 69, 60)); break;
		case GauntletType::Death: editGauntletSingle("Death", ccc3(22, 22, 22), ccc3(255, 255, 255), ccc3(100, 100, 100), ccc3(48, 48, 48)); break;
		case GauntletType::Forest: editGauntletSingle("Forest", ccc3(33, 68, 34), ccc3(255, 255, 255), ccc3(148, 255, 98), ccc3(61, 165, 20)); break;
		case GauntletType::Water: editGauntletSingle("Water", ccc3(13, 11, 48), ccc3(255, 255, 255), ccc3(78, 212, 230), ccc3(18, 80, 151)); break;
		case GauntletType::Inferno: editGauntletSingle("Inferno", ccc3(70, 24, 54), ccc3(255, 255, 255), ccc3(255, 223, 67), ccc3(208, 58, 0)); break;
		case GauntletType::Portal: editGauntletSingle("Portal", ccc3(31, 49, 77), ccc3(255, 255, 255), ccc3(255, 50, 140), ccc3(109, 34, 86)); break;
		case GauntletType::Strange: editGauntletSingle("Strange", ccc3(42, 52, 3), ccc3(255, 255, 255), ccc3(203, 134, 255), ccc3(112, 59, 117)); break;
		case GauntletType::Fantasy: editGauntletSingle("Fantasy", ccc3(75, 58, 30), ccc3(255, 255, 255), ccc3(185, 255, 92), ccc3(73, 126, 38)); break;
		case GauntletType::Mystery: editGauntletSingle("Mystery", ccc3(75, 51, 1), ccc3(255, 255, 255), ccc3(255, 233, 23), ccc3(255, 146, 0)); break;
		case GauntletType::Cursed: editGauntletSingle("Cursed", ccc3(46, 14, 43), ccc3(255, 255, 255), ccc3(81, 255, 0), ccc3(8, 121, 4)); break;
		case GauntletType::Cyborg: editGauntletSingle("Cyborg", ccc3(50, 50, 50), ccc3(255, 255, 255), ccc3(182, 228, 237), ccc3(63, 88, 123)); break;
		case GauntletType::Castle: editGauntletSingle("Castle", ccc3(62, 90, 122), ccc3(255, 255, 255), ccc3(190, 214, 230), ccc3(105, 119, 136)); break;
		case GauntletType::World: editGauntletSingle("World", ccc3(35, 37, 175), ccc3(255, 255, 255), ccc3(122, 233, 31), ccc3(54, 109, 33)); break;
		case GauntletType::Galaxy: editGauntletSingle("Galaxy", ccc3(40, 26, 44), ccc3(255, 255, 255), ccc3(255, 180, 255), ccc3(181, 9, 149)); break;
		case GauntletType::Universe: editGauntletSingle("Universe", ccc3(36, 70, 105), ccc3(255, 255, 255), ccc3(255, 252, 104), ccc3(255, 1, 136)); break;
		
		// Change Background for Discord Gauntlet
		case GauntletType::Discord: {
			editGauntletSingle("Discord", ccc3(44, 47, 51), ccc3(255, 255, 255), ccc3(88, 101, 212), ccc3(35, 41, 99));
			GameManager::get()->loadBackground(10);
			auto texture = CCTextureCache::sharedTextureCache()->textureForKey("game_bg_10_001.png");
			this->m_backgroundSprite->setTexture(texture);
			break;
		}

		case GauntletType::Split: editGauntletSingle("Split", ccc3(62, 63, 86), ccc3(255, 255, 255), ccc3(109, 110, 151), ccc3(255, 110, 237)); break;

	// Inactive Gauntlets
		case GauntletType::Acid: editGauntletSingle("Acid", ccc3(45, 38, 17), ccc3(255, 255, 255), ccc3(208, 255, 0), ccc3(162, 255, 24)); break;
		case GauntletType::Christmas: editGauntletSingle("Christmas", ccc3(0, 23, 48), ccc3(255, 255, 255), ccc3(255, 0, 0), ccc3(255, 208, 0)); break;
		case GauntletType::Dragon: editGauntletSingle("Dragon", ccc3(46, 0, 0), ccc3(255, 255, 255), ccc3(0, 255, 0), ccc3(255, 236, 127)); break;
		case GauntletType::Force: editGauntletSingle("Force", ccc3(53, 50, 64), ccc3(255, 255, 255), ccc3(130, 112, 193), ccc3(160, 19, 74)); break;
		case GauntletType::Gem: editGauntletSingle("Gem", ccc3(39, 38, 66), ccc3(255, 255, 255), ccc3(201, 246, 229), ccc3(188, 129, 220)); break;
		case GauntletType::Ghost: editGauntletSingle("Ghost", ccc3(41, 41, 41), ccc3(255, 255, 255), ccc3(226, 226, 226), ccc3(153, 153, 153)); break;
		case GauntletType::Grave: editGauntletSingle("Grave", ccc3(23, 32, 31), ccc3(255, 255, 255), ccc3(176, 195, 207), ccc3(80, 66, 87)); break;
		case GauntletType::Halloween: editGauntletSingle("Halloween", ccc3(39, 36, 12), ccc3(255, 255, 255), ccc3(255, 100, 3), ccc3(173, 34, 34)); break;
		case GauntletType::Haunted: editGauntletSingle("Haunted", ccc3(28, 36, 33), ccc3(255, 255, 255), ccc3(255, 255, 110), ccc3(72, 45, 54)); break;
		case GauntletType::Potion: editGauntletSingle("Potion", ccc3(58, 30, 52), ccc3(255, 255, 255), ccc3(255, 0, 144), ccc3(139, 0, 148)); break;
		case GauntletType::Power: editGauntletSingle("Power", ccc3(72, 58, 42), ccc3(255, 255, 255), ccc3(206, 174, 149), ccc3(116, 87, 56)); break;
		case GauntletType::Rune: editGauntletSingle("Rune", ccc3(46, 18, 0), ccc3(255, 255, 255), ccc3(227, 130, 33), ccc3(100, 28, 0)); break;
		case GauntletType::Snake: editGauntletSingle("Snake", ccc3(66, 31, 114), ccc3(255, 255, 255), ccc3(209, 167, 107), ccc3(110, 57, 34)); break;
		case GauntletType::Spider: editGauntletSingle("Spider", ccc3(44, 52, 56), ccc3(255, 255, 255), ccc3(141, 192, 209), ccc3(75, 66, 91)); break;
		case GauntletType::Spooky: editGauntletSingle("Spooky", ccc3(55, 167, 173), ccc3(255, 255, 255), ccc3(232, 52, 24), ccc3(109, 43, 17)); break;
		case GauntletType::Surprise: editGauntletSingle("Surprise", ccc3(42, 52, 3), ccc3(255, 255, 255), ccc3(213, 52, 40), ccc3(100, 41, 18)); break;
		case GauntletType::Temple: editGauntletSingle("Temple", ccc3(36, 37, 13), ccc3(255, 255, 255), ccc3(255, 226, 184), ccc3(116, 93, 63)); break;
		case GauntletType::Toxic: editGauntletSingle("Toxic", ccc3(41, 4, 43), ccc3(255, 255, 255), ccc3(0, 248, 0), ccc3(9, 87, 8)); break;
		case GauntletType::Treasure: editGauntletSingle("Treasure", ccc3(43, 49, 38), ccc3(255, 255, 255), ccc3(249, 129, 48), ccc3(136, 39, 0)); break;
		case GauntletType::Witch: editGauntletSingle("Witch", ccc3(0, 44, 25), ccc3(255, 255, 255), ccc3(66, 99, 125), ccc3(35, 13, 46)); break;
		
		// Reserved for 2.21
		// case GauntletType::NCS: editGauntletSingle("NCS", ccc3(0, 0, 0,), ccc3(255, 255, 255), ccc3(32, 254, 254), ccc3(0, 0, 0)); break;
		// case GauntletType::NCS2: editGauntletSingle("NCS2", ccc3(0, 0, 0,), ccc3(255, 255, 255), ccc3(255, 152, 255), ccc3(0, 0, 0)); break;
	}

	// m_fields->m_loaded = true;
	// log::debug("{}", static_cast<int>(m_gauntletType));
	}

	void editGauntletSingle(const std::string& title, ccColor3B bgColor, ccColor3B outlineColor, ccColor3B titleColor, ccColor3B highlightColor) {
		
		auto winSizeX = CCDirector::sharedDirector()->getWinSize().width;
		auto winSizeY = CCDirector::sharedDirector()->getWinSize().height;

		auto gauntletOutlineText = CCLabelBMFont::create(std::string(title + " Gauntlet").c_str(), "GR_OxygeneFontOutline.fnt"_spr);
		auto gauntletHighlightText = CCLabelBMFont::create(std::string(title + " Gauntlet").c_str(), "GR_OxygeneFontHighlight.fnt"_spr);

		auto gauntletTitleText = static_cast<CCLabelBMFont*>(this->getChildByID("title-shadow"));
		if (!gauntletTitleText) return;

		auto gauntletShadowText = static_cast<CCLabelBMFont*>(this->getChildByID("title"));
		if (!gauntletShadowText) return;

	// Colors
		m_backgroundSprite->setColor(bgColor);
		gauntletOutlineText->setColor(outlineColor);
		gauntletTitleText->setColor(titleColor);
		gauntletHighlightText->setColor(highlightColor);

	// Text Highlights
		gauntletHighlightText->setID("title-highlight");
		gauntletHighlightText->setFntFile("GR_OxygeneFontHighlight.fnt"_spr);
		gauntletHighlightText->setScale(0.75);
		gauntletHighlightText->setPositionX(winSizeX / 2 + 2);
		gauntletHighlightText->setPositionY(winSizeY - 30);

	// Text Outlines
		gauntletOutlineText->setID("title-outline");
		gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
		gauntletOutlineText->setScale(0.75);
		gauntletOutlineText->setPositionX(winSizeX / 2 - 1.5);
		gauntletOutlineText->setPositionY(winSizeY - 30);

	// Title
		gauntletTitleText->setString(std::string(title + " Gauntlet").c_str());

	// Shadow
		gauntletShadowText->setString(std::string(title + " Gauntlet").c_str());
		
		this->addChild(gauntletOutlineText);
		this->addChild(gauntletHighlightText);
		
		gauntletHighlightText->setZOrder(37);
	}
};

#ifdef GEODE_IS_WINDOWS
$execute {
	BindManager::get()->registerBindable({
		"first-gauntlet-level"_spr,
		"First Gauntlet Level",
		"Use this keybind (set to 1 by default) to view the first gauntlet level.",
		{ Keybind::create(KEY_One) },
		"Global/Gauntlet Touchup"
	});
	BindManager::get()->registerBindable({
		"second-gauntlet-level"_spr,
		"Second Gauntlet Level",
		"Use this keybind (set to 2 by default) to view the second gauntlet level.",
		{ Keybind::create(KEY_Two) },
		"Global/Gauntlet Touchup"
	});
	BindManager::get()->registerBindable({
		"third-gauntlet-level"_spr,
		"Third Gauntlet Level",
		"Use this keybind (set to 3 by default) to view the third gauntlet level.",
		{ Keybind::create(KEY_Three) },
		"Global/Gauntlet Touchup"
	});
	BindManager::get()->registerBindable({
		"fourth-gauntlet-level"_spr,
		"Fourth Gauntlet Level",
		"Use this keybind (set to 4 by default) to view the fourth gauntlet level.",
		{ Keybind::create(KEY_Four) },
		"Global/Gauntlet Touchup"
	});
	BindManager::get()->registerBindable({
		"fifth-gauntlet-level"_spr,
		"Fifth Gauntlet Level",
		"Use this keybind (set to 5 by default) to view the fifth gauntlet level.",
		{ Keybind::create(KEY_Five) },
		"Global/Gauntlet Touchup"
	});
}
#endif