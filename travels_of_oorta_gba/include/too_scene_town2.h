#ifndef TOO_SCENE_TOWN2_H
#define TOO_SCENE_TOWN2_H

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
    class Town2
    {       
        private:
            //Player pointer
            Player* _player;
            //Portal Dialogs
            bn::string_view portal_text_town[1] = {"This door has closed..."};
            bn::string_view portal_text_summer[1] = {"You need the Summer Key..."};
            bn::string_view portal_text_autumn[1] = {"You need the Autumn Key..."};
            bn::string_view portal_text_winter[1] = {"You need the Winter Key..."};
            bn::string_view portal_text_spring[1] = {"You need the Spring Key..."};

            //Portal label
            bn::string_view portal_title_town = "To Town 1";
            bn::string_view portal_title_summer = "To Summer 1";
            bn::string_view portal_title_autumn = "To Autumn 1";
            bn::string_view portal_title_winter = "To Winter 1";
            bn::string_view portal_title_spring = "To Sping 1";



            //NPCs & Subtexts

        public:
            Town2(Player& player);
            Scene execute(bn::fixed_point spawn);
    };
}

#endif