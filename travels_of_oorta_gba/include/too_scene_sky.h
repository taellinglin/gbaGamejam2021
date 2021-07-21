#ifndef TOO_SCENE_SKY_H
#define TOO_SCENE_SKY_H

#include "too_scene.h"
#include "too_player.h"
#include "bn_fixed_point.h"

namespace too
{
    class Sky
    {       
        private:
            Player* _player;
        public:
            Sky(Player& player);
            Scene execute(bn::fixed_point spawn);
    };
}

#endif