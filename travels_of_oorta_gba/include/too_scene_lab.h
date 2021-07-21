#ifndef TOO_SCENE_LAB_H
#define TOO_SCENE_LAB_H

#include "too_scene.h"
#include "too_player.h"
#include "bn_fixed_point.h"

namespace too
{
    class Lab
    {       
        private:
            Player* _player;
        public:
            Lab(Player& player);
            Scene execute( bn::fixed_point spawn);
    };
}

#endif