#ifndef TOO_SCENE_LIMBO3_H
#define TOO_SCENE_LIMBO3_H

#include "too_scene.h"
#include "too_player.h"
#include "bn_fixed_point.h"
#include "bn_string_view.h"
#include "bn_span.h"

namespace too
{
    class Limbo3
    {       
        private:
            Player* _player;
            bn::string_view portal_text[1] = {
            "This door is not open yet"
            };
            bn::string_view portal_title_limbo2 = "To Limbo 2";
            bn::string_view portal_title_town = "To Town";
        public:
            Limbo3(Player& player);
            Scene execute(bn::fixed_point spawn);
    };
}

#endif