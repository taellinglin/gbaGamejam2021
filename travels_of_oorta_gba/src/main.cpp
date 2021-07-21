#include "bn_core.h"
#include "bn_math.h"
#include "bn_sprite_builder.h"
#include "bn_sprite_ptr.h"
#include "bn_keypad.h"
#include "bn_string.h"
#include "bn_regular_bg_ptr.h"
#include "bn_fixed_point.h"
#include "bn_regular_bg_item.h"
#include "bn_affine_bg_ptr.h"
#include "bn_affine_bg_item.h"
#include "bn_affine_bg_tiles_ptr.h"
#include "bn_affine_bg_map_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_camera_actions.h"
#include "bn_sprite_animate_actions.h"

#include "bn_string_view.h"
#include "bn_vector.h"
#include "bn_log.h"
#include "bn_sprite_text_generator.h"

#include "too_hitbox.h"
#include "too_scene_dungeon.h"
#include "too_scene_dungeon_return.h"
#include "too_scene_sky.h"
#include "too_scene_sky_return.h"
#include "too_scene_other.h"
#include "too_scene_house.h"
#include "too_scene_loading.h"
#include "too_scene_title.h"
#include "too_scene_death.h"
#include "too_scene_gba.h"
#include "too_scene_butano.h"
#include "too_scene_end.h"
#include "too_scene_lab.h"
#include "too_scene_lab_after.h"
#include "too_scene_limbo1.h"
#include "too_scene.h"

#include "bn_sprite_items_cat_sprite.h"
#include "common_info.h"
#include "common_variable_8x16_sprite_font.h"

int main()
{
    bn::core::init();
    too::Scene scene = too::Scene::TITLE;
    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);

    bn::sprite_ptr cat_sprite = bn::sprite_items::cat_sprite.create_sprite(0,0);
    cat_sprite.set_visible(false);
    too::Player player = too::Player(cat_sprite, text_generator);

    while(true)
    {
        if(scene == too::Scene::HOUSE_START){
            too::House house = too::House(player);
            scene = house.execute(bn::fixed_point(293, 368));
        } 
        else if(scene == too::Scene::LIMBO1){
            too::Limbo1 limbo1= too::Limbo1(player);
            scene = limbo1.execute(bn::fixed_point(112, 208));
        } 
        else if(scene == too::Scene::HOUSE_SKY){
            too::Sky sky = too::Sky(player);
            scene = sky.execute(bn::fixed_point(153, 272));
        } 
        else if(scene == too::Scene::SKY_DUNGEON)
        {
            too::Dungeon dungeon = too::Dungeon(player);
            scene = dungeon.execute(bn::fixed_point(150, 192));
        } 
        else if(scene == too::Scene::DUNGEON_SKY)
        {
            too::Sky sky = too::Sky(player);
            scene = sky.execute(bn::fixed_point(169, 616));
        }
        else if(scene == too::Scene::RETURN_SKY)
        {
            too::SkyReturn sky_return = too::SkyReturn(player);
            scene = sky_return.execute(bn::fixed_point(169, 616));
        }
        else if(scene == too::Scene::SKY_HOUSE)
        {
            too::House house = too::House(player);
            scene = house.execute(bn::fixed_point(555, 384));
        }
        else if(scene == too::Scene::TITLE)
        {
            too::Title title = too::Title();
            scene = title.execute();
        }
        else if(scene == too::Scene::BUTANO)
        {
            too::Butano butano = too::Butano();
            scene = butano.execute();
        }
        else if(scene == too::Scene::GBA)
        {
            too::GBA gba = too::GBA();
            scene = gba.execute();
        }
        else if(scene == too::Scene::END)
        {
            too::End end = too::End();
            scene = end.execute();
            scene = too::Scene::TITLE;
        }
        else if(scene == too::Scene::OTHER)
        {
            too::Other other = too::Other(player);
            scene = other.execute(bn::fixed_point(235, 590));
        }
        else if(scene == too::Scene::OTHER_DUNGEON)
        {
            too::DungeonReturn dungeon2 = too::DungeonReturn(player);
            scene = dungeon2.execute(bn::fixed_point(212, 848));
        }
        else if(scene == too::Scene::DEATH)
        {
            too::Death death = too::Death(player);
            scene = death.execute();
        }
        else if(scene == too::Scene::LAB)
        {
            too::Lab lab = too::Lab(player);
            scene = lab.execute(bn::fixed_point(61, 344));
        }
        else if(scene == too::Scene::LAB_AFTER)
        {
            too::LabAfter lab_after = too::LabAfter(player);
            scene = lab_after.execute(bn::fixed_point(502, 704));
        }
        player.delete_data();
        player.hide();
        if(scene != too::Scene::DEATH && scene != too::Scene::BUTANO && scene != too::Scene::TITLE){
            too::Loading loading = too::Loading();
            loading.execute(scene);
        }
        bn::core::update();
        
    }
    
}
