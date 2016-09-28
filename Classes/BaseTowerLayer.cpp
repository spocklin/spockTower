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
    TowerFactory::createTower(en_RocketTower,Vec2(100,100));
    TowerFactory::createTower(en_FireBottleTower,Vec2(100,100));
    TowerFactory::createTower(en_SnowTower,Vec2(100,100));
    for (auto & toweritem : TowerManager::getInstance()->getTowerVec()){
        toweritem->setPosition(Vec2(100,300));
        log("======towermanagerhave");
    }
}