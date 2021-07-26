#ifndef TOO_SCENE_LOADING_H
#define TOO_SCENE_LOADING_H

#include "too_scene.h"
#include"bn_optional.h"
namespace too
{
    class Loading
    {       
        public:
            void execute(Scene next_scene);
    };
}

#endif