#include "BlockHubPopup.hpp"
#include <Geode/modify/EditorUI.hpp>
#include <Geode/ui/ScrollLayer.hpp>

BlockHubPopup* BlockHubPopup::create(int categoryID) {
    auto ret = new BlockHubPopup();
    if (ret && ret->init(categoryID)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool BlockHubPopup::init(int categoryID) {
    m_categoryID = categoryID;
    m_showingFavorites = false;
    setupBlockGroups();
    loadFavorites();

    if (!FLAlertLayer::init(nullptr, "Block Hub", "", "Cerrar", nullptr, 450.f, false, 0, 1.f)) return false;

    // Campo de búsqueda
    m_searchInput = CCTextInputNode::create(200.f, 30.f, "Buscar...", "bigFont.fnt");
    m_searchInput->setPosition({0.f, 130.f});
    m_searchInput->setDelegate(this);
    this->addChild(m_searchInput);

    // Botón de favoritos
    auto favBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Favoritos"),
        this,
        menu_selector(BlockHubPopup::onToggleFavorites)
    );
    favBtn->setPosition({-150.f, 130.f});
    this->addChild(favBtn);

    // Botones de subcategorías
    m_menu = CCMenu::create();
    m_menu->setPosition(CCPointZero);
    this->addChild(m_menu);

    float y = 80.f;
    for (auto& pair : m_groupNames) {
        auto btn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(pair.second.c_str()),
            this,
            menu_selector(BlockHubPopup::onSelectSubcategory)
        );
        btn->setTag(pair.first);
        btn->setPosition({0.f, y});
        m_menu->addChild(btn);
        y -= 40.f;
    }

    // Scroll layer para bloques
    m_scrollLayer = ScrollLayer::create(CCSize(400.f, 200.f));
    m_scrollLayer->setPosition({-200.f, -120.f});
    this->addChild(m_scrollLayer);

    return true;
}

void BlockHubPopup::setupBlockGroups() {
    // Categoría de bloques (categoryID == 1)
    if (m_categoryID == 1) {
        m_groupNames = {
            {1, "Bloques Basicos"},
            {2, "Slopes"},
            {3, "Spikes"},
            {4, "Orbes"},
            {5, "Portales"},
            {6, "Pads"},
            {7, "Rings"},
            {8, "Hazards"}
        };
        m_blockGroups = {
            {1, {1, 2, 3, 4, 5, 6, 7, 8}},
            {2, {9, 10, 11, 12}},
            {3, {13, 14, 15, 16}},
            {4, {17, 18, 19, 20}},
            {5, {21, 22, 23}},
            {6, {24, 25, 26}},
            {7, {27, 28, 29}},
            {8, {30, 31, 32}}
        };
    }
    // Categoría de triggers (categoryID == 2)
    else if (m_categoryID == 2) {
        m_groupNames = {
            {1, "Move"},
            {2, "Rotate"},
            {3, "Scale"},
            {4, "Alpha"},
            {5, "Toggle"},
            {6, "Spawn"},
            {7, "Animate"},
            {8, "Follow"}
        };
        m_blockGroups = {
            {1, {100, 101, 102}},
            {2, {103, 104, 105}},
            {3, {106, 107, 108}},
            {4, {109, 110, 111}},
            {5, {112, 113, 114}},
            {6, {115, 116, 117}},
            {7, {118, 119, 120}},
            {8, {121, 122, 123}}
        };
    }
    // Categoría de decoraciones (categoryID == 3)
    else if (m_categoryID == 3) {
        m_groupNames = {
            {1, "Fondo"},
            {2, "Ground"},
            {3, "Animado"},
            {4, "Efectos"}
        };
        m_blockGroups = {
            {1, {200, 201, 202}},
            {2, {203, 204, 205}},
            {3, {206, 207, 208}},
            {4, {209, 210, 211}}
        };
    }
}

void BlockHubPopup::onSelectSubcategory(CCObject* sender) {
    int groupID = sender->getTag();
    showSubcategory(groupID);
}

void BlockHubPopup::showSubcategory(int groupID) {
    m_scrollLayer->m_contentLayer->removeAllChildren();

    m_filteredBlocks = m_blockGroups[groupID];

    float x = 0.f, y = 0.f;
    int col = 0;
    for (int blockID : m_filteredBlocks) {
        auto spr = CCSprite::createWithSpriteFrameName("block.png");
        if (!spr) spr = CCSprite::create("block.png");
        if (!spr) continue;
        auto btn = CCMenuItemSpriteExtra::create(
            spr,
            this,
            menu_selector(BlockHubPopup::onSelectBlock)
        );
        btn->setTag(blockID);
        btn->setPosition({x, y});
        m_scrollLayer->m_contentLayer->addChild(btn);

        auto favBtn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_starBtn_001.png"),
            this,
            menu_selector(BlockHubPopup::onAddToFavorites)
        );
        favBtn->setTag(blockID);
        favBtn->setScale(0.5f);
        favBtn->setPosition({x + 20.f, y + 20.f});
        m_scrollLayer->m_contentLayer->addChild(favBtn);

        col++;
        x += 50.f;
        if (col >= 7) {
            col = 0;
            x = 0.f;
            y -= 50.f;
        }
    }
}

void BlockHubPopup::onSelectBlock(CCObject* sender) {
    int blockID = sender->getTag();
    (void)blockID;
    this->onClose(nullptr);
}

void BlockHubPopup::onToggleFavorites(CCObject* sender) {
    m_showingFavorites = !m_showingFavorites;
    if (m_showingFavorites) {
        showFavorites();
    } else {
        showSubcategory(1);
    }
}

void BlockHubPopup::showFavorites() {
    m_scrollLayer->m_contentLayer->removeAllChildren();

    float x = 0.f, y = 0.f;
    int col = 0;
    for (int blockID : m_favorites) {
        auto spr = CCSprite::createWithSpriteFrameName("block.png");
        if (!spr) spr = CCSprite::create("block.png");
        if (!spr) continue;
        auto btn = CCMenuItemSpriteExtra::create(
            spr,
            this,
            menu_selector(BlockHubPopup::onSelectBlock)
        );
        btn->setTag(blockID);
        btn->setPosition({x, y});
        m_scrollLayer->m_contentLayer->addChild(btn);

        auto removeBtn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_deleteBtn_001.png"),
            this,
            menu_selector(BlockHubPopup::onAddToFavorites)
        );
        removeBtn->setTag(blockID);
        removeBtn->setScale(0.5f);
        removeBtn->setPosition({x + 20.f, y + 20.f});
        m_scrollLayer->m_contentLayer->addChild(removeBtn);

        col++;
        x += 50.f;
        if (col >= 7) {
            col = 0;
            x = 0.f;
            y -= 50.f;
        }
    }
}

void BlockHubPopup::onAddToFavorites(CCObject* sender) {
    int blockID = sender->getTag();
    auto it = std::find(m_favorites.begin(), m_favorites.end(), blockID);
    if (it != m_favorites.end()) {
        m_favorites.erase(it);
    } else {
        m_favorites.push_back(blockID);
    }
    saveFavorites();
    if (m_showingFavorites) {
        showFavorites();
    }
}

void BlockHubPopup::loadFavorites() {
    m_favorites = {};
}

void BlockHubPopup::saveFavorites() {
    // TODO: Mod::get()->setSavedValue
}

void BlockHubPopup::onSearch(CCObject* sender) {
    (void)sender;
}

void BlockHubPopup::filterBlocks(const std::string& query) {
    (void)query;
}

void BlockHubPopup::onClose(CCObject* sender) {
    (void)sender;
    this->setKeypadEnabled(false);
    this->removeFromParentAndCleanup(true);
}
