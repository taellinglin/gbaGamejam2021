#ifndef TOO_SCENE_TOWN1_H
#define TOO_SCENE_TOWN1_H

#include "too_scene.h"
#include "too_player.h"
#include "bn_fixed_point.h"
#include "bn_string_view.h"
#include "bn_span.h"

namespace too
{
    class Town1
    {       
        private:
            Player* _player;
            bn::string_view portal_text_limbo[1] = {
            "This door has closed..."
            };
            bn::string_view portal_text_summer[1] = {
            "You need the Summer Key..."
            };
            bn::string_view portal_text_autumn[1] = {
            "You need the Autumn Key..."
            };
            bn::string_view portal_text_winter[1] = {
            "You need the Winter Key..."
            };
            bn::string_view portal_text_spring[1] = {
            "You need the Spring Key..."
            };
            bn::string_view portal_text_dusk[1] = {
            "You need the Dusk Key..."
            };
            bn::string_view portal_text_dawn[1] = {
            "You need the Dawn Key..."
            };
            bn::string_view portal_title_limbo = "To Limbo 3";
            bn::string_view portal_title_summer = "To Summer 1";
            bn::string_view portal_title_autumn = "To Autumn 1";
            bn::string_view portal_title_winter = "To Winter 1";
            bn::string_view portal_title_spring = "To Sping 1";
            bn::string_view portal_title_dusk = "To Dusk 1";
            bn::string_view portal_title_dawn =  "To Dawn 1";

        public:
            Town1(Player& player);
            Scene execute(bn::fixed_point spawn);
    };
}

#endif