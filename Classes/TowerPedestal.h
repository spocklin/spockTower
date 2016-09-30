//游戏主界面初始塔基座

#ifndef __aStar__TowerPedestal__
#define __aStar__TowerPedestal__

#include "cocos2d.h"

USING_NS_CC;

class TowerPedestal: public Sprite
{
public:
    virtual bool init() override;
    CREATE_FUNC(TowerPedestal);
};

#endif