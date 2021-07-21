#include "too_portal.h"
#include "too_portal_type.h"

#include "bn_optional.h"
#include "bn_math.h"
#include "bn_log.h"
#include "bn_display.h"
#include "bn_keypad.h"
#include "bn_sprite_text_generator.h"

#include "bn_sprite_items_portal_town.h"
#include "bn_sprite_items_portal_limbo.h"
#include "bn_sprite_items_portal_summer.h"
#include "bn_sprite_items_portal_autumn.h"
#include "bn_sprite_items_portal_winter.h"
#include "bn_sprite_items_portal_dawn.h"
#include "bn_sprite_items_portal_dusk.h"

#include "variable_8x8_sprite_font.h"
#include "bn_sprite_items_stone_plaque.h"
#include "bn_sound_items.h"

namespace too
{

    Portal::Portal(bn::fixed_point pos, bn::camera_ptr& camera, PORTAL_TYPE type, bn::sprite_text_generator& text_generator, bn::span<bn::string_view> lines, bn::string_view tooltip, bool is_open) :
        _pos(pos), _camera(camera), _type(type), _text_generator(text_generator), _lines(lines),_tooltip(tooltip), _is_open(is_open)
    {
        _text_generator.set_bg_priority(0);
        
        if(_type == PORTAL_TYPE::TOWN_PORTAL)
        {
            _sprite = bn::sprite_items::portal_town.create_sprite(_pos.x(), _pos.y());
            
            _closed = bn::sprite_animate_action<5>::forever( _sprite.value(), 120, bn::sprite_items::portal_town.tiles_item(), bn::array<uint16_t,5>{0,1,2,3,4});
            _open = bn::sprite_animate_action<18>::forever(_sprite.value(), 120, bn::sprite_items::portal_town.tiles_item(),  bn::array<uint16_t,18>{5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22});
                
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

    void Portal::set_open(bool is_open){
        _is_open = is_open;
    }

    bool Portal::get_open(){
        return _is_open;
    }


}