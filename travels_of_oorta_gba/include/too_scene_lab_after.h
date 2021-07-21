#ifndef TOO_SCENE_LAB_AFTER_H
#define TOO_SCENE_LAB_AFTER_H

#include "too_scene.h"
#include "too_player.h"
#include "bn_fixed_point.h"

namespace too
{
    class LabAfter
    {       
        private:
            Player* _player;
        public:
            LabAfter(Player& player);
            Scene execute( bn::fixed_point spawn);
    };
}

#endif