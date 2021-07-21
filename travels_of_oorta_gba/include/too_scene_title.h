#ifndef TOO_SCENE_TITLE_H
#define TOO_SCENE_TITLE_H

#include "too_scene.h"
#include "bn_optional.h"
#include "bn_regular_bg_ptr.h"

namespace too
{
    class Title
    {   private:
            bn::optional <bn::regular_bg_ptr> background_bg;
            bn::optional <bn::regular_bg_ptr> midground_bg;
            bn::optional <bn::regular_bg_ptr> foreground_bg;

        public:
            Scene execute();
    };
}

#endif