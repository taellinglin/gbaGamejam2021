#include "too_scene_town2.h"

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

//fe code
#include "too_level.h"
#include "too_player.h"
#include "too_scene.h"
#include "too_npc.h"
#include "too_npc_type.h"
#include "too_tooltip.h"
#include "too_portal.h"

//assets
#include "bn_sprite_items_cat_sprite.h"
#include "bn_sprite_items_box.h"
#include "bn_affine_bg_items_town2.h"
#include "bn_regular_bg_items_town_background.h"

#include "bn_sprite_text_generator.h"
#include "variable_8x8_sprite_font.h"
#include "bn_music_items.h"
#include "bn_music_actions.h"

namespace too
{
    Town2::Town2(Player& player)
    : _player(&player){}

    Scene Town2::execute(bn::fixed_point spawn_location)
    {
        bn::sprite_text_generator text_generator(variable_8x8_sprite_font);

        bn::camera_ptr camera = bn::camera_ptr::create(spawn_location.x(), spawn_location.y());

        bn::music_items::castle.play();
        bn::music::set_volume(0.7);

        // map
        bn::regular_bg_ptr map_bg = bn::regular_bg_items::town_background.create_bg(512, 512);
        bn::affine_bg_ptr map = bn::affine_bg_items::town2.create_bg(256, 256);
        map_bg.set_priority(1);
        map.set_priority(0);
        too::Level level = too::Level(map);

        // camera
        map.set_camera(camera);
       // map_bg.set_camera(camera);
        
        bn::vector<Portal*, 5> portals = {};
        portals.push_back(new Portal(bn::fixed_point(256, 384), camera, PORTAL_TYPE::TOWN_PORTAL,  too::Scene::TOWN1_TOWN2, text_generator, portal_text_town, portal_title_town, true));
        portals.push_back(new Portal(bn::fixed_point(48, 384), camera, PORTAL_TYPE::SUMMER_PORTAL, too::Scene::SUMMER1_TOWN2, text_generator, portal_text_summer, portal_title_summer, false));
        portals.push_back(new Portal(bn::fixed_point(144, 304), camera, PORTAL_TYPE::AUTUMN_PORTAL, too::Scene::AUTUMN1_TOWN2, text_generator, portal_text_autumn, portal_title_autumn, false));
        portals.push_back(new Portal(bn::fixed_point(368, 304), camera, PORTAL_TYPE::WINTER_PORTAL,  too::Scene::WINTER1_TOWN2,text_generator, portal_text_winter, portal_title_winter, false));
        portals.push_back(new Portal(bn::fixed_point(464, 384), camera, PORTAL_TYPE::SPRING_PORTAL, too::Scene::SPRING1_TOWN2, text_generator, portal_text_spring, portal_title_spring, false));
        //portals.push_back(new Portal(bn::fixed_point(64, 160), camera, PORTAL_TYPE::DUSK_PORTAL, too::Scene::DUSK1_TOWN1, text_generator, portal_text_dusk, portal_title_dusk, false));
        //portals.push_back(new Portal(bn::fixed_point(960, 160), camera, PORTAL_TYPE::DAWN_PORTAL, too::Scene::DAWN1_TOWN1, text_generator, portal_text_dawn, portal_title_dawn, false));
        
        //NPC
        
        //too::NPC frog = NPC(bn::fixed_point(932,957), camera, NPC_TYPE::FROG, text_generator);
        //too::Tooltip talk_to_frog = Tooltip(bn::fixed_point(932, 957),"Talk::Gero the Frog", text_generator);

        //No Enemies
        bn::vector<Enemy, 16> enemies = {};

        // player
        _player->spawn(spawn_location, camera, map, enemies);

        while(true)
        {
            /*
            if(frog.check_trigger(_player->pos()))
            {
                if(bn::keypad::up_pressed()){
                    _player->set_listening(true);
                   frog.talk();
                }else if(!frog.is_talking()){
                    _player->set_listening(false);
                }
            } else{
                _player->set_listening(false);
            }
            */

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
            
           

        
            //frog.update();
            //talk_to_frog.update();
            

            //Moving Elements
            //elevator.update_position();
            _player->update_position(map,level);
            _player->apply_animation_state();
            // BN_LOG(bn::to_string<32>(_player->pos().x())+" " + bn::to_string<32>(_player->pos().y()));
            

            
            
            bn::core::update();
        }
    }
}