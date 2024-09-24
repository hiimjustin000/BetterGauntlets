#ifndef GEODE_IS_MACOS
#include <Geode/modify/GauntletSelectLayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>

using namespace geode::prelude;
using namespace keybinds;

class $modify(RedesignedGauntletSelectLayer, GauntletSelectLayer) {
    struct Fields {
        int currentGauntletPage = 0;
    };

void defineKeybind(const char* id, std::function<void()> callback) {
    this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
        if (event->isDown()) {
            callback();
        }
    return ListenerResult::Propagate;
    }, id);
}

void findCurrentGauntletPageUsing(CCNode* pageButtons) {

auto pageButtonsChildren = CCArrayExt<CCNode*>(pageButtons->getChildren());
    for (int i = 0; i < pageButtonsChildren.size(); i++) {
        if (const auto ccSprite = typeinfo_cast<CCSprite*>(pageButtonsChildren[i])) {
            if (ccSprite->getDisplayedColor() == ccColor3B({255, 255, 255})) {
                m_fields->currentGauntletPage = (i + 1);
                }
            }
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
    if (const auto pageButtons = getChildByIDRecursive("page-buttons")) {
        RedesignedGauntletSelectLayer::findCurrentGauntletPageUsing(pageButtons);
        }
    }

void onBack(cocos2d::CCObject* sender){
m_fields->currentGauntletPage = 0;
GauntletSelectLayer::onBack(sender);
}

void setupGauntlets() {
    GauntletSelectLayer::setupGauntlets();
    if (const auto pageButtons = getChildByIDRecursive("page-buttons")) {
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
};
#endif

#ifndef GEODE_IS_MACOS
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