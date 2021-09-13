#ifndef BF_SCENE_H
#define BF_SCENE_H

namespace too
{
    enum class Scene
    {
        HOUSE_START,
        LIMBO1,
        LIMBO1_LIMBO2,
        LIMBO2_LIMBO1,
        LIMBO3_LIMBO2,
        LIMBO2_LIMBO3,
        TOWN1_LIMBO3,
        LIMBO3_TOWN1,
        TOWN1_TOWN2,
        TOWN2_TOWN1,
        TOWN2_SUMMER1,
        SUMMER1_TOWN2,
        SUMMER1_SUMMER2,
        SUMMER2_SUMMER1,
        TOWN2_AUTUMN1,
        AUTUMN1_TOWN2,
        TOWN2_WINTER1,
        WINTER1_TOWN2,
        TOWN2_SPRING1,
        SPRING1_TOWN2,
        TOWN1_DUSK1,
        DUSK1_TOWN1,
        TOWN1_DAWN1,
        DAWN1_TOWN1,
        HOUSE_SKY,
        SKY_HOUSE,
        SKY_DUNGEON,
        RETURN_SKY,
        DUNGEON_SKY,
        OTHER,
        OTHER_DUNGEON,
        INTRO,
        GBA,
        BUTANO,
        DEATH,
        LOADING,
        TITLE,
        LAB,
        LAB_AFTER,
        END
    };
}

#endif
