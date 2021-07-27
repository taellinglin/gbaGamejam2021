#include "too_scene_limbo3.h"

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
#include "bn_affine_bg_items_limbo3.h"
#include "bn_regular_bg_items_background.h"

#include "bn_sprite_text_generator.h"
#include "variable_8x8_sprite_font.h"
#include "bn_music_items.h"
#include "bn_music_actions.h"
#include "bn_sound_items.h"

namespace too
{
    Limbo3::Limbo3(Player& player)
    : _player(&player){}

    Scene Limbo3::execute(bn::fixed_point spawn_location)
    {
        bn::sprite_text_generator text_generator(variable_8x8_sprite_font);

        bn::camera_ptr camera = bn::camera_ptr::create(spawn_location.x(), spawn_location.y());

        bn::music_items::limbo_bgm.play();
        bn::music::set_volume(0.7);

        //NPC
        //NPC tortoise = NPC(bn::fixed_point(380, 376), camera, NPC_TYPE::FROG, text_generator);
        //Tooltip explain_attack = Tooltip(bn::fixed_point(440, 304),"Press 'B' to Attack", text_generator);

        // map
        bn::regular_bg_ptr map_bg = bn::regular_bg_items::background.create_bg(512, 512);
        bn::affine_bg_ptr map = bn::affine_bg_items::limbo3.create_bg(512, 512);
        map_bg.set_priority(1);
        map.set_priority(0);
        too::Level level = too::Level(map);

        // camera
        map.set_camera(camera);

        //Add NPCs
        //NPC frog = NPC(bn::fixed_point(832, 144), camera, NPC_TYPE::FROG, text_generator);

        //Enemies
        bn::vector<Enemy, 16> enemies = {};
        enemies.push_back(Enemy(191, 463, camera, map, ENEMY_TYPE::SLIME, 2));
        enemies.push_back(Enemy(656, 256, camera, map, ENEMY_TYPE::BAT, 1));

        // Spawn Player
        _player->spawn(spawn_location, camera, map, enemies);
        
        //Story Saves
        //StorySave to_limbo2 = StorySave(bn::fixed_point(944, 736), STORY_TYPE::BEGINNING, camera, text_generator);

        //Portals

        bn::vector<Portal*, 2> portals = {};
        portals.push_back(new Portal(bn::fixed_point(208, 224), camera, PORTAL_TYPE::LIMBO_PORTAL, Scene::LIMBO2_LIMBO3, text_generator, portal_text, portal_title_limbo2, true));
        portals.push_back(new Portal(bn::fixed_point(816, 368), camera, PORTAL_TYPE::TOWN_PORTAL, Scene::TOWN1_LIMBO3, text_generator, portal_text, portal_title_town, true));

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
            
            for(Portal* portal : portals){
                if(portal->check_trigger(_player->pos())){
                    if(bn::keypad::up_pressed()){
                        if(portal->get_is_open()){
                            return portal->goto_scene();
                        }else{
                            _player->set_listening(true);
                            portal->dialog();
                        }
                    }else if(!portal->is_in_dialog()){
                        _player->set_listening(false);
                    }
                }
                portal->update();
            }
            
            _player->update_position(map,level);
            _player->apply_animation_state();

            bn::core::update();
        }
    }
}