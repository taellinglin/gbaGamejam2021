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
            bn::string_view portal_text[1] = {
            "There are still monsters here!",
            };
            bn::string_view portal_title;
        public:
            Limbo1(Player& player);
            Scene execute(bn::fixed_point spawn);
    };
}

#endif