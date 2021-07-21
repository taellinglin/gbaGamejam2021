#ifndef TOO_SCENE_HOUSE_H
#define TOO_SCENE_HOUSE_H

#include "too_scene.h"
#include "too_player.h"
#include "bn_fixed_point.h"

namespace too
{
    class House
    {       
        private:
            Player* _player;
        public:
            House(Player& player);
            Scene execute(bn::fixed_point spawn);
    };
}

#endif