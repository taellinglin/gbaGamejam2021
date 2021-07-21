#ifndef TOO_PORTAL_H
#define TOO_PORTAL_H

#include "bn_sprite_ptr.h"
#include "bn_fixed_point.h"
#include "bn_camera_ptr.h"
#include "bn_optional.h"
#include "bn_span.h"
#include "bn_vector.h"
#include "bn_display.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_text_generator.h"

#include "too_portal_type.h"
namespace too
{
    class Portal
    {
    private:
        PORTAL_TYPE _type;
        bn::fixed_point _pos;
        bn::camera_ptr& _camera;
        bn::optional<bn::sprite_ptr> _sprite;
        bn::optional<bn::sprite_animate_action<18>> _open;
        bn::optional<bn::sprite_animate_action<5>> _closed;
        bool _is_open = false;
        bool _hidden = false;
        bool _is_in_dialog = false;
        bool _is_near_player = false;
        bool _finished = false;
        bool _dialog_read = false;
        bn::vector<bn::sprite_ptr, 32> _text_sprites;
        bn::sprite_text_generator _text_generator;

        const bn::fixed _text_y_inc = 14;
        const bn::fixed _text_y_limit = (bn::display::height() / 2) - _text_y_inc;

        bn::span<bn::string_view> _lines;
        bn::string_view _tooltip;
        int _currentLine = 0;
        int _currentChar = 0;
        bn::string_view _currentChars = "";

    public:
        Portal(bn::fixed_point pos, bn::camera_ptr& camera, PORTAL_TYPE type, bn::sprite_text_generator& text_generator, bn::span<bn::string_view> lines, bn::string_view tooltip, bool is_open);
        void update();
        bool check_trigger(bn::fixed_point player_pos);
         bool is_in_dialog();
        void dialog();
        bool finished_dialog();
        void set_open(bool is_open);
        bool get_open();
        void set_is_hidden(bool is_hidden);
        bool hidden();
    };
    
    
    
}
#endif