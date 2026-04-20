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
    setupBlockGroups();

    if (!FLAlertLayer::init(nullptr, "Block Hub", "", "Cerrar", nullptr, 400.f, false, 0, 1.f)) return false;

    // Campo de búsqueda
    m_searchInput = CCTextInputNode::create(200.f, 30.f, "Buscar...", "bigFont.fnt");
    m_searchInput->setPosition({0, 120});
    m_searchInput->setDelegate(this);
    this->addChild(m_searchInput);

    // Botones de subcategorías
    m_menu = CCMenu::create();
    m_menu->setPosition(CCPointZero);
    this->addChild(m_menu);

    int y = 80;
    for (auto& pair : m_groupNames) {
        auto btn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(pair.second.c_str()),
            this,
            menu_selector(BlockHubPopup::onSelectSubcategory)
        );
        btn->setTag(pair.first);
        btn->setPosition({0, y});
        m_menu->addChild(btn);
        y -= 40;
    }

    // Scroll layer para bloques
    m_scrollLayer = CCScrollLayerExt::create(CCRect(0, 0, 350, 200));
    m_scrollLayer->setPosition({-175, -100});
    this->addChild(m_scrollLayer);

    return true;
}

void BlockHubPopup::setupBlockGroups() {
    // Ejemplo para categoría de bloques (categoryID == 1)
    if (m_categoryID == 1) {
        m_groupNames = {
            {1, "Cuadrados"},
            {2, "Slopes"},
            {3, "Glow"},
            {4, "Spikes"},
            {5, "Orbes"}
        };
        m_blockGroups = {
            {1, {1, 2, 3, 4}},      // Cuadrados
            {2, {10, 11, 12}},      // Slopes
            {3, {50, 51, 52}},      // Glow
            {4, {100, 101, 102}},   // Spikes
            {5, {200, 201, 202}}    // Orbes
        };
    }
    // Agregar más categorías: triggers, deco, etc.
    else if (m_categoryID == 2) {  // Triggers
        m_groupNames = {
            {1, "Move"},
            {2, "Rotate"},
            {3, "Scale"}
        };
        m_blockGroups = {
            {1, {300, 301}},
            {2, {310, 311}},
            {3, {320, 321}}
        };
    }
    // Etc.
}

void BlockHubPopup::onSelectSubcategory(CCObject* sender) {
    int groupID = sender->getTag();
    showSubcategory(groupID);
}

void BlockHubPopup::showSubcategory(int groupID) {
    m_scrollLayer->m_contentLayer->removeAllChildren();

    m_filteredBlocks = m_blockGroups[groupID];

    int x = 0, y = 0;
    int col = 0;
    for (int blockID : m_filteredBlocks) {
        auto spr = CCSprite::createWithSpriteFrameName("block.png");  // Placeholder
        if (!spr) spr = CCSprite::create("block.png");  // Fallback
        auto btn = CCMenuItemSpriteExtra::create(
            spr,
            this,
            menu_selector(BlockHubPopup::onSelectBlock)
        );
        btn->setTag(blockID);
        btn->setPosition({x, y});
        m_scrollLayer->m_contentLayer->addChild(btn);
        col++;
        x += 50;
        if (col >= 7) {  // 7 columnas
            col = 0;
            x = 0;
            y -= 50;
        }
    }

    m_scrollLayer->updateScrollBounds();
}

void BlockHubPopup::onSelectBlock(CCObject* sender) {
    int blockID = sender->getTag();
    // Seleccionar el bloque en el editor
    // EditorUI::get()->selectObject(blockID, true);
    this->onClose(nullptr);
}

void BlockHubPopup::onSearch(CCObject* sender) {
    std::string query = m_searchInput->getString();
    filterBlocks(query);
    // Actualizar la vista actual
    if (!m_filteredBlocks.empty()) {
        showSubcategory(1);  // Mostrar en la subcategoría actual o global
    }
}

void BlockHubPopup::filterBlocks(const std::string& query) {
    // Implementar filtrado simple por ID o nombre (placeholder)
    m_filteredBlocks.clear();
    for (auto& group : m_blockGroups) {
        for (int id : group.second) {
            if (query.empty() || std::to_string(id).find(query) != std::string::npos) {
                m_filteredBlocks.push_back(id);
            }
        }
    }
}

void BlockHubPopup::onClose(CCObject* sender) {
    this->setKeypadEnabled(false);
    this->removeFromParentAndCleanup(true);
}