#pragma once

#include <Geode/Geode.hpp>
#include <map>
#include <vector>
#include <string>

using namespace geode::prelude;

class BlockHubPopup : public FLAlertLayer {
protected:
    int m_categoryID;
    CCMenu* m_menu;
    CCScrollLayerExt* m_scrollLayer;
    CCTextInputNode* m_searchInput;
    std::map<int, std::vector<int>> m_blockGroups;
    std::map<int, std::string> m_groupNames;
    std::vector<int> m_filteredBlocks;
    std::vector<int> m_favorites;
    bool m_showingFavorites;

    bool init(int categoryID);
    void onClose(CCObject* sender);
    void onSelectSubcategory(CCObject* sender);
    void onSelectBlock(CCObject* sender);
    void onSearch(CCObject* sender);
    void onToggleFavorites(CCObject* sender);
    void onAddToFavorites(CCObject* sender);
    void filterBlocks(const std::string& query);
    void loadFavorites();
    void saveFavorites();

public:
    static BlockHubPopup* create(int categoryID);
    void showSubcategory(int groupID);
    void setupBlockGroups();
    void showFavorites();
};