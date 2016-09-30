#include "TowerPedestal.h"

bool TowerPedestal::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }
    auto TowerPedestal = Sprite::createWithSpriteFrameName("whalespeech_bg.png");
    TowerPedestal->setPosition(Vec2(600,20));
    TowerPedestal->setScaleX(1.5);
    addChild(TowerPedestal);
    return true;
}