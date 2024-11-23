#include <Geode/modify/GauntletSelectLayer.hpp>

using namespace geode::prelude;
#ifdef GEODE_IS_WINDOWS
#include <geode.custom-keybinds/include/Keybinds.hpp>
using namespace keybinds;
#endif 

class $modify(RedesignedGauntletSelectLayer, GauntletSelectLayer) {
    struct Fields {
        std::vector<CCMenuItemSpriteExtra*> m_dots = {};
        CCMenu* m_dotsMenu = nullptr;
        int currentGauntletPage = 0;
    };

    void updateDots() {
        auto sfc = CCSpriteFrameCache::sharedSpriteFrameCache();

        for(CCMenuItemSpriteExtra* btn : m_fields->m_dots) {
            auto btnIdx = std::find(m_fields->m_dots.begin(), m_fields->m_dots.end(), btn) - m_fields->m_dots.begin();

            int newPage = m_scrollLayer->m_page;
            if (newPage <= -1) newPage = m_fields->m_dots.size() + newPage;
            if (newPage >= m_fields->m_dots.size()) newPage = newPage % m_fields->m_dots.size();
            // log::info("{}, {}", btnIdx, newPage);

            if (btnIdx == newPage)
                static_cast<CCSprite*>(btn->getNormalImage())->setDisplayFrame(sfc->spriteFrameByName("gj_navDotBtn_on_001.png"));
            else
                static_cast<CCSprite*>(btn->getNormalImage())->setDisplayFrame(sfc->spriteFrameByName("gj_navDotBtn_off_001.png"));
        }
    }

    void setupGauntlets() {
        GauntletSelectLayer::setupGauntlets();

        m_fields->m_dots.clear();
        if (m_fields->m_dotsMenu) {
            m_fields->m_dotsMenu->removeFromParent();
            m_fields->m_dotsMenu = nullptr;
        }

        auto director = CCDirector::sharedDirector();

        m_fields->m_dotsMenu = CCMenu::create();
        m_fields->m_dotsMenu->setLayout(AxisLayout::create());
        m_fields->m_dotsMenu->setPositionY(director->getScreenBottom() + 15.f);
        m_fields->m_dotsMenu->setID("page-navigation"_spr);
        addChild(m_fields->m_dotsMenu);

        for (int i = 0; i < m_scrollLayer->getTotalPages(); i++) {
            auto spr = CCSprite::createWithSpriteFrameName("gj_navDotBtn_off_001.png");
            spr->setScale(0.8f);

            CCMenuItemSpriteExtra* btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(RedesignedGauntletSelectLayer::onDot));
            m_fields->m_dotsMenu->addChild(btn);
            m_fields->m_dots.push_back(btn);
        }

        auto dotsArray = CCArrayExt<CCSprite*>(m_scrollLayer->m_dots);

        for(CCSprite* dot : dotsArray) {
            dot->setVisible(false);
        }
        m_scrollLayer->m_dotsVisible = false;

        updateDots();

        m_fields->m_dotsMenu->updateLayout();

        // thank you ery :3
        if (const auto pageButtons = m_scrollLayer->m_dots) {
            RedesignedGauntletSelectLayer::findCurrentGauntletPageUsing(pageButtons);
        }
        #ifdef GEODE_IS_WINDOWS
        this->defineKeybind("next-gauntlet"_spr, [this]() {
            GauntletSelectLayer::onNext(nullptr); // default: right arrow key
        });
        this->defineKeybind("previous-gauntlet"_spr, [this]() {
            GauntletSelectLayer::onPrev(nullptr); // default: left arrow key
        });
        this->defineKeybind("first-visible-gauntlet"_spr, [this]() {
            RedesignedGauntletSelectLayer::pressGauntlet(1); // default: numrow 1
        });
        this->defineKeybind("second-visible-gauntlet"_spr, [this]() {
            RedesignedGauntletSelectLayer::pressGauntlet(2); // default: numrow 2
        });
        this->defineKeybind("third-visible-gauntlet"_spr, [this]() {
            RedesignedGauntletSelectLayer::pressGauntlet(3); // default: numrow 3
        }); 
        #endif
        
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        log::debug("winSize = {}px, {}px", winSize.width, winSize.height);

        auto main = getChildByID("main-layer");

        // auto title = getChildByID("title");
        // title->setVisible(false);

        // auto cornerBL = getChildByID("bottom-left-corner");
        // cornerBL->setVisible(false);
        
        // auto cornerBR = getChildByID("bottom-right-corner");
        // cornerBR->setVisible(false);

        auto gauntletGround = CCSprite::create("gauntletGround_001.png"_spr);
        if (gauntletGround) {
            gauntletGround->setID("floor");
            gauntletGround->setColor(ccc3(255, 255, 255));
            gauntletGround->setPosition(ccp(winSize.width / 2, director->getScreenBottom() + 20.f));
            gauntletGround->setZOrder(-1);
            gauntletGround->setOpacity(15);
            this->addChild(gauntletGround);
        }
        
        auto chainParentNode = CCNode::create();
        if (chainParentNode) {
            chainParentNode->setID("chain-parent-node");
            chainParentNode->setPosition(0, 0);
            chainParentNode->setZOrder(-1);
            this->addChild(chainParentNode);

            for (int c = 0; c < 15; c++) {

            auto chain = CCSprite::createWithSpriteFrameName("d_03_chain_01_001.png");
            chain->setID(fmt::format("chain-{}", c + 1));
            chain->setColor(ccc3(20, 20, 20));
            chain->setPosition(ccp(0, 0));
            chainParentNode->addChild(chain);
            }
            // first chain pair //
            auto chain1 = getChildByIDRecursive("chain-1");
            chain1->setScale(2.0);
            chain1->setPosition(ccp(80.f, director->getScreenTop() - 0));

            auto chain2 = getChildByIDRecursive("chain-2");
            chain2->setScale(2.0);
            chain2->setPosition(ccp(80.f, director->getScreenTop() - 30));

            auto chain3 = getChildByIDRecursive("chain-3");
            chain3->setScale(2.0);
            chain3->setPosition(ccp(80.f, director->getScreenTop() - 60));

            auto chain4 = getChildByIDRecursive("chain-4");
            chain4->setScale(2.0);
            chain4->setPosition(ccp(80.f, director->getScreenTop() - 90));

            auto chain5 = getChildByIDRecursive("chain-5");
            chain5->setScale(2.0);
            chain5->setPosition(ccp(80.f, director->getScreenTop() - 120));

            // second chain pair //
            auto chain6 = getChildByIDRecursive("chain-6");
            chain6->setScale(1.0);
            chain6->setPosition(ccp(380.f, director->getScreenTop() - 0));

            auto chain7 = getChildByIDRecursive("chain-7");
            chain7->setScale(1.0);
            chain7->setPosition(ccp(380.f, director->getScreenTop() - 15));

            auto chain8 = getChildByIDRecursive("chain-8");
            chain8->setScale(1.0);
            chain8->setPosition(ccp(380.f, director->getScreenTop() - 30));

            auto chain9 = getChildByIDRecursive("chain-9");
            chain9->setScale(1.0);
            chain9->setPosition(ccp(380.f, director->getScreenTop() - 45));

            auto chain10 = getChildByIDRecursive("chain-10");
            chain10->setScale(1.0);
            chain10->setPosition(ccp(380.f, director->getScreenTop() - 60));

            // third chain pair //
            auto chain11 = getChildByIDRecursive("chain-11");
            chain11->setScale(1.65);
            chain11->setPosition(ccp(440.f, director->getScreenTop() - 0));

            auto chain12 = getChildByIDRecursive("chain-12");
            chain12->setScale(1.65);
            chain12->setPosition(ccp(440.f, director->getScreenTop() - 25));

            auto chain13 = getChildByIDRecursive("chain-13");
            chain13->setScale(1.65);
            chain13->setPosition(ccp(440.f, director->getScreenTop() - 50));

            auto chain14 = getChildByIDRecursive("chain-14");
            chain14->setScale(1.65);
            chain14->setPosition(ccp(440.f, director->getScreenTop() - 75));

            auto chain15 = getChildByIDRecursive("chain-15");
            chain15->setScale(1.65);
            chain15->setPosition(ccp(440.f, director->getScreenTop() - 100));
        }

        for (int p = 0; p < 18; p++) {

        auto gauntletList = getChildByIDRecursive("gauntlets-list");
        if (gauntletList) {
            
            auto gauntletPages = gauntletList->getChildByIDRecursive("gauntlet-pages");
            if (gauntletPages) {
                
                auto gauntletPage = gauntletPages->getChildByIDRecursive(fmt::format("gauntlet-page-{}", p + 1));
                if (gauntletPage) {
                    
                    auto gauntletMenu = gauntletPage->getChildByIDRecursive("gauntlet-menu");
                    if (gauntletMenu) {
                        gauntletMenu->setScale(0.85);
                        gauntletMenu->setPosition(0, 5);
                        for (int gb = 0; gb < 3; gb++) {
                            
                            auto gauntletBtn = gauntletMenu->getChildByIDRecursive(fmt::format("gauntlet-button-{}", gb + 1));
                            if (gauntletBtn) {
                                
                                auto gauntletNodePrnt = gauntletBtn->getChildByIDRecursive("gauntlet-node-parent");
                                if (gauntletNodePrnt) {
                                    
                                    auto gauntletNode = gauntletNodePrnt->getChildByIDRecursive("gauntlet-node");
                                    if (gauntletNode) {
                                        
                                        auto bgPortal = Mod::get()->getSettingValue<bool>("update-backgrounds");
                                        if (bgPortal) {

                                            auto nameLabelRepos = gauntletNode->getChildByIDRecursive("gauntlet-name-label");
                                            nameLabelRepos->setScale(0.50);
                                            nameLabelRepos->setPosition(ccp(0, 90));

                                            auto nameLabelShadowRepos = gauntletNode->getChildByIDRecursive("gauntlet-name-shadow-label");
                                            nameLabelShadowRepos->setScale(nameLabelRepos->getScale());
                                            nameLabelShadowRepos->setPosition(ccp(nameLabelRepos->getPositionX() + 1, nameLabelRepos->getPositionY() - 1.5));
                                            
                                            auto gauntletLabel = gauntletNode->getChildByIDRecursive("gauntlet-label");
                                            gauntletLabel->setScale(0.35);
                                            gauntletLabel->setPosition(ccp(0, nameLabelRepos->getPositionY() - 10));
                                            
                                            auto gauntletShadowLabel = gauntletNode->getChildByIDRecursive("gauntlet-shadow-label");
                                            gauntletShadowLabel->setScale(gauntletLabel->getScale());
                                            gauntletShadowLabel->setPosition(ccp(gauntletLabel->getPositionX() + 1, gauntletLabel->getPositionY() - 1.5));

                                            auto infoNode = gauntletNode->getChildByIDRecursive("gauntlet-info-node");
                                                
                                                auto gauntletSprite = infoNode->getChildByIDRecursive("gauntlet-sprite");
                                                if (gauntletSprite) {
                                                    gauntletSprite->setPosition(ccp(0, -92.5));
                                                    gauntletSprite->setScale(0.65);
                                                }
                                                auto chestSprite = infoNode->getChildByIDRecursive("chest-sprite");
                                                if (chestSprite) {
                                                    chestSprite->setPosition(ccp(0, -120.5));
                                                    chestSprite->setScale(0.25);
                                                }
                                                auto chestShadowSprite = infoNode->getChildByIDRecursive("chest-shadow-sprite");
                                                if (chestShadowSprite) {
                                                    chestShadowSprite->setPosition(ccp(chestSprite->getPositionX() + 2, chestSprite->getPositionY() - 3));
                                                    chestShadowSprite->setScale(0.25);
                                                }
                                                auto rewardLabel = infoNode->getChildByIDRecursive("reward-label");
                                                if (rewardLabel) {
                                                    rewardLabel->setPosition(ccp(0, -130));
                                                    rewardLabel->setZOrder(3);
                                                }
                                                auto rewardShadowLabel = infoNode->getChildByIDRecursive("reward-shadow-label");
                                                if (rewardShadowLabel) {
                                                    rewardShadowLabel->setPosition(ccp(rewardLabel->getPositionX() + 2, rewardLabel->getPositionY() - 3));
                                                }
                                                auto progressLabel = infoNode->getChildByIDRecursive("gauntlet-progress-label");
                                                if (progressLabel) {
                                                    progressLabel->setPosition(ccp(0, 55));
                                                } 
                                                auto progressShadowLabel = infoNode->getChildByIDRecursive("gauntlet-progress-shadow-label");
                                                if (progressShadowLabel) {
                                                    progressShadowLabel->setPosition(ccp(progressLabel->getPositionX() + 2, progressLabel->getPositionY() - 3));
                                                }
                                            auto checkmarkSprite = gauntletNode->getChildByIDRecursive("checkmark-sprite");
                                            if (checkmarkSprite) {
                                                checkmarkSprite->setPosition(ccp(0, -120));
                                            }
                                            auto checkmarkShadowSprite = gauntletNode->getChildByIDRecursive("checkmark-shadow-sprite");
                                            if (checkmarkShadowSprite) {
                                                checkmarkShadowSprite->setPosition(ccp(checkmarkSprite->getPositionX() + 2, checkmarkSprite->getPositionY() - 3));
                                            }
                                            auto shadowSprite = gauntletNode->getChildByIDRecursive("gauntlet-shadow-sprite");
                                            shadowSprite->setVisible(false);
                                        }
                                    }
                                }
                            }
                        }
                        std::vector<CCSprite*> gauntletButtons;
                        for (int b = 0; b < 3; b++) {
                            
                            auto gauntletButton = static_cast<CCSprite*>(gauntletMenu->getChildByIDRecursive(fmt::format("gauntlet-button-{}", b + 1)));
                            if (gauntletButton) {
                                gauntletButtons.push_back(gauntletButton);
                            }
                        }
                        int buttonCount = gauntletButtons.size();
                        float startX = winSize.width / 2 - (buttonCount - 1) * 57.5;
                        float posY = winSize.height / 2 - 17.5;
                        for (int i = 0; i < buttonCount; i++) {
                            gauntletButtons[i]->setPosition(ccp(startX + i * 115, posY));

                            auto bgPortal = Mod::get()->getSettingValue<bool>("update-backgrounds");
                            if (bgPortal) {
                            
                                auto gauntletNodeParent = gauntletButtons[i]->getChildByIDRecursive("gauntlet-node-parent");
                                if (gauntletNodeParent) {
                                    
                                    auto gauntletNode = static_cast<CCSprite*>(gauntletNodeParent->getChildByIDRecursive("gauntlet-node"));
                                    if (gauntletNode) {

                                        auto backgroundNode = static_cast<CCSprite*>(gauntletNode->getChildByIDRecursive("background"));
                                        ccColor3B backgroundColor = backgroundNode ? backgroundNode->getColor() : ccc3(255, 255, 255); // white bg by default

                                        auto portalParentNode = CCNode::create();
                                        if (portalParentNode) {
                                            portalParentNode->setID("gauntlet-portal-parent-node");
                                            portalParentNode->setPosition(ccp(gauntletNode->getContentSize().width / 2 - 3, gauntletNode->getContentSize().height / 2));
                                            gauntletNode->addChild(portalParentNode);

                                            auto portalBase = CCSprite::create("gauntletPortal_001.png"_spr);
                                                portalBase->setID(fmt::format("portal-base", i + 1));
                                                portalBase->setColor(backgroundColor);
                                                portalBase->setPosition(ccp(1, 0));
                                                portalBase->setZOrder(-1);
                                                portalParentNode->addChild(portalBase);
                                            
                                            auto portalOut = CCSprite::create("gauntletPortal_002.png"_spr);
                                                portalOut->setID("portal-outline");
                                                portalOut->setPosition(ccp(3, -1.75));
                                                portalOut->setZOrder(-2);
                                                portalParentNode->addChild(portalOut);

                                            auto portalFill = CCSprite::create("gauntletPortal_003.png"_spr);
                                                portalFill->setID("portal-fill");
                                                portalFill->setPosition(ccp(portalOut->getPositionX() - 0.5, 1.50));
                                                portalFill->setZOrder(-2);
                                                portalParentNode->addChild(portalFill);

                                            auto portalShine = CCSprite::create("gauntletPortal_004.png"_spr);
                                                portalShine->setID("portal-shine");
                                                portalShine->setPosition(ccp(1, 0));
                                                portalShine->setZOrder(-1);
                                                portalParentNode->addChild(portalShine);

                                            auto portalBG = CCSprite::create("gauntletPortal_005.png"_spr);
                                                portalBG->setID("portal-background");
                                                portalBG->setPosition(ccp(0, 0));
                                                portalBG->setScale(1.25);
                                                portalBG->setZOrder(-3);

                                                auto portalBGColor = static_cast<CCSprite*>(gauntletNode->getChildByIDRecursive("background"));
                                                if (portalBGColor) {
                                                    ccColor3B bgColor = portalBGColor->getColor();
                                                    portalBG->setColor(bgColor);
                                                } else {
                                                    portalBG->setColor(ccc3(128, 128, 128));
                                                }
                                                portalParentNode->addChild(portalBG);

                                            auto portalBGGlow = CCSprite::create("gauntletPortal_006.png"_spr);
                                                portalBGGlow->setID("portal-background-glow");
                                                portalBGGlow->setPosition(ccp(2, 1));
                                                portalBGGlow->setZOrder(-2);
                                                portalBGGlow->setOpacity(150);
                                                portalParentNode->addChild(portalBGGlow);
                                            
                                            auto portalPlaque = CCSprite::create("gauntletPlaque_001.png"_spr);
                                                portalPlaque->setID(fmt::format("portal-plaque", i + 1));
                                                portalPlaque->setPosition(ccp(3, -95));
                                                portalPlaque->setZOrder(1);

                                                auto portalPlaqueColor = static_cast<CCSprite*>(gauntletNode->getChildByIDRecursive("background"));
                                                if (portalPlaqueColor) {
                                                    ccColor3B plaqueColor = portalPlaqueColor->getColor();
                                                    portalPlaque->setColor(plaqueColor);
                                                } else {
                                                    portalPlaque->setColor(ccc3(255, 255, 255));
                                                }
                                                portalParentNode->addChild(portalPlaque);

                                            auto portalPlaqueOut = CCSprite::create("gauntletPlaque_002.png"_spr);
                                                portalPlaqueOut->setID("portal-plaque-outline");
                                                portalPlaqueOut->setPosition(ccp(portalPlaque->getPositionX() + 1.5, portalPlaque->getPositionY() - 1));
                                                portalPlaqueOut->setZOrder(-1);
                                                portalParentNode->addChild(portalPlaqueOut);
                                            
                                            auto portalNamePlaque = CCSprite::create("gauntletPlaque_003.png"_spr);
                                                portalNamePlaque->setID(fmt::format("portal-name-plaque", i + 1));
                                                portalNamePlaque->setPosition(ccp(3, 84));
                                                portalNamePlaque->setZOrder(1);
                                                portalNamePlaque->setScale(0.65);

                                                auto portalNamePlaqueColor = static_cast<CCSprite*>(gauntletNode->getChildByIDRecursive("background"));
                                                if (portalNamePlaqueColor) {
                                                    ccColor3B plaqueColor = portalNamePlaqueColor->getColor();
                                                    portalNamePlaque->setColor(plaqueColor);
                                                } else {

                                                    portalNamePlaque->setColor(ccc3(255, 255, 255));
                                                }
                                                portalParentNode->addChild(portalNamePlaque);

                                            auto portalNamePlaqueOut = CCSprite::create("gauntletPlaque_004.png"_spr);
                                                portalNamePlaqueOut->setID("portal-name-plaque-outline");
                                                portalNamePlaqueOut->setPosition(ccp(portalNamePlaque->getPositionX() + 0.75, portalNamePlaque->getPositionY() - 0.75));
                                                portalNamePlaqueOut->setZOrder(-1);
                                                portalNamePlaqueOut->setScale(portalNamePlaque->getScale());
                                                portalParentNode->addChild(portalNamePlaqueOut);
                                        }
                                        backgroundNode->setVisible(false);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    const char* titleA = "The Lost";
    const char* titleB = "Gauntlets";

        // Small title children
        auto GRTitleSML = CCLabelBMFont::create(titleA, "GR_OxygeneFont.fnt"_spr);
        GRTitleSML->setID("title-small-base");
        GRTitleSML->setScale(0.50);
        GRTitleSML->setPosition(ccp(winSize.width / 2, winSize.height - 17.5));
        GRTitleSML->setColor(ccc3(255, 255, 105));

        auto GRTitleOutlineSML = CCLabelBMFont::create(titleA, "GR_OxygeneFontOutline.fnt"_spr);
        GRTitleOutlineSML->setID("title-small-outline");
        GRTitleOutlineSML->setScale(0.50);
        GRTitleOutlineSML->setPosition(ccp(winSize.width / 2 - 1, winSize.height - 17.5));
        GRTitleOutlineSML->setColor(ccc3(255, 255, 255));

        auto GRTitleHighlightSML = CCLabelBMFont::create(titleA, "GR_OxygeneFontHighlight.fnt"_spr);
        GRTitleHighlightSML->setID("title-small-highlight");
        GRTitleHighlightSML->setScale(0.50);
        GRTitleHighlightSML->setPosition(ccp(winSize.width / 2 + 1.25, winSize.height - 17.5));
        GRTitleHighlightSML->setColor(ccc3(255, 118, 0));

        auto GRTitleShadowSML = CCLabelBMFont::create(titleA, "GR_OxygeneFontOutline.fnt"_spr);
        GRTitleShadowSML->setID("title-small-shadow");
        GRTitleShadowSML->setScale(0.50);
        GRTitleShadowSML->setPosition(ccp(winSize.width / 2 + 0.75, winSize.height - 19));
        GRTitleShadowSML->setColor(ccc3(0, 0, 0));
        GRTitleShadowSML->setOpacity(100);

        this->addChild(GRTitleShadowSML);
        this->addChild(GRTitleOutlineSML);
        this->addChild(GRTitleSML);
        this->addChild(GRTitleHighlightSML);

        // Large title children
		auto GRTitleLRG = CCLabelBMFont::create(titleB, "GR_OxygeneFont.fnt"_spr);
        GRTitleLRG->setID("title-large-base");
        GRTitleLRG->setScale(0.90);
        GRTitleLRG->setPosition(ccp(winSize.width / 2, winSize.height - 45));
        GRTitleLRG->setColor(ccc3(255, 255, 105));

        auto GRTitleOutlineLRG = CCLabelBMFont::create(titleB, "GR_OxygeneFontOutline.fnt"_spr);
        GRTitleOutlineLRG->setID("title-large-outline");
        GRTitleOutlineLRG->setScale(0.90);
        GRTitleOutlineLRG->setPosition(ccp(winSize.width / 2 - 1.65, winSize.height - 45));
        GRTitleOutlineLRG->setColor(ccc3(255, 255, 255));

        auto GRTitleHighlightLRG = CCLabelBMFont::create(titleB, "GR_OxygeneFontHighlight.fnt"_spr);
        GRTitleHighlightLRG->setID("title-large-highlight");
        GRTitleHighlightLRG->setScale(0.90);
        GRTitleHighlightLRG->setPosition(ccp(winSize.width / 2 + 2.75, winSize.height - 45));
        GRTitleHighlightLRG->setColor(ccc3(255, 118, 0));
        
        auto GRTitleShadowLRG = CCLabelBMFont::create(titleB, "GR_OxygeneFontOutline.fnt"_spr);
        GRTitleShadowLRG->setID("title-large-shadow");
        GRTitleShadowLRG->setScale(0.90);
        GRTitleShadowLRG->setPosition(ccp(winSize.width / 2 + 1.65, winSize.height - 48));
        GRTitleShadowLRG->setColor(ccc3(0, 0, 0));
        GRTitleShadowLRG->setOpacity(100);

        this->addChild(GRTitleShadowLRG);
        this->addChild(GRTitleOutlineLRG);
        this->addChild(GRTitleLRG);
        this->addChild(GRTitleHighlightLRG);
    }

    void onDot(CCObject* sender) {
        auto btnIdx = std::find(m_fields->m_dots.begin(), m_fields->m_dots.end(), sender) - m_fields->m_dots.begin();

        m_scrollLayer->instantMoveToPage(btnIdx);
        m_scrollLayer->updatePages();
        m_scrollLayer->repositionPagesLooped();
    }

    void scrollLayerScrolledToPage(BoomScrollLayer* p0, int p1) {
        GauntletSelectLayer::scrollLayerScrolledToPage(p0, p1);
        updateDots();
    }

    #ifdef GEODE_IS_WINDOWS
    void defineKeybind(const char* id, std::function<void()> callback) {
        this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
            if (event->isDown()) {
                callback();
            }
            return ListenerResult::Propagate;
        }, id);
    }
    #endif

    void findCurrentGauntletPageUsing(CCArray* pageButtons) {
        int i = 0;
        for (CCSprite* ccSprite : CCArrayExt<CCSprite*>(pageButtons)) {
            if (ccSprite->getDisplayedColor() == ccColor3B({255, 255, 255})) {
                m_fields->currentGauntletPage = (i + 1);
                break;
            }
            i++;
        }
    }

    void pressGauntlet(int desiredGauntlet) {
        if (const auto theGauntletPage = getChildByIDRecursive(fmt::format("gauntlet-page-{}", m_fields->currentGauntletPage))) {
            if (const auto theGauntlet = theGauntletPage->getChildByIDRecursive(fmt::format("gauntlet-button-{}", desiredGauntlet))) {
                GauntletSelectLayer::onPlay(theGauntlet);
            }
        }
    }

    void scrollLayerWillScrollToPage(BoomScrollLayer* p0, int p1) {
        GauntletSelectLayer::scrollLayerWillScrollToPage(p0, p1);
        if (const auto pageButtons = m_scrollLayer->m_dots) {
            RedesignedGauntletSelectLayer::findCurrentGauntletPageUsing(pageButtons);
        }
    }

    void onBack(cocos2d::CCObject* sender){
        m_fields->currentGauntletPage = 0;
        GauntletSelectLayer::onBack(sender);
    }
};

#ifdef GEODE_IS_WINDOWS
$execute {
    BindManager::get()->registerBindable({
        "previous-gauntlet"_spr,
        "Previous Gauntlet Page",
        "Use this keybind (set to Left by default) to view the previous gauntlet page.",
        { Keybind::create(KEY_Left) },
        "Global/Better Gauntlets"
    });
    BindManager::get()->registerBindable({
        "next-gauntlet"_spr,
        "Next Gauntlet Page",
        "Use this keybind (set to Right by default) to view the next gauntlet page.",
        { Keybind::create(KEY_Right) },
        "Global/Better Gauntlets"
    });
    BindManager::get()->registerBindable({
        "first-visible-gauntlet"_spr,
        "First Gauntlet",
        "Enters the <cg>first</c> gauntlet on the current Gauntlet Page.\n\n<cy>(Disclaimer: Results may not be accurate.)</c>",
        { Keybind::create(KEY_One) },
        "Global/Better Gauntlets"
    });
    BindManager::get()->registerBindable({
        "second-visible-gauntlet"_spr,
        "Second Gauntlet",
        "Enters the <cg>second</c> gauntlet on the current Gauntlet Page.\n\n<cy>(Disclaimer: Results may not be accurate.)</c>",
        { Keybind::create(KEY_Two) },
        "Global/Better Gauntlets"
    });
    BindManager::get()->registerBindable({
        "third-visible-gauntlet"_spr,
        "Third Gauntlet",
        "Enters the <cg>third</c> gauntlet on the current Gauntlet Page.\n\n<cy>(Disclaimer: Results may not be accurate.)</c>",
        { Keybind::create(KEY_Three) },
        "Global/Better Gauntlets"
    });
}
#endif