//
//  GameEndLayer.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-9-30.
//
//

#include "GameEndLayer.h"
#include "SharedMenu.h"
#include "LevelConfigUtil.h"
#include "NumSprite.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "SoundUtil.h"
#include "LocalDataUtil.h"
#include "MapUtil.h"

GameEndLayer *GameEndLayer::create(const GameEndType &rEnGameEndType)
{
    auto pGameEndLayer = new GameEndLayer();
    
    if(!(pGameEndLayer && pGameEndLayer->init(rEnGameEndType))) CC_SAFE_DELETE(pGameEndLayer);
    
    return pGameEndLayer;
}

bool GameEndLayer::init(const GameEndType &rEnGameEndType)
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Layer::init());
        
        auto pBlackLayer = LayerColor::create(Color4B(0, 0, 0, 130));
        
        addChild(pBlackLayer);
        
        _enGameEndType = rEnGameEndType;
        
        createMenu();
                
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void GameEndLayer::saveLevelData()
{
    if(en_GameWin != _enGameEndType) return;
    
    auto tCurLevelIndex = SceneManager::getInstance()->getCurLevelIndex() + 1;
        
    auto tCurPageIndex = SceneManager::getInstance()->getCurPageIndex() + 1;
    
    auto tLevelData = std::make_tuple(0, _iCarrotType, tCurPageIndex, tCurLevelIndex);
    NOTIFY->postNotification(LEVELDATACHANGE, reinterpret_cast<Ref*>(&tLevelData));
    
    if(tCurLevelIndex == 12)
    {
        ++tCurPageIndex;
        tCurLevelIndex = 0;
    }
    
    auto tNextLevelData = std::make_tuple(0, 1, tCurPageIndex, tCurLevelIndex + 1);
    NOTIFY->postNotification(LEVELDATACHANGE, reinterpret_cast<Ref*>(&tNextLevelData));
}


void GameEndLayer::createMenu()
{
    auto pBg = Sprite::createWithSpriteFrameName(std::get<0>(GAMEENDSOURCE[_enGameEndType]));
    pBg->setPosition(Vec2(VisibleRect::center()));
    addChild(pBg);
    
    auto pTitle = Sprite::createWithSpriteFrameName(GAMEENDTITLE);
    addChild(pTitle);
    pTitle->setPosition(Vec2(VisibleRect::center()));
    
    auto pChooseLevelItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName(CHOOSESOURCE[0]), Sprite::createWithSpriteFrameName(CHOOSESOURCE[1]), [](Ref *pSender)
    {
        auto enLevelSelectScene = std::make_tuple(en_LevelSelectScene,SceneManager::getInstance()->getCurPageIndex());
        NOTIFY->postNotification("changeScene",reinterpret_cast<Ref *>(&enLevelSelectScene));
    });
    pChooseLevelItem->setPosition(Vec2(367, 220));
    
    auto pAgainItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName(std::get<1>(GAMEENDSOURCE[_enGameEndType])), Sprite::createWithSpriteFrameName(std::get<2>(GAMEENDSOURCE[_enGameEndType])), [&](Ref *pSender)
    {
        auto tCurLevelIndex = SceneManager::getInstance()->getCurLevelIndex();
        std::tuple<SceneType, int> tEnGameScene;
        if(en_GameLose == _enGameEndType) tEnGameScene = std::make_tuple(en_GameScene, tCurLevelIndex);
        else tEnGameScene = std::make_tuple(en_GameScene, tCurLevelIndex + 1);
        NOTIFY->postNotification("changeScene",reinterpret_cast<Ref *>(&tEnGameScene));
    });
    pAgainItem->setPosition(Vec2(600, 220));
    
    auto pMenu = Menu::create(pChooseLevelItem, pAgainItem, nullptr);
    addChild(pMenu);
    
    addChild(SharedMenu::create());
}

void GameEndLayer::loadInfo()
{
    auto pMonsterBatchNode = NumSprite::createNum(StringUtils::format("%02d", LevelConfigUtil::getInstance()->getCurLevelMonsterBatchCount()), MONEYNUMIMAGE);
    pMonsterBatchNode->setPosition(Vec2(563, 350));
    addChild(pMonsterBatchNode);

    auto tMonsterBatchCount = GameManager::getInstance()->getIMonsterBatch();
    if(en_GameLose == _enGameEndType) --tMonsterBatchCount;
        
    auto pCurMonsterBatchNode = NumSprite::createNum(StringUtils::format("%02d", tMonsterBatchCount), MONSTERBATCHIMAGE);
    pCurMonsterBatchNode->setPosition(Vec2(465, 350));
    addChild(pCurMonsterBatchNode);
    
    auto pCurLevelNode = NumSprite::createNum(StringUtils::format("%02d", SceneManager::getInstance()->getCurLevelIndex() + 1), LITTLENUMIMAGE);
    pCurLevelNode->setPosition(Vec2(415, 290));
    addChild(pCurLevelNode);
    
    checkCarrotType();
}

void GameEndLayer::checkCarrotType()
{
    auto tCarrotHp = GameManager::getInstance()->getICarrotHp();
    
    if(GOLDCARROTHP == tCarrotHp)
    {
        _sCarrotType = GOLDCARROT;
        _iCarrotType = 4;
    }
    
    if(tCarrotHp > SILVERCARROTHP1 && tCarrotHp <= SILVERCARROTHP2)
    {
        _sCarrotType = SILVERCARROT;
        _iCarrotType = 3;
    }
    if(tCarrotHp > 0 && tCarrotHp <= SILVERCARROTHP1)
    {
        _sCarrotType = NORMALCARROT;
        _iCarrotType = 2;
    }
    
    if(_sCarrotType.size())
    {
//        auto pGameWinParticle = ParticleSystemQuad::create("loading/test.plist");
//        auto pBatch = ParticleBatchNode::createWithTexture(pGameWinParticle->getTexture());
//        pBatch->addChild(pGameWinParticle);
//        addChild(pBatch, 19);
        
        auto pCarrotMedal = Sprite::createWithSpriteFrameName(_sCarrotType);
        pCarrotMedal->setPosition(485, 455);
        addChild(pCarrotMedal, 20);
    }

}

void GameEndLayer::onExit()
{
    Director::getInstance()->resume();
    Layer::onExit();
}

void GameEndLayer::onEnter()
{
    Layer::onEnter();
    registerNoTouch();
    loadInfo();
    saveLevelData();
    Director::getInstance()->pause();
    playGameEndSound();
}

void GameEndLayer::playGameEndSound()
{
    if(en_GameLose == _enGameEndType) SoundUtil::getInstance()->playEffect(GAMELOSE);
    else SoundUtil::getInstance()->playEffect(GAMEWIN);
}

void GameEndLayer::registerNoTouch()
{
    auto pListener = EventListenerTouchOneByOne::create();
    
    pListener->setSwallowTouches(true);
    pListener->onTouchBegan = [](Touch *pTouch, Event *pEvent){return true;};
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pListener, this);
}



