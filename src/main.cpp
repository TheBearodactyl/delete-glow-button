#include <Geode/Geode.hpp>
#include <Geode/binding/ButtonSprite.hpp>
#include <Geode/binding/CCMenuItemSpriteExtra.hpp>
#include <Geode/cocos/cocoa/CCObject.h>
#include <Geode/modify/EditorPauseLayer.hpp>
#include <Geode/modify/GameObject.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/Modify.hpp>
#include <Geode/utils/cocos.hpp>
#include <vector>

using namespace geode::prelude;

int glow_objs[] = {505, 504, 503, 1013, 1012, 1011, 1010, 1269, 1274, 1273, 1272, 1271, 1270, 1293, 1292, 1291, 1759, 1758, 1760, 1761, 1762, 1763, 1888, 1887, 1886};

struct UnGlowify : Modify<UnGlowify, LevelEditorLayer> {
    void del_objs_with_id(int id) {
      auto objs = CCArrayExt<GameObject*>(this->m_objects);
      std::vector<GameObject*> removed_objs;

      for (auto obj : objs) {
        for (int id : glow_objs) {
          if (obj && obj->m_objectID == id) {
            removed_objs.push_back(obj);
          }
        }
      }

      for (auto obj : removed_objs) {
        this->m_objects->removeObject(obj);
      }
    }
};

class $modify(DelAllGlow, EditorPauseLayer){bool init(LevelEditorLayer * lel){if (!EditorPauseLayer::init(lel)){return false;
}

auto menu = this->getChildByID("small-actions-menu");
auto deglowify_spr = ButtonSprite::create("Remove\nGlow", 30, 0, .4f, true, "bigFont.fnt", "GJ_button_04.png", 30.f);

deglowify_spr->setScale(.8f);

auto deglowify_btn = CCMenuItemSpriteExtra::create(deglowify_spr, this, menu_selector(UnGlowify::del_objs_with_id));

deglowify_btn->setID("deglowify-btn"_spr);
menu->insertBefore(deglowify_btn, nullptr);

menu->updateLayout();

return true;
}
}
;
