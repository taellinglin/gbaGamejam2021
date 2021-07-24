#ifndef TOO_SCENE_SUMMER2_H
#define TOO_SCENE_SUMMER2_H

#include "too_scene.h"
#include "too_player.h"
#include "bn_fixed_point.h"
#include "bn_string_view.h"
#include "bn_span.h"

namespace too
{
    class Summer2
    {       
        private:
            //Player
            Player* _player;

            //Portals and Tooltips/dialog

            //NPCs

            //Enemy sets...

            
        public:
            Summer2(Player& player);
            Scene execute(bn::fixed_point spawn);
    };
}

#endif