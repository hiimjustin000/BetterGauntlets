#include <Geode/modify/GauntletSelectLayer.hpp>
#include <algorithm>

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

            if(btnIdx == newPage)
                static_cast<CCSprite*>(btn->getNormalImage())->setDisplayFrame(sfc->spriteFrameByName("gj_navDotBtn_on_001.png"));
            else
                static_cast<CCSprite*>(btn->getNormalImage())->setDisplayFrame(sfc->spriteFrameByName("gj_navDotBtn_off_001.png"));
        }
    }

    void setupGauntlets() {
        GauntletSelectLayer::setupGauntlets();

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

        // ery
        if (const auto pageButtons = m_scrollLayer->m_dots) {
            RedesignedGauntletSelectLayer::findCurrentGauntletPageUsing(pageButtons);
        }
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

    void defineKeybind(const char* id, std::function<void()> callback) {
        this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
            if (event->isDown()) {
                callback();
            }
            return ListenerResult::Propagate;
        }, id);
    }

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
        "Previous Gauntlet",
        "Use this keybind (set to Left by default) to view the previous gauntlet page.",
        { Keybind::create(KEY_Left) },
        "Global/Gauntlet Touchup"
    });
    BindManager::get()->registerBindable({
        "next-gauntlet"_spr,
        "Next Gauntlet",
        "Use this keybind (set to Right by default) to view the next gauntlet page.",
        { Keybind::create(KEY_Right) },
        "Global/Gauntlet Touchup"
    });
    BindManager::get()->registerBindable({
        "first-visible-gauntlet"_spr,
        "First Gauntlet",
        "Use this keybind (set to 1 by default) to enter the first visible gauntlet.\n\n<cy>(Disclaimer: Results may not be accurate.)</c>",
        { Keybind::create(KEY_One) },
        "Global/Gauntlet Touchup"
    });
    BindManager::get()->registerBindable({
        "second-visible-gauntlet"_spr,
        "Second Gauntlet",
        "Use this keybind (set to 2 by default) to enter the second visible gauntlet.\n\n<cy>(Disclaimer: Results may not be accurate.)</c>",
        { Keybind::create(KEY_Two) },
        "Global/Gauntlet Touchup"
    });
    BindManager::get()->registerBindable({
        "third-visible-gauntlet"_spr,
        "Third Gauntlet",
        "Use this keybind (set to 3 by default) to enter the third visible gauntlet.\n\n<cy>(Disclaimer: Results may not be accurate.)</c>",
        { Keybind::create(KEY_Three) },
        "Global/Gauntlet Touchup"
    });
}
#endif