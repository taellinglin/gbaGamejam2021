#include "too_scene_town1.h"

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
#include "bn_affine_bg_items_town1.h"
#include "bn_regular_bg_items_town_background.h"

#include "bn_sprite_text_generator.h"
#include "variable_8x8_sprite_font.h"
#include "bn_music_items.h"
#include "bn_music_actions.h"

namespace too
{
    Town1::Town1(Player& player)
    : _player(&player){}

    Scene Town1::execute(bn::fixed_point spawn_location)
    {
        bn::sprite_text_generator text_generator(variable_8x8_sprite_font);

        bn::camera_ptr camera = bn::camera_ptr::create(spawn_location.x(), spawn_location.y());

        bn::music_items::castle.play();
        bn::music::set_volume(0.7);

        // map
        bn::regular_bg_ptr map_bg = bn::regular_bg_items::town_background.create_bg(512, 512);
        bn::affine_bg_ptr map = bn::affine_bg_items::town1.create_bg(512, 512);
        map_bg.set_priority(1);
        map.set_priority(0);
        too::Level level = too::Level(map);

        // camera
        map.set_camera(camera);
       // map_bg.set_camera(camera);
        
        //Open Portals
        Portal to_limbo3 = Portal(bn::fixed_point(80, 976), camera, PORTAL_TYPE::LIMBO_PORTAL, text_generator, portal_text_limbo, portal_title_limbo, true);
        to_limbo3.set_open(true);

        //Closed Portals
        Portal to_summer1 = Portal(bn::fixed_point(880,672), camera, PORTAL_TYPE::SUMMER_PORTAL, text_generator, portal_text_summer, portal_title_summer, false);
        to_summer1.set_open(false);
        /*
         Portal to_autumn1 = Portal(bn::fixed_point(64,512), camera, PORTAL_TYPE::AUTUMN_PORTAL, text_generator, portal_text_autumn, portal_title_autumn, false);
        to_autumn1.set_open(false);

         Portal to_winter1 = Portal(bn::fixed_point(320,336), camera, PORTAL_TYPE::WINTER_PORTAL, text_generator, portal_text_winter, portal_title_winter, false);
        to_winter1.set_open(false);

        Portal to_spring1 = Portal(bn::fixed_point(748,416), camera, PORTAL_TYPE::SPRING_PORTAL, text_generator, portal_text_spring, portal_title_spring, false);
        to_spring1.set_open(false);
        */
/*
        Portal to_dusk1 = Portal(bn::fixed_point(64,160), camera, PORTAL_TYPE::DUSK_PORTAL, text_generator, portal_text_dusk, portal_title_dusk, false);
        to_dusk1.set_open(false);

        Portal to_dawn1 = Portal(bn::fixed_point(64,160), camera, PORTAL_TYPE::DAWN_PORTAL, text_generator, portal_text_dawn, portal_title_dawn, false);
        to_dawn1.set_open(false);
*/
        //NPC
        /*
        NPC frog = NPC(bn::fixed_point(932,957), camera, NPC_TYPE::FROG, text_generator);
        Tooltip explain_attack = Tooltip(bn::fixed_point(932, 957),"Talk::Gero the Frog", text_generator);
        */
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
            if(to_limbo3.check_trigger(_player->pos()))
            {
                if(bn::keypad::up_pressed()){
                    return Scene::LIMBO3_TOWN1;
                }else if(!to_limbo3.is_in_dialog()){
                    _player->set_listening(false);
                }else{
                _player->set_listening(false);
                }
            }
            
            if(to_summer1.check_trigger(_player->pos()))
            {
                if(bn::keypad::up_pressed()){
                    _player->set_listening(true);
                    to_summer1.dialog();
                }else if(!to_summer1.is_in_dialog()){
                    _player->set_listening(false);
                }else{
                    _player->set_listening(false);
                }
            }
          /*  
            if(to_autumn1.check_trigger(_player->pos()))
            {
                if(bn::keypad::up_pressed()){
                    _player->set_listening(true);
                    to_autumn1.dialog();
                }else if(!to_autumn1.is_in_dialog()){
                    _player->set_listening(false);
                }
                else {
                _player->set_listening(false);
                }
            }
            
            if(to_winter1.check_trigger(_player->pos()))
            {
                if(bn::keypad::up_pressed()){
                    _player->set_listening(true);
                    to_winter1.dialog();
                }else if(!to_winter1.is_in_dialog()){
                    _player->set_listening(false);
                }else {
                    _player->set_listening(false);
                }
            }
            
            if(to_spring1.check_trigger(_player->pos()))
            {
                if(bn::keypad::up_pressed()){
                    _player->set_listening(true);
                    to_spring1.dialog();
                }else if(!to_spring1.is_in_dialog()){
                    _player->set_listening(false);
                }else{
                    _player->set_listening(false);
                }
            }

            */
            /*
            if(to_dusk1.check_trigger(_player->pos()))
            {
                if(bn::keypad::up_pressed()){
                    _player->set_listening(true);
                    to_dusk1.dialog();
                }else if(!to_dusk1.is_in_dialog()){
                    _player->set_listening(false);
                }else{
                    _player->set_listening(false);
                }
            }
            
            if(to_dawn1.check_trigger(_player->pos()))
            {
                if(bn::keypad::up_pressed()){
                    _player->set_listening(true);
                    to_dawn1.dialog();
                }else if(!to_dawn1.is_in_dialog()){
                    _player->set_listening(false);
                }else{
                _player->set_listening(false);
                }
            }
            */
            to_limbo3.update();

            to_summer1.update();
            //to_autumn1.update();
            //to_winter1.update();
            //to_spring1.update();
            /*
            to_dusk1.update();
            to_dawn1.update();
            */
           /*
            frog.update();
            */
            //explain_attack.update();

            //elevator.update_position();
            _player->update_position(map,level);
            _player->apply_animation_state();
            // BN_LOG(bn::to_string<32>(_player->pos().x())+" " + bn::to_string<32>(_player->pos().y()));
            

            
            
            bn::core::update();
        }
    }
}