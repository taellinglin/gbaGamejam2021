#include "fe_dungeon_scene.h"

//butano
#include "bn_core.h"
#include "bn_log.h"
#include "bn_string.h"
#include "bn_keypad.h"
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_camera_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_affine_bg_ptr.h"

//fe code
#include "fe_level.h"
#include "fe_player.h"
#include "fe_scene.h"

//assets
#include "bn_sprite_items_cat.h"
#include "bn_affine_bg_items_dungeon.h"
#include "bn_regular_bg_items_dungeon_bg.h"
#include "bn_regular_bg_items_vines.h"

namespace fe
{
    Scene Dungeon::execute()
    {
        bn::fixed_point init_pos = bn::fixed_point(112, 952);

        // player sprite
        bn::sprite_ptr cat_sprite = bn::sprite_items::cat.create_sprite(init_pos.x(), init_pos.y());
        cat_sprite.set_bg_priority(1);
        bn::camera_ptr camera = bn::camera_ptr::create(init_pos.x(), init_pos.y());

        // map
        bn::regular_bg_ptr map_bg = bn::regular_bg_items::dungeon_bg.create_bg(512, 512);
        bn::affine_bg_ptr map = bn::affine_bg_items::dungeon.create_bg(512, 512);
        bn::regular_bg_ptr vines = bn::regular_bg_items::vines.create_bg(512, 512);
        map_bg.set_priority(2);
        map.set_priority(1);
        vines.set_priority(0);
        fe::Level level = fe::Level(map);
        map.set_horizontal_scale(2);
        map.set_vertical_scale(2);

        // camera
        cat_sprite.set_camera(camera);
        map.set_camera(camera);
        map_bg.set_camera(camera);
        vines.set_camera(camera);

        // player
        fe::Player player = fe::Player(init_pos, cat_sprite, camera);

        while(true)
        {

            //elevator.update_position();
            player.update_position(map,level);
            player.apply_animation_state();
            vines.set_position(bn::fixed_point((512-player.pos().x())/10,(512-player.pos().y())/10));
            BN_LOG(bn::to_string<32>(player.pos().x())+" " + bn::to_string<32>(player.pos().y()));

            if(bn::keypad::up_pressed())
            {
                if(player.pos().x() < 120 && player.pos().x() > 100){
                    if(player.pos().y() < 960 && player.pos().y() > 920){
                        return Scene::SKY;
                    }
                }
            }

            bn::core::update();
        }
    }
}