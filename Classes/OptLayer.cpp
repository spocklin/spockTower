
#include "OptLayer.h"
#include "MapUtil.h"
#include "TowerManager.h"
#include "BarrierBase.h"
#include "BarrierManager.h"
#include "TowerOptBtn.h"
#include "TowerBase.h"
#include "MonsterManager.h"
#include "MonsterBase.h"
#include "SoundUtil.h"
#include "Carrot.h"
#include "GameScene.h"

bool OptLayer::init()
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Layer::init());
		towerOptBtn = TowerOptBtn::create();
		towerOptBtn->setName("towerOptBtn");
		towerOptBtn->setTag(0);
		_pforbiddenSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("forbidden.png"));
		_pforbiddenSp->setVisible(false);
		addChild(_pforbiddenSp);
		addChild(towerOptBtn);
		listener();
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void OptLayer::listener()
{
	auto listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan = [=](Touch* t, Event* e){
        startPoint = t->getLocation();
        
        if(startPoint.y > 590) return true;
		if (towerOptBtn->getTag()){
			towerOptBtn->setTag(0);
			towerOptBtn->hideTowerOpt();
		}else{
			Carrot* carrot = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene())->getCarrot();
			if (carrot->getBoundingBox().containsPoint(startPoint)){
				return true;
			}
			for (auto & toweritem : TowerManager::getInstance()->getTowerVec()){
				if (toweritem->getBoundingBox().containsPoint(startPoint)){
					towerOptBtn->setTag(1);
					towerOptBtn->setPosition(toweritem->getPosition());
					towerOptBtn->showTowerOpt();
					towerOptBtn->gradeTowerMenu(toweritem);
					return true;
				}
			}
			for (auto & blankitem : MapUtil::getInstance()->getEffectTowerPoses()){
				if (blankitem.containsPoint(startPoint)){
					towerOptBtn->setTag(1);
					towerOptBtn->setPosition(blankitem.origin + blankitem.size/2);
					towerOptBtn->showTowerOpt();
					towerOptBtn->showCreateMenu();
                    return true;
				}
                
			}
			auto tMonsterVec = MonsterManager::getInstance()->getMonsterVec();
			for (auto & monsterIter : tMonsterVec)
			{
				if (monsterIter->getBoundingBox().containsPoint(startPoint))
				{
					auto tMonsterLockFlag = monsterIter->getAtkTarget();
					BarrierManager::getInstance()->clearBeAtkLockState();
					MonsterManager::getInstance()->clearBeAtkLockState();
					monsterIter->setAtkTarget(!tMonsterLockFlag);
					return true;
				}
			}
			auto tBarrierVec = BarrierManager::getInstance()->getBarrierVec();
			for (auto & barrierItem : tBarrierVec)
			{
				if (barrierItem->getBoundingBox().containsPoint(startPoint))
				{
					auto tBarrierLockFlag = barrierItem->getAtkTarget();
					MonsterManager::getInstance()->clearBeAtkLockState();
					BarrierManager::getInstance()->clearBeAtkLockState();
					barrierItem->setAtkTarget(!tBarrierLockFlag);
					return true;
				}
			}
            SoundUtil::getInstance()->playEffect(SELECTFAULT);
			_pforbiddenSp->setVisible(true);
			_pforbiddenSp->runAction(Sequence::create(FadeIn::create(0.1), FadeOut::create(1), NULL));
			_pforbiddenSp->setPosition(startPoint);
		}
		return true;
	};
	listen->onTouchEnded = [=](Touch* x, Event* e){
		endPoint = x->getLocation();
        log("========endx,eny[%f][%f]",endPoint.x,endPoint.y);
		for (auto & toweritem : TowerManager::getInstance()->getTowerVec()){
			if (toweritem->getBoundingBox().containsPoint(startPoint)){
				for (auto & blankitem : MapUtil::getInstance()->getEffectTowerPoses()){
					if (blankitem.containsPoint(endPoint)){
						towerOptBtn->setPosition(blankitem.origin + blankitem.size/2);
						toweritem->setPosition(blankitem.origin + blankitem.size/2);
					}
                }
			}
		}
    };
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, this);
}
