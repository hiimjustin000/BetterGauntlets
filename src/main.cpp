#include <Geode/Geode.hpp>
#include <Geode/modify/GauntletLayer.hpp>

using namespace geode::prelude;

class $modify(RedesignedGauntletLayer, GauntletLayer) {
	void setupGauntlet(cocos2d::CCArray* p0) {
		GauntletLayer::setupGauntlet(p0);

		auto backgroundSprite = static_cast<CCSprite*>(this->getChildByIDRecursive("background"));
		if (!backgroundSprite) return;


		// this is the shadow text for whatever fuckall reason
		auto gauntletShadowText = static_cast<CCLabelBMFont*>(this->getChildByIDRecursive("title"));
		if (!gauntletShadowText) return;
		
		gauntletShadowText->setID("title-Shadow");
		gauntletShadowText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
		gauntletShadowText->setColor(ccc3(0, 0, 0));
		gauntletShadowText->setScale(0.750);
		gauntletShadowText->setPosition(286.50, 287);
		
		// and this is the actual title text like what dude
		auto gauntletTitleText = static_cast<CCLabelBMFont*>(this->getChildByIDRecursive("title-shadow"));
		if (!gauntletTitleText) return;
		
		gauntletTitleText->setID("title-Main");
		gauntletTitleText->setFntFile("GR_OxygeneFont.fnt"_spr);
		gauntletTitleText->setColor(ccc3(255, 255, 255));
		gauntletTitleText->setScale(0.750);
		gauntletTitleText->setPosition(284.50, 290);


	// because GauntletType::Fire is fucking itself over rn. why? idfk :sob:
			if (static_cast<int>(m_gauntletType) == 1) {
				auto gauntletOutlineText = CCLabelBMFont::create("Fire Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(63, 29, 9));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(255, 169, 57));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

			this->addChild(gauntletOutlineText);
				log::debug("Fire");
			}


			if (static_cast<int>(m_gauntletType) == 2) {
				auto gauntletOutlineText = CCLabelBMFont::create("Ice Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(8, 68, 83));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(120, 255, 255));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Ice");
			}


			if (static_cast<int>(m_gauntletType) == 3) {
				auto gauntletOutlineText = CCLabelBMFont::create("Poison Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(20, 63, 9));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(132, 255, 128));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Poison");
			}


			if (static_cast<int>(m_gauntletType) == 4) {
				auto gauntletOutlineText = CCLabelBMFont::create("Shadow Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(46, 19, 45));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(230, 128, 255));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Shadow");
			}


			if (static_cast<int>(m_gauntletType) == 5) {
				auto gauntletOutlineText = CCLabelBMFont::create("Lava Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(63, 9, 9));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(252, 170, 75));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Lava");
			}


			if (static_cast<int>(m_gauntletType) == 6) {
				auto gauntletOutlineText = CCLabelBMFont::create("Bonus Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(30, 54, 85));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(255, 245, 155));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Bonus");
			}

			if (static_cast<int>(m_gauntletType) == 7) {
				auto gauntletOutlineText = CCLabelBMFont::create("Chaos Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(54, 54, 54));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(126, 68, 68));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Chaos");
			}


			if (static_cast<int>(m_gauntletType) == 8) {
				auto gauntletOutlineText = CCLabelBMFont::create("Demon Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(29, 29, 29));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(199, 45, 45));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Demon");
			}


			if (static_cast<int>(m_gauntletType) == 9) {
				auto gauntletOutlineText = CCLabelBMFont::create("Time Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(10, 8, 117));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(103, 113, 255));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Time");
			}


			if (static_cast<int>(m_gauntletType) == 10) {
				auto gauntletOutlineText = CCLabelBMFont::create("Crystal Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(78, 23, 62));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(244, 190, 255));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Crystal");
			}


			if (static_cast<int>(m_gauntletType) == 11) {
				auto gauntletOutlineText = CCLabelBMFont::create("Magic Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(25, 13, 59));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(185, 159, 235));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Magic");
			}


			if (static_cast<int>(m_gauntletType) == 12) {
				auto gauntletOutlineText = CCLabelBMFont::create("Spike Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(73, 69, 50));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(245, 233, 177));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Spike");
			}


			if (static_cast<int>(m_gauntletType) == 13) {
				auto gauntletOutlineText = CCLabelBMFont::create("Monster Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(23, 78, 30));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(59, 160, 39));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Monster");
			}


			if (static_cast<int>(m_gauntletType) == 14) {
				auto gauntletOutlineText = CCLabelBMFont::create("Doom Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(48, 36, 33));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(141, 133, 128));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Doom");
			}

			if (static_cast<int>(m_gauntletType) == 15) {
				auto gauntletOutlineText = CCLabelBMFont::create("Death Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(22, 22, 22));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(100, 100, 100));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Death");
			}

			
			if (static_cast<int>(m_gauntletType) == 16) {
				auto gauntletOutlineText = CCLabelBMFont::create("Forest Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(33, 68, 34));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(137, 172, 121));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Forest");
			}


			if (static_cast<int>(m_gauntletType) == 21) {
				auto gauntletOutlineText = CCLabelBMFont::create("Water Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(13, 11, 48));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(78, 101, 230));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Water");
			}


			if (static_cast<int>(m_gauntletType) == 34) {
				auto gauntletOutlineText = CCLabelBMFont::create("Inferno Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(43, 12, 41));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(207, 130, 41));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Inferno");
			}


			if (static_cast<int>(m_gauntletType) == 35) {
				auto gauntletOutlineText = CCLabelBMFont::create("Portal Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(39, 50, 58));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(184, 66, 125));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Portal");
			}


			if (static_cast<int>(m_gauntletType) == 36) {
				auto gauntletOutlineText = CCLabelBMFont::create("Strange Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(36, 68, 46));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(180, 125, 190));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Strange");
			}


			if (static_cast<int>(m_gauntletType) == 37) {
				auto gauntletOutlineText = CCLabelBMFont::create("Fantasy Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(54, 40, 18));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(151, 201, 85));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Fantasy");
			}


			if (static_cast<int>(m_gauntletType) == 40) {
				auto gauntletOutlineText = CCLabelBMFont::create("Mystery Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(47, 71, 36));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(216, 174, 57));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Mystery");
			}


			if (static_cast<int>(m_gauntletType) == 41) {
				auto gauntletOutlineText = CCLabelBMFont::create("Cursed Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(46, 14, 43));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(159, 255, 114));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Cursed");
			}


			if (static_cast<int>(m_gauntletType) == 42) {
				auto gauntletOutlineText = CCLabelBMFont::create("Cyborg Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(50, 50, 50));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(195, 219, 214));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Cyborg");
			}


			if (static_cast<int>(m_gauntletType) == 43) {
				auto gauntletOutlineText = CCLabelBMFont::create("Castle Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(62, 90, 122));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(190, 214, 230));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Castle");
			}


			if (static_cast<int>(m_gauntletType) == 46) {
				auto gauntletOutlineText = CCLabelBMFont::create("World Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(76, 77, 165));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(154, 231, 90));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("World");
			}


			if (static_cast<int>(m_gauntletType) == 47) {
				auto gauntletOutlineText = CCLabelBMFont::create("Galaxy Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(40, 26, 44));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(249, 75, 255));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Galaxy");
			}


			if (static_cast<int>(m_gauntletType) == 48) {
				auto gauntletOutlineText = CCLabelBMFont::create("Universe Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(23, 1, 36));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(255, 94, 0));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Universe");
			}


			if (static_cast<int>(m_gauntletType) == 49) {
				auto gauntletOutlineText = CCLabelBMFont::create("Discord Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(31, 35, 75));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(88, 101, 212));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Discord");
			}


			if (static_cast<int>(m_gauntletType) == 50) {
				auto gauntletOutlineText = CCLabelBMFont::create("Split Gauntlet", "GR_OxygeneFontOutline.fnt"_spr);

				// ----- Colors ----- //
				backgroundSprite->setColor(ccc3(50, 50, 50));
				gauntletOutlineText->setColor(ccc3(255, 255, 255));
				gauntletTitleText->setColor(ccc3(255, 90, 192));

				// ----- Font Edits ----- //
				gauntletOutlineText->setID("title-Highlight");
				gauntletOutlineText->setFntFile("GR_OxygeneFontOutline.fnt"_spr);
				gauntletOutlineText->setScale(0.750);
				gauntletOutlineText->setPosition(283.38, 290);

				this->addChild(gauntletOutlineText);
					log::debug("Split");
			}

			log::debug("{}", static_cast<int>(m_gauntletType));
		}

	void loadLevelsFinished(CCArray* p0, char const* p1, int p2) {
		GauntletLayer::loadLevelsFinished(p0, p1, p2);

		
	}
};