#include "too_portal.h"
#include "too_portal_type.h"

#include "bn_optional.h"
#include "bn_math.h"
#include "bn_log.h"
#include "bn_display.h"
#include "bn_keypad.h"
#include "bn_sprite_text_generator.h"

#include "bn_sprite_items_portal_town.h"
/*
#include "bn_sprite_items_portal_limbo.h"
#include "bn_sprite_items_portal_summer.h"
#include "bn_sprite_items_portal_spring.h"
#include "bn_sprite_items_portal_autumn.h"
#include "bn_sprite_items_portal_winter.h"
#include "bn_sprite_items_portal_dawn.h"
#include "bn_sprite_items_portal_dusk.h"
*/

#include "bn_sprite_palette_items_portal_limbo_pal.h"
#include "bn_sprite_palette_items_portal_town_pal.h"
#include "bn_sprite_palette_items_portal_summer_pal.h"
#include "bn_sprite_palette_items_portal_autumn_pal.h"
#include "bn_sprite_palette_items_portal_winter_pal.h"
#include "bn_sprite_palette_items_portal_spring_pal.h"
#include "bn_sprite_palette_items_portal_dusk_pal.h"
#include "bn_sprite_palette_items_portal_dawn_pal.h"

//Palette Includes
#include "bn_sprite_palette_actions.h"
#include "bn_sprite_palettes_actions.h"
#include "bn_bg_palette_color_hbe_ptr.h"
#include "bn_bg_palettes_transparent_color_hbe_ptr.h"

#include "variable_8x8_sprite_font.h"
#include "bn_sprite_items_stone_plaque.h"
#include "bn_sound_items.h"

namespace too
{

    Portal::Portal(bn::fixed_point pos, bn::camera_ptr& camera, PORTAL_TYPE type, Scene scene, bn::sprite_text_generator& text_generator,  bn::span<bn::string_view> lines, bn::string_view tooltip, bool is_open) :
        _pos(pos), _camera(camera), _type(type), _text_generator(text_generator), _lines(lines),_tooltip(tooltip), _is_open(is_open), _scene(scene)
    {
        
        _sprite = bn::sprite_items::portal_town.create_sprite(_pos.x(), _pos.y());
        const bn::sprite_palette_item& palette_item = bn::sprite_items::portal_town.palette_item();
        const bn::sprite_palette_item& portal_town_palette = bn::sprite_palette_items::portal_town_pal;
        const bn::sprite_palette_item& portal_limbo_palette = bn::sprite_palette_items::portal_limbo_pal;
        const bn::sprite_palette_item& portal_summer_palette = bn::sprite_palette_items::portal_summer_pal;
        const bn::sprite_palette_item& portal_autumn_palette = bn::sprite_palette_items::portal_autumn_pal;
        const bn::sprite_palette_item& portal_winter_palette = bn::sprite_palette_items::portal_winter_pal;
        const bn::sprite_palette_item& portal_spring_palette = bn::sprite_palette_items::portal_spring_pal;
        const bn::sprite_palette_item& portal_dusk_palette = bn::sprite_palette_items::portal_dusk_pal;
        const bn::sprite_palette_item& portal_dawn_palette = bn::sprite_palette_items::portal_dawn_pal;
        bn::sprite_palette_ptr portal_palette = _sprite->palette();
        portal_palette.set_colors(portal_town_palette);
        _closed = bn::sprite_animate_action<5>::forever( _sprite.value(), 10, bn::sprite_items::portal_town.tiles_item(), bn::array<uint16_t,5>{0,1,2,3,4});
        _open = bn::sprite_animate_action<17>::forever(_sprite.value(), 10, bn::sprite_items::portal_town.tiles_item(),  bn::array<uint16_t,17>{5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21});
        _text_generator.set_bg_priority(0);
        
        if(_type == PORTAL_TYPE::TOWN_PORTAL)
        {
            portal_palette.set_colors(portal_town_palette);        
        }
        else if(_type == PORTAL_TYPE::LIMBO_PORTAL)
        {
            portal_palette.set_colors(portal_limbo_palette);
        }
        else if(_type == PORTAL_TYPE::SUMMER_PORTAL)
        {
            portal_palette.set_colors(portal_summer_palette);
        }
        else if(_type == PORTAL_TYPE::AUTUMN_PORTAL)
        {
            portal_palette.set_colors(portal_autumn_palette);      
        }
        else if(_type == PORTAL_TYPE::WINTER_PORTAL)
        {
            portal_palette.set_colors(portal_winter_palette);
        }
        else if(_type == PORTAL_TYPE::SPRING_PORTAL)
        {
            portal_palette.set_colors(portal_spring_palette);
        }
        else if(_type == PORTAL_TYPE::DAWN_PORTAL)
        {
            portal_palette.set_colors(portal_dawn_palette);
        }
        else if(_type == PORTAL_TYPE::DUSK_PORTAL)
        {
            portal_palette.set_colors(portal_dusk_palette);
        }
        if(_sprite.has_value())
        {
            _sprite.value().set_camera(_camera);
            _sprite.value().set_bg_priority(1);
            _sprite.value().set_z_order(2);
        }
    }
   
    void Portal::update(){
        if (_is_open){
            if(_open.has_value()){
            _open->update();
            }
        }
        else{
            if(_closed.has_value()){
            _closed->update();
            }
        }


        if(_is_in_dialog){
            if(_currentChar == _lines.at(_currentLine).size() * 2){
                if(bn::keypad::up_pressed() || bn::keypad::a_pressed() || bn::keypad::a_held() || bn::keypad::up_held())
                {
                    if(_currentLine == _lines.size()-1)
                    {
                        _is_in_dialog = false;
                        _currentChars = "";
                        _currentChar = 0;
                        _currentLine = 0;
                        _dialog_read = true;
                    } else {
                        bn::sound_items::dialog_start.play();
                        _currentLine += 1;
                        _currentChar = 0;
                    }
                } else if(bn::keypad::start_pressed()){
                    bn::sound_items::dialog_end.play();
                    _is_in_dialog = false;
                    _currentChars = "";
                    _currentChar = 0;
                    _currentLine = 0;
                    _dialog_read = true;
                }
            } else {
                if(bn::keypad::start_pressed()){
                    _is_in_dialog = false;
                    _currentChars = "";
                    _currentChar = 0;
                    _currentLine = 0;
                    _dialog_read = true;
                }
                _currentChars = _lines.at(_currentLine).substr(0,(_currentChar/2)+1);
                if(bn::keypad::a_held() || bn::keypad::up_held()){
                    _currentChar+=2;
                    bn::sound_items::type.play();
                } else {
                    bn::sound_items::type.play();
                    ++_currentChar;
                }
                
            }
            _text_generator.set_left_alignment();
            _text_sprites.clear();
            _text_generator.generate(-110, _text_y_limit, _currentChars, _text_sprites);
        } else if(_is_near_player && !_finished) {
            _text_generator.set_center_alignment();
            _text_sprites.clear();
            _text_generator.generate(0, _text_y_limit, _tooltip, _text_sprites);
        } else {
            _text_sprites.clear();
        }
    }

    bool Portal::finished_dialog(){
        return _dialog_read;
    }

    bool Portal::check_trigger(bn::fixed_point pos){
        if(!_finished && !_hidden){
            if(bn::abs(_pos.x() - pos.x()) < 50){
                if(bn::abs(_pos.y() - pos.y()) < 50){
                    _is_near_player = true;
                    return true;
                }
            }
            _is_near_player = false;
        }
        return false;
    }

    void Portal::dialog(){
        _is_in_dialog = true;
        bn::sound_items::dialog_start.play();
    }

    bool Portal::is_in_dialog(){
        return _is_in_dialog;
    }

    void Portal::set_is_hidden(bool is_hidden){
        _hidden = is_hidden;
        if(_sprite.has_value()){
            _sprite->set_visible(!is_hidden);
        }
    }

    bool Portal::hidden(){
        return _hidden;
    }

    void Portal::set_is_open(bool is_open){
        _is_open = is_open;
    }

    bool Portal::get_is_open(){
        return _is_open;
    }
    Scene Portal::goto_scene(){
        reset();
        return _scene;
    }
    void Portal::set_scene(Scene& scene){
        _scene = scene;
    }
    void Portal::reset(){
        if(_sprite.has_value()){
            _sprite.reset();
        }
        if(_open.has_value()){
            _open.reset();
        }
        if(_closed.has_value()){
            _closed.reset();
        }
    }


}