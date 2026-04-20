#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>
#include "BlockHubPopup.hpp"

using namespace geode::prelude;

class $modify(MyEditorUI, EditorUI) {
    void onSelectCategory(CCObject* sender) {
        // Cancelar el comportamiento original
        // Abrir el HUB personalizado
        int categoryID = sender->getTag();  // Asumiendo que el tag es el ID de categoría
        BlockHubPopup::create(categoryID)->show();
    }
};

$execute {
    // Inicialización si es necesaria
}