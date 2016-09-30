//存储每盘开始时候的塔的信息

#include "TowerBase.h"
#include "TowerFactory.h"
#include "BaseTowerLayer.h"
#include "TowerManager.h"

bool BaseTowerLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Layer::init());
        this->initTower();
		bRet = true;
    }
    while (0);
    
    return bRet;
}
void BaseTowerLayer::initTower()
{
    std::vector<Vec2> vec;
    vec.push_back(Vec2(500,20));
    vec.push_back(Vec2(600,20));
    vec.push_back(Vec2(700,20));
    TowerFactory::createTower(en_GreenTower,Vec2(0,0));
    TowerFactory::createTower(en_FireBottleTower,Vec2(0,0));
    TowerFactory::createTower(en_SnowTower,Vec2(0,0));
    int i=0;
    for (auto & toweritem : TowerManager::getInstance()->getTowerVec()){
        toweritem->setPosition(vec[i]);
        toweritem->setState(false);
        i++;
    }
}