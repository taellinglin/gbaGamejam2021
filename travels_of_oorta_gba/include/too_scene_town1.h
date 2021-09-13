#ifndef TOO_SCENE_TOWN1_H
#define TOO_SCENE_TOWN1_H

#include "too_scene.h"
#include "too_player.h"
#include "bn_fixed_point.h"
#include "bn_vector.h"
#include "bn_string_view.h"
#include "bn_span.h"
#include "too_npc.h"
#include "too_npc_type.h"
#include "too_enemy.h"
#include "too_enemy_type.h"
#include "too_portal.h"
#include "too_tooltip.h"



namespace too
{
    class Town1
    {       
        private:
            //Player pointer
            Player* _player;
            //Portal Dialogs
            bn::string_view portal_text_limbo[1] = {"This door has closed..."};
            bn::string_view portal_text_dusk[1] = {"You need the Dusk Key..."};
            bn::string_view portal_text_dawn[1] = {"You need the Dawn Key..."};

            //Portal label
            bn::string_view portal_title_limbo = "To Limbo 3";
            bn::string_view portal_title_dusk = "To Dusk 1";
            bn::string_view portal_title_dawn =  "To Dawn 1";



            //NPCs & Subtexts

        public:
            Town1(Player& player);
            Scene execute(bn::fixed_point spawn);
    };
}

#endif