#pragma once
#include "includes.h"
#include "GarageLayer.h"
#include "AchievementNotifier.h"

class MenuLayer : public Layer {
public:
    static Scene* scene();
    bool init();
    CREATE_FUNC(MenuLayer);
};