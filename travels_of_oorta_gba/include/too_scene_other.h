#ifndef TOO_SCENE_OTHER_H
#define TOO_SCENE_OTHER_H

#include "too_scene.h"
#include "too_player.h"
#include "bn_fixed_point.h"

namespace too
{
    class Other
    {       
        private:
            Player* _player;
        public:
            Other(Player& player);
            Scene execute( bn::fixed_point spawn);
    };
}

#endif