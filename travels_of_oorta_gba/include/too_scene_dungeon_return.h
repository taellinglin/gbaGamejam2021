#ifndef TOO_SCENE_DUNEON_RETURN_H
#define TOO_SCENE_DUNEON_RETURN_H

#include "too_scene.h"
#include "too_player.h"
#include "bn_fixed_point.h"

namespace too
{
    class DungeonReturn
    {       
        private:
            Player* _player;
        public:
            DungeonReturn(Player& player);
            Scene execute(bn::fixed_point spawn);
    };
}

#endif