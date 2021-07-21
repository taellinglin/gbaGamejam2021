#ifndef TOO_SCENE_LIMBO1_H
#define TOO_SCENE_LIMBO1_H

#include "too_scene.h"
#include "too_player.h"
#include "bn_fixed_point.h"
#include "bn_string_view.h"
#include "bn_span.h"

namespace too
{
    class Limbo1
    {       
        private:
            Player* _player;
            bn::string_view portal_text[3] = {
            "This door is not open yet",
            "Wait here and train while",
            "we make the rest of the game!"
            };
            bn::string_view portal_title;
        public:
            Limbo1(Player& player);
            Scene execute(bn::fixed_point spawn);
    };
}

#endif