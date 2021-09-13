#ifndef TOO_SCENE_LOADING_H
#define TOO_SCENE_LOADING_H

#include "too_scene.h"
#include"bn_optional.h"
#include "bn_vector.h"
#include "bn_sprite_ptr.h"
namespace too
{
    class Loading
    {       
        private:
        bn::vector<bn::sprite_ptr, 32> _text_sprites;
        public:
            void execute(Scene next_scene);
    };
}

#endif