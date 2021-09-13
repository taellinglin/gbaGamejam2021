#include "too_scene_loading.h"

//butano
#include "bn_core.h"
#include "bn_log.h"
#include "bn_keypad.h"
#include "bn_string.h"
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_camera_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_affine_bg_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_random.h"
#include "common_info.h"
#include "bn_sprite_text_generator.h"
#include "daemon_font.h"
//fe code
#include "too_scene.h"

//assets
#include "bn_sprite_items_cat_sprite.h"
#include "bn_sprite_items_cat_sprite_other.h"
#include "bn_regular_bg_items_loading_bg.h"
#include "bn_regular_bg_items_lab_bg.h"
#include "bn_regular_bg_items_loading_bg_other.h"
#include "bn_regular_bg_items_background.h"
#include "bn_regular_bg_items_midground.h"
#include "bn_regular_bg_items_foreground.h"

#include "bn_music_items.h"
#include "bn_music_actions.h"

#include "bn_music_items.h"

namespace too
{
    void Loading::execute(Scene next_scene)
    {
        bn::sprite_text_generator text_generator(common::daemon_font);
        

        bn::fixed_point init_pos = bn::fixed_point(0, 0);


        bn::music::set_volume(0.3);
        
        
        // player sprite
        bn::sprite_ptr cat_sprite1 = bn::sprite_items::cat_sprite.create_sprite(init_pos.x(), init_pos.y()+32);
        
        bn::sprite_animate_action<10> action1 = bn::create_sprite_animate_action_forever(
                        cat_sprite1, 2, bn::sprite_items::cat_sprite.tiles_item(), 8, 9,10,11, 2, 3, 4, 5, 6,7);

        cat_sprite1.set_scale(0.5);

        bn::camera_ptr camera = bn::camera_ptr::create(init_pos.x()+100, init_pos.y());

        // map
        bn::regular_bg_ptr background_bg = bn::regular_bg_items::background.create_bg(64, 32);
        bn::regular_bg_ptr midground_bg = bn::regular_bg_items::midground.create_bg(64, 64);
        bn::regular_bg_ptr foreground_bg = bn::regular_bg_items::foreground.create_bg(64, 64);
        foreground_bg.set_priority(0);
        // map.set_horizontal_scale(2);
        constexpr bn::string_view info_text_lines = "loading...";


        text_generator.generate(-36, 0, info_text_lines, _text_sprites);


        // camera
        cat_sprite1.set_camera(camera);
        /*
        background_bg.set_camera(camera);
        midground_bg.set_camera(camera);
        foreground_bg.set_camera(camera);
        */

        for(int i = 0; i < 160; ++i)
        {
            foreground_bg.set_x(foreground_bg.x() - 1);
            midground_bg.set_x(midground_bg.x() - 0.5);
            //info.update();
            cat_sprite1.set_x(cat_sprite1.x() + 1.3);
            action1.update();
            bn::core::update();
        }
    }
}