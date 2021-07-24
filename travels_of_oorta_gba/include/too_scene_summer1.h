#ifndef TOO_SCENE_SUMMER1_H
#define TOO_SCENE_SUMMER1_H

#include "too_scene.h"
#include "too_player.h"
#include "bn_fixed_point.h"
#include "bn_string_view.h"
#include "bn_span.h"

namespace too
{
    class Summer1
    {       
        private:
            //Player
            Player* _player;

            //Portals and Tooltips/dialog

            //NPCs

            //Enemy sets...

            
        public:
            Summer1(Player& player);
            Scene execute(bn::fixed_point spawn);
    };
}

#endif