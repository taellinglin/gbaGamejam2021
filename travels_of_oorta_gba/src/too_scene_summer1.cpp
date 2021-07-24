#include "too_scene_summer1.h"

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
#include "bn_affine_bg_map_ptr.h"
#include "bn_optional.h"
#include "bn_span.h"
#include "bn_affine_bg_map_cell.h"
#include "bn_math.h"


//fe code
#include "too_level.h"
#include "too_player.h"
#include "too_scene.h"
#include "too_npc.h"
#include "too_npc_type.h"
#include "too_tooltip.h"
#include "too_story_save.h"
#include "too_story_type.h"
#include "too_portal_type.h"
#include "too_portal.h"
//assets
#include "bn_sprite_items_cat_sprite.h"
#include "bn_sprite_items_box.h"
#include "bn_affine_bg_items_summer1.h"
#include "bn_regular_bg_items_summer_background.h"

#include "bn_sprite_text_generator.h"
#include "variable_8x8_sprite_font.h"
#include "bn_music_items.h"
#include "bn_music_actions.h"
#include "bn_sound_items.h"

namespace too
{
    Summer1::Summer1(Player& player)
    : _player(&player){}

    Scene Summer1::execute(bn::fixed_point spawn_location)
    {
        bn::sprite_text_generator text_generator(variable_8x8_sprite_font);

        bn::camera_ptr camera = bn::camera_ptr::create(spawn_location.x(), spawn_location.y());

        bn::music_items::summer_stage_1.play();
        bn::music::set_volume(0.7);

        //NPC
        //NPC tortoise = NPC(bn::fixed_point(380, 376), camera, NPC_TYPE::FROG, text_generator);
        //Tooltip explain_attack = Tooltip(bn::fixed_point(440, 304),"Press 'B' to Attack", text_generator);

        // map
        bn::regular_bg_ptr map_bg = bn::regular_bg_items::summer_background.create_bg(512, 512);
        bn::affine_bg_ptr map = bn::affine_bg_items::summer1.create_bg(512, 512);
        map_bg.set_priority(2);
        map.set_priority(1);
        too::Level level = too::Level(map);

        // camera
        map.set_camera(camera);
       // map_bg.set_camera(camera);

        // bn::fixed max_cpu_usage;
        // int counter = 1;
        bn::vector<Enemy, 16> enemies = {};

        // player
        _player->spawn(spawn_location, camera, map, enemies);
        
        
        while(true)
        {
            if(_player->hp() <= 0){
                bn::sound_items::oorta_die.play();
                _player->delete_data();
                return Scene::DEATH;
            }
            for(Enemy& enemy : enemies){
                if(bn::abs(enemy.pos().x() - camera.x()) < 200 && bn::abs(enemy.pos().y() - camera.y()) < 100){
                    enemy.update(_player->pos());
                } else {
                    enemy.set_visible(false);
                }
            }           
            _player->update_position(map,level);
            _player->apply_animation_state();
            
            bn::core::update();
        }
    }
}