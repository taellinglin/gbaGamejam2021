#ifndef TOO_SCENE_SKY_RETURN_H
#define TOO_SCENE_SKY_RETURN_H

#include "too_scene.h"
#include "too_player.h"
#include "bn_fixed_point.h"

namespace too
{
    class SkyReturn
    {       
        private:
            Player* _player;
        public:
            SkyReturn(Player& player);
            Scene execute(bn::fixed_point spawn);
    };
}

#endif