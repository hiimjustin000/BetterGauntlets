#include <Geode/Geode.hpp>
#include <Geode/modify/GauntletSelectLayer.hpp>

using namespace geode::prelude;

#ifdef GEODE_IS_WINDOWS
#include <geode.custom-keybinds/include/Keybinds.hpp>

using namespace keybinds;
#endif

class $modify(GauntletSelectLayerHook, GauntletSelectLayer) {
    bool init(int gauntletType) {
        if (!GauntletSelectLayer::init(gauntletType)) return false;

        auto title = this->getChildByID("title");
        if (title) {
            title->setVisible(false);
        }

        auto BLCorner = this->getChildByID("bottom-left-corner");
        if (BLCorner) {
            BLCorner->setVisible(false);
        }

        auto BRCorner = this->getChildByID("bottom-right-corner");
        if (BRCorner) {
            BRCorner->setVisible(false);
        }
        return true;
    }

    void onEnter() {
        GauntletSelectLayer::onEnter();

        auto title = this->getChildByID("title");
        if (title) {
            title->setVisible(false);
        }
        
        auto BLCorner = this->getChildByID("bottom-left-corner");
        if (BLCorner) {
            BLCorner->setVisible(false);
        }

        auto BRCorner = this->getChildByID("bottom-right-corner");
        if (BRCorner) {
            BRCorner->setVisible(false);
        }
    }
};

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

        auto floor = CCSprite::create("gauntletGround_001.png"_spr);
        if (floor) {
            floor->setID("floor");
            floor->setColor(ccc3(37, 37, 37));

            auto floorSize = floor->getContentSize();

            float scaleX = winSize.width / floorSize.width;
            float scaleY = winSize.height / floorSize.height;

            float scale = std::min(scaleX, scaleY);

            floor->setScale(scale);

            floor->setPosition(ccp(winSize.width / 2, floorSize.height * scale / 2));
            floor->setAnchorPoint(ccp(0.5, 0.5));

            floor->setZOrder(-1);
            this->addChild(floor);
        }

        auto navMenu = getChildByID("dasshu.better-gauntlets/page-navigation");
        navMenu->setScale(0.9f);

        auto decorationParentNode = CCNode::create();
        if (decorationParentNode) {
            decorationParentNode->setID("background-decoration-node");
            decorationParentNode->setPosition(0, 0);
            decorationParentNode->setZOrder(-1);
            this->addChild(decorationParentNode);
        
            auto chainParentNode = CCNode::create();
            if (chainParentNode) {
                chainParentNode->setID("chain-parent-node");
                chainParentNode->setPosition(0, 0);
                chainParentNode->setZOrder(-1);
                decorationParentNode->addChild(chainParentNode);

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
                chain1->setPosition(ccp(director->getScreenLeft() + 50.f, director->getScreenTop() - 0));

                auto chain2 = getChildByIDRecursive("chain-2");
                chain2->setScale(2.0);
                chain2->setPosition(ccp(director->getScreenLeft() + 50.f, director->getScreenTop() - 30));

                auto chain3 = getChildByIDRecursive("chain-3");
                chain3->setScale(2.0);
                chain3->setPosition(ccp(director->getScreenLeft() + 50.f, director->getScreenTop() - 60));

                auto chain4 = getChildByIDRecursive("chain-4");
                chain4->setScale(2.0);
                chain4->setPosition(ccp(director->getScreenLeft() + 50.f, director->getScreenTop() - 90));

                auto chain5 = getChildByIDRecursive("chain-5");
                chain5->setScale(2.0);
                chain5->setPosition(ccp(director->getScreenLeft() + 50.f, director->getScreenTop() - 120));

                // second chain pair //
                auto chain6 = getChildByIDRecursive("chain-6");
                chain6->setScale(1.0);
                chain6->setPosition(ccp(director->getScreenRight() - 60.f, director->getScreenTop() - 0));

                auto chain7 = getChildByIDRecursive("chain-7");
                chain7->setScale(1.0);
                chain7->setPosition(ccp(director->getScreenRight() - 60.f, director->getScreenTop() - 15));

                auto chain8 = getChildByIDRecursive("chain-8");
                chain8->setScale(1.0);
                chain8->setPosition(ccp(director->getScreenRight() - 60.f, director->getScreenTop() - 30));

                auto chain9 = getChildByIDRecursive("chain-9");
                chain9->setScale(1.0);
                chain9->setPosition(ccp(director->getScreenRight() - 60.f, director->getScreenTop() - 45));

                auto chain10 = getChildByIDRecursive("chain-10");
                chain10->setScale(1.0);
                chain10->setPosition(ccp(director->getScreenRight() - 60.f, director->getScreenTop() - 60));

                // third chain pair //
                auto chain11 = getChildByIDRecursive("chain-11");
                chain11->setScale(1.65);
                chain11->setPosition(ccp(director->getScreenRight() - 40.f, director->getScreenTop() - 0));

                auto chain12 = getChildByIDRecursive("chain-12");
                chain12->setScale(1.65);
                chain12->setPosition(ccp(director->getScreenRight() - 40.f, director->getScreenTop() - 25));

                auto chain13 = getChildByIDRecursive("chain-13");
                chain13->setScale(1.65);
                chain13->setPosition(ccp(director->getScreenRight() - 40.f, director->getScreenTop() - 50));

                auto chain14 = getChildByIDRecursive("chain-14");
                chain14->setScale(1.65);
                chain14->setPosition(ccp(director->getScreenRight() - 40.f, director->getScreenTop() - 75));

                auto chain15 = getChildByIDRecursive("chain-15");
                chain15->setScale(1.65);
                chain15->setPosition(ccp(director->getScreenRight() - 40.f, director->getScreenTop() - 100));
            }
        }

        auto torchParentNode = CCNode::create();
        if (torchParentNode) {
            torchParentNode->setID("torch-parent-node");
            torchParentNode->setPosition(0, 0);
            torchParentNode->setZOrder(-1);
            decorationParentNode->addChild(torchParentNode);

            auto lightL = CCSprite::create("torchShine_001.png"_spr);
            if (lightL) {
                
                auto lightScaleUp = CCEaseInOut::create(CCScaleTo::create(1.5f, 2.0f), 2.0f);
                auto lightScaleDown = CCEaseInOut::create(CCScaleTo::create(1.5f, 1.15f), 2.0f);
                auto lightScaleSequence = CCSequence::create(lightScaleUp, lightScaleDown, nullptr);
                
                auto lightFadeFrom = CCFadeTo::create(3.0f, 112);
                auto lightFadeTo = CCFadeTo::create(3.0f, 156);
                auto lightFadeSequence = CCSequence::create(lightFadeFrom, lightFadeTo, nullptr);

                auto scaleLoop = CCRepeatForever::create(lightScaleSequence);
                auto fadeLoop = CCRepeatForever::create(lightFadeSequence);
                
                lightL->setScale(1.15f);
                lightL->setPosition(ccp(director->getScreenLeft() + 75.f, winSize.height / 2));
                lightL->setZOrder(3);
                lightL->setOpacity(156);
                lightL->setColor(ccc3(255, 196, 0));
                lightL->runAction(scaleLoop);
                lightL->runAction(fadeLoop);
                torchParentNode->addChild(lightL);
            }

            auto lightR = CCSprite::create("torchShine_001.png"_spr);
            if (lightR) {
                
                auto lightScaleUp = CCEaseInOut::create(CCScaleTo::create(1.5f, 2.0f), 2.0f);
                auto lightScaleDown = CCEaseInOut::create(CCScaleTo::create(1.5f, 1.15f), 2.0f);
                auto lightScaleSequence = CCSequence::create(lightScaleUp, lightScaleDown, nullptr);
                
                auto lightFadeFrom = CCFadeTo::create(3.0f, 112);
                auto lightFadeTo = CCFadeTo::create(3.0f, 156);
                auto lightFadeSequence = CCSequence::create(lightFadeFrom, lightFadeTo, nullptr);

                auto scaleLoop = CCRepeatForever::create(lightScaleSequence);
                auto fadeLoop = CCRepeatForever::create(lightFadeSequence);
                
                lightR->setScale(1.15f);
                lightR->setPosition(ccp(director->getScreenRight() - 75.f, winSize.height / 2));
                lightR->setZOrder(3);
                lightR->setOpacity(156);
                lightR->setColor(ccc3(255, 196, 0));
                lightR->runAction(scaleLoop);
                lightR->runAction(fadeLoop);
                torchParentNode->addChild(lightR);
            }

            auto torchParticleA1 = CCParticleSystemQuad::create();
            if (torchParticleA1) {
                CCParticleSystemQuad* torchParticleLA = GameToolbox::particleFromString("30a-1a2a0.55a6a90a90a0a0a0a0a0a28a2a0a0a6a75a0a0a40a1a0a0.5a0a0a0a1a0a0a0a0a25a1a0a0.5a0a0a0a1a0a0.15a0a0.25a0a0a0a0a0a0a0a0a2a1a0a0a0a28a0a0a0a0a0a0a0a0a0a0a0a0a0a0", NULL, false);
                torchParticleLA->setPosition(director->getScreenLeft() + 75.f, winSize.height / 2);
                torchParticleLA->setZOrder(1);
                torchParticleLA->setScale(0.85f);
                torchParentNode->addChild(torchParticleLA);
            }
        
            auto torchParticleA2 = CCParticleSystemQuad::create();
            if (torchParticleA2) {
                CCParticleSystemQuad* torchParticleLB = GameToolbox::particleFromString("30a-1a2a0.55a6a90a90a0a0a0a0a0a43a2a0a0a10a10a0a0a40a0.25a0a0.25a0a0.25a0a1a0a30a10a0a25a0a0a0a0a0a0a0a0a0.15a0a0.25a0a0a0a0a0a0a0a0a2a0a0a0a0a182a0a1.4a0a0a0a0a0a0a0a0a0a0a0a0", NULL, false);
                torchParticleLB->setPosition(director->getScreenLeft() + 75.f, winSize.height / 2);
                torchParticleLB->setZOrder(0);
                torchParticleLB->setScale(1.75f);
                torchParentNode->addChild(torchParticleLB);
                }
            
            auto torchHandleL = CCSprite::create("wallTorch_001.png"_spr);
            if (torchHandleL) {
                torchHandleL->setPosition(ccp(director->getScreenLeft() + 75.f, winSize.height / 2 - 20));
                torchHandleL->setZOrder(2);
                torchHandleL->setScale(0.75);
                torchHandleL->setColor(ccc3(35, 35, 35));
                torchParentNode->addChild(torchHandleL);
            }

            auto torchParticleB1 = CCParticleSystemQuad::create();
            if (torchParticleB1) {
                CCParticleSystemQuad* torchParticleRA = GameToolbox::particleFromString("30a-1a2a0.55a6a90a90a0a0a0a0a0a28a2a0a0a6a75a0a0a40a1a0a0.5a0a0a0a1a0a0a0a0a25a1a0a0.5a0a0a0a1a0a0.15a0a0.25a0a0a0a0a0a0a0a0a2a1a0a0a0a28a0a0a0a0a0a0a0a0a0a0a0a0a0a0", NULL, false);
                torchParticleRA->setPosition(director->getScreenRight() - 75.f, winSize.height / 2);
                torchParticleRA->setZOrder(1);
                torchParticleRA->setScale(0.85f);
                torchParentNode->addChild(torchParticleRA);
            }
        
            auto torchParticleB2 = CCParticleSystemQuad::create();
            if (torchParticleB2) {
                CCParticleSystemQuad* torchParticleRB = GameToolbox::particleFromString("30a-1a2a0.55a6a90a90a0a0a0a0a0a43a2a0a0a10a10a0a0a40a0.25a0a0.25a0a0.25a0a1a0a30a10a0a25a0a0a0a0a0a0a0a0a0.15a0a0.25a0a0a0a0a0a0a0a0a2a0a0a0a0a182a0a1.4a0a0a0a0a0a0a0a0a0a0a0a0", NULL, false);
                torchParticleRB->setPosition(director->getScreenRight() - 75.f, winSize.height / 2);
                torchParticleRB->setZOrder(0);
                torchParticleRB->setScale(1.75f);
                torchParentNode->addChild(torchParticleRB);
                }
            
            auto torchHandleR = CCSprite::create("wallTorch_001.png"_spr);
            if (torchHandleR) {
                torchHandleR->setPosition(ccp(director->getScreenRight() - 75.f, winSize.height / 2 - 20));
                torchHandleR->setZOrder(2);
                torchHandleR->setScale(0.75);
                torchHandleR->setColor(ccc3(94, 94, 94));
                torchParentNode->addChild(torchHandleR);
            }
        }

        auto dust = CCParticleSystemQuad::create();
        if (dust) {
            CCParticleSystemQuad* dustParticles = GameToolbox::particleFromString("30a-1a1.85a1.5a3a90a90a0a0a250a0a0a-300a0a0a0a0a15a5a0a40a0a0a0a0a0a0a0.26a0.05a0a0a0a25a0a0a0a0a0a0a0.1a0.05a0.25a0a0.25a0a0a0a0a0a0a0a0a2a0a0a0a0a183a0a1.8a0a0a0a0a0a0a0a0a0a0a0a0", NULL, false);
            dustParticles->setPosition(winSize.width / 2, director->getScreenTop() + 10);
            dustParticles->setZOrder(-2);
            this->addChild(dustParticles);
        }   

        for (int p = 0; p < m_scrollLayer->getTotalPages(); p++) {

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

                                            auto particleParentNode = CCNode::create();
                                            if (particleParentNode) {
                                                particleParentNode->setID("particle-parent-node");
                                                particleParentNode->setZOrder(5);
                                                gauntletNode->addChild(particleParentNode);

                                                for (int p = 0; p < 1; p++) {
                                                    auto portalParticle1 = CCParticleSystemQuad::create();
                                                    if (portalParticle1) {
                                                        CCParticleSystemQuad* particle1 = GameToolbox::particleFromString("50a-1a2a0.35a7a0a180a0a0a20a40a0a0a-19a0a0a0a2a1a0a40a1a0a1a0a1a0a0.7a0.3a0a0a0a25a1a0a1a0a1a0a0.4a0.05a0.6a0a1a0a50a0a0a10a-30a15a1a2a1a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0", NULL, false);
                                                        particle1->setPosition(ccp(0, 0));
                                                        particle1->setZOrder(2);
                                                        particle1->setScale(1.7f);
                                                        particleParentNode->addChild(particle1);
                                                    }
                                                
                                                    auto portalParticle2 = CCParticleSystemQuad::create();
                                                    if (portalParticle2) {
                                                        CCParticleSystemQuad* particle2 = GameToolbox::particleFromString("20a-1a2a1a6a180a0a0a0a25a50a0a5a-8a0a0a10a0a0a0a360a1a0a1a0a1a0a0.08a0.04a100a30a0a180a1a0a1a0a1a0a0.02a0a0.6a0a1a0a0a0a0a0a0a0a1a2a1a0a0a0a190a0a0a0a0a0a0a0a0a0a0a0a0a0a0", NULL, false);
                                                        particle2->setPosition(ccp(0, 0));
                                                        particle2->setZOrder(2);
                                                        particle2->setScaleX(1.25f);
                                                        particle2->setScaleY(2.5f);
                                                        particleParentNode->addChild(particle2);
                                                    }

                                                    auto portalParticle3 = CCParticleSystemQuad::create();
                                                    if (portalParticle3) {
                                                        CCParticleSystemQuad* particle3 = GameToolbox::particleFromString("20a-1a2a0a2a180a0a0a0a25a50a0a5a-8a0a0a10a0a0a0a171a1a0a1a0a1a0a0.1a0.05a85a10a0a97a1a0a1a0a1a0a0.02a0a0a0a0.35a0a0a0a0a0a0a0a1a2a1a0a0a0a179a0a0a0a0a0a0a0a0a0a0a0a0a0a0", NULL, false);
                                                        particle3->setPosition(ccp(0, 0));
                                                        particle3->setZOrder(2);
                                                        particle3->setScaleX(1.25f);
                                                        particle3->setScaleY(2.5f);
                                                        particleParentNode->addChild(particle3);
                                                    }
                                                }
                                            }

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
                                        ccColor3B backgroundColor = backgroundNode ? backgroundNode->getColor() : ccc3(128, 128, 128); // grey bg by default

                                        auto portalParentNode = CCNode::create();
                                        if (portalParentNode) {
                                            portalParentNode->setID("gauntlet-portal-parent-node");
                                            portalParentNode->setPosition(ccp(gauntletNode->getContentSize().width / 2 - 3, gauntletNode->getContentSize().height / 2));
                                            gauntletNode->addChild(portalParentNode);

                                            auto portalBase = CCSprite::create("gauntletPortal_001_01.png"_spr);
                                            portalBase->setID(fmt::format("portal-base", i + 1));
                                            portalBase->setColor(backgroundColor);
                                            portalBase->setPosition(ccp(1, 0));
                                            portalBase->setZOrder(0);
                                            portalParentNode->addChild(portalBase);
                                            
                                            auto portalOut = CCSprite::create("gauntletPortal_002.png"_spr);
                                            portalOut->setID("portal-outline");
                                            portalOut->setPosition(ccp(3, -1.75));
                                            portalOut->setZOrder(-3);

                                            auto portalOutColor = static_cast<CCSprite*>(gauntletNode->getChildByIDRecursive("background"));
                                                if (portalOutColor) {
                                                    ccColor3B bgColor = portalOutColor->getColor();
                                                    portalOut->setColor(bgColor);
                                                } else {
                                                    portalOut->setColor(ccc3(128, 128, 128));
                                                }
                                                portalParentNode->addChild(portalOut);

                                            auto portalFill = CCSprite::create("gauntletPortal_003.png"_spr);
                                            portalFill->setID("portal-fill");
                                            portalFill->setPosition(ccp(2.5, 1.50));
                                            portalFill->setZOrder(-1);
                                            ccBlendFunc portalFillBlend = { GL_SRC_ALPHA, GL_ONE };
                                            portalFill->setBlendFunc(portalFillBlend);
                                            portalParentNode->addChild(portalFill);

                                            auto portalColor = CCSprite::create("gauntletPortal_004_02.png"_spr);
                                            portalColor->setID("portal-color");
                                            portalColor->setPosition(ccp(1.25, 0.3));
                                            portalColor->setZOrder(-1);

                                                auto portalBaseColor = static_cast<CCSprite*>(gauntletNode->getChildByIDRecursive("background"));
                                                if (portalBaseColor) {
                                                    ccColor3B bgColor = portalBaseColor->getColor();
                                                    portalColor->setColor(bgColor);
                                                } else {
                                                    portalColor->setColor(ccc3(128, 128, 128));
                                                }
                                                portalParentNode->addChild(portalColor);

                                            auto portalBG = CCSprite::create("gauntletPortal_005.png"_spr);
                                            portalBG->setID("portal-background");
                                            portalBG->setPosition(ccp(0, 0));
                                            portalBG->setScale(1.25);
                                            portalBG->setZOrder(-2);

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
                                            portalBGGlow->setPosition(ccp(2.5, 1));
                                            portalBGGlow->setZOrder(-1);
                                            portalBGGlow->setOpacity(150);
                                            ccBlendFunc portalBGGlowBlend = { GL_SRC_ALPHA, GL_ONE };
                                            portalBGGlow->setBlendFunc(portalBGGlowBlend);
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
                                            portalPlaqueOut->setZOrder(-3);
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

                                            auto portalNamePlaqueOut = CCSprite::create("gauntletPlaque_004_1.png"_spr);
                                            portalNamePlaqueOut->setID("portal-name-plaque-outline");
                                            portalNamePlaqueOut->setPosition(ccp(portalNamePlaque->getPositionX() + 0.75, portalNamePlaque->getPositionY() - 0.75));
                                            portalNamePlaqueOut->setZOrder(-3);
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

        auto titleParentNode = CCNode::create();
        if (titleParentNode) {
            titleParentNode->setID("title-parent-node");
            titleParentNode->setPosition(0, 0);
            titleParentNode->setZOrder(-1);
            this->addChild(titleParentNode);
        }
        // order SHOULD be Shadow -> Outline -> Base -> Detail //
        auto GRTitleShadowSML = CCLabelBMFont::create(titleA, "GR_OxygeneFontOutline.fnt"_spr);
        GRTitleShadowSML->setID("title-small-shadow");
        GRTitleShadowSML->setScale(0.50);
        GRTitleShadowSML->setPosition(ccp(winSize.width / 2 + 0.75, winSize.height - 19));
        GRTitleShadowSML->setColor(ccc3(0, 0, 0));
        GRTitleShadowSML->setOpacity(100);
        titleParentNode->addChild(GRTitleShadowSML);

        auto GRTitleOutlineSML = CCLabelBMFont::create(titleA, "GR_OxygeneFontOutline.fnt"_spr);
        GRTitleOutlineSML->setID("title-small-outline");
        GRTitleOutlineSML->setScale(0.50);
        GRTitleOutlineSML->setPosition(ccp(winSize.width / 2 - 1, winSize.height - 17.5));
        GRTitleOutlineSML->setColor(ccc3(255, 255, 255));
        titleParentNode->addChild(GRTitleOutlineSML);

        auto GRTitleSML = CCLabelBMFont::create(titleA, "GR_OxygeneFont.fnt"_spr);
        GRTitleSML->setID("title-small-base");
        GRTitleSML->setScale(0.50);
        GRTitleSML->setPosition(ccp(winSize.width / 2, winSize.height - 17.5));
        GRTitleSML->setColor(ccc3(255, 255, 105));
        titleParentNode->addChild(GRTitleSML);

        auto GRTitleHighlightSML = CCLabelBMFont::create(titleA, "GR_OxygeneFontHighlight.fnt"_spr);
        GRTitleHighlightSML->setID("title-small-highlight");
        GRTitleHighlightSML->setScale(0.50);
        GRTitleHighlightSML->setPosition(ccp(winSize.width / 2 + 1.25, winSize.height - 17.5));
        GRTitleHighlightSML->setColor(ccc3(255, 123, 0));
        titleParentNode->addChild(GRTitleHighlightSML);

        // Large title children //
        auto GRTitleShadowLRG = CCLabelBMFont::create(titleB, "GR_OxygeneFontOutline.fnt"_spr);
        GRTitleShadowLRG->setID("title-large-shadow");
        GRTitleShadowLRG->setScale(0.90);
        GRTitleShadowLRG->setPosition(ccp(winSize.width / 2 + 1.65, winSize.height - 48));
        GRTitleShadowLRG->setColor(ccc3(0, 0, 0));
        GRTitleShadowLRG->setOpacity(100);
        titleParentNode->addChild(GRTitleShadowLRG);

        auto GRTitleOutlineLRG = CCLabelBMFont::create(titleB, "GR_OxygeneFontOutline.fnt"_spr);
        GRTitleOutlineLRG->setID("title-large-outline");
        GRTitleOutlineLRG->setScale(0.90);
        GRTitleOutlineLRG->setPosition(ccp(winSize.width / 2 - 1.65, winSize.height - 45));
        GRTitleOutlineLRG->setColor(ccc3(255, 255, 255));
        titleParentNode->addChild(GRTitleOutlineLRG);

        auto GRTitleLRG = CCLabelBMFont::create(titleB, "GR_OxygeneFont.fnt"_spr);
        GRTitleLRG->setID("title-large-base");
        GRTitleLRG->setScale(0.90);
        GRTitleLRG->setPosition(ccp(winSize.width / 2, winSize.height - 45));
        GRTitleLRG->setColor(ccc3(255, 255, 105));
        titleParentNode->addChild(GRTitleLRG);

        auto GRTitleHighlightLRG = CCLabelBMFont::create(titleB, "GR_OxygeneFontHighlight.fnt"_spr);
        GRTitleHighlightLRG->setID("title-large-highlight");
        GRTitleHighlightLRG->setScale(0.90);
        GRTitleHighlightLRG->setPosition(ccp(winSize.width / 2 + 2.75, winSize.height - 45));
        GRTitleHighlightLRG->setColor(ccc3(255, 123, 0));
        titleParentNode->addChild(GRTitleHighlightLRG);
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