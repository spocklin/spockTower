//
//  MonsterManager.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-9-13.
//
//

#include "MonsterManager.h"
#include "MonsterBase.h"
#include "GameManager.h"

MonsterManager *MonsterManager::_gInstance;

MonsterManager::MonsterManager()
{
}

void MonsterManager::clearBeAtkLockState()
{
    for(auto &iterMonster : *_pMonsterVec)
    {
        iterMonster->setAtkTarget(false);
    }
}

MonsterManager::~MonsterManager()
{
    CC_SAFE_DELETE(_pMonsterVec);
}

bool MonsterManager::init()
{
    bool bRet = false;
    do
    {
        _pMonsterVec = new Vector<MonsterBase *>;
        registerDeadEvent();
        bRet = true;
    }
    while (0);
    
    return bRet;
}

Vector<MonsterBase*> &MonsterManager::getMonsterVec()
{
    return *_pMonsterVec;
}

void MonsterManager::addMonster(MonsterBase *pMonster)
{
    if(_pMonsterVec) _pMonsterVec->pushBack(pMonster);
    _funcAddMonsterToLayer(pMonster);
}

void MonsterManager::setFuncAddMonsterToLayer(const std::function<void (Entity*)> &rFuncAddMonsterToLayer)
{
    _funcAddMonsterToLayer = rFuncAddMonsterToLayer;
}

void MonsterManager::registerDeadEvent()
{
    NOTIFY->addObserver(this, callfuncO_selector(MonsterManager::removeMonsterFromManager), "MonsterDead", nullptr);
    NOTIFY->addObserver(this, callfuncO_selector(MonsterManager::openCheckGameEnd), "openCheckGameEnd", nullptr);
}

void MonsterManager::removeMonsterFromManager(Ref *pMonster)
{
    if(!(_pMonsterVec && _pMonsterVec->size())) return;
    _pMonsterVec->eraseObject(reinterpret_cast<MonsterBase*>(pMonster));
    
    if(_bIsOpenCheckGameEnd)
    {
        if(!_pMonsterVec->size())
        {
            auto tEnGameWin = en_GameWin;
            if(GameManager::getInstance()->getICarrotHp() >= 1) NOTIFY->postNotification("gameEnd", reinterpret_cast<Ref*>(&tEnGameWin));
            _bIsOpenCheckGameEnd = false;
        }
    }
}

void MonsterManager::clearManager()
{
    _pMonsterVec->clear();
}

void MonsterManager::openCheckGameEnd(cocos2d::Ref *pSender)
{
    _bIsOpenCheckGameEnd = true;
}







