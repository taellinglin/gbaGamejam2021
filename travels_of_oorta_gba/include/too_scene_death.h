#ifndef TOO_SCENE_DEATH_H
#define TOO_SCENE_DEATH_H

#include "too_scene.h"
#include "too_player.h"

namespace too
{
    class Death
    {       
        private:
            Player* _player;
        public:
            Death(Player& player);
            Scene execute();
    };
}

#endif