//
//  PauseLayer.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-9-21.
//
//

#include "PauseLayer.h"
#include "SceneManager.h"
#include "SharedMenu.h"
#include "SoundUtil.h"
#include "PublicSourceDefine.h"
#include "GameManager.h"

bool PauseLayer::init()
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Layer::init());
        
        auto pBlackLayer = LayerColor::create(Color4B(0, 0, 0, 170));
        
        addChild(pBlackLayer);
        
        createMenu();
        
        createSharedMenu();
        
        closeTouchEvent();
        
        bRet = true;
    }
    while (0);
    
    return bRet;

}


void PauseLayer::createMenu()
{
    auto pMenuBg = Sprite::createWithSpriteFrameName("menu_bg.png");
    pMenuBg->setPosition(VisibleRect::center());
    addChild(pMenuBg);
    
    MenuItemSprite *pBtnResume = MenuItemSprite::create(
                                                        Sprite::createWithSpriteFrameName("menu_resume_normal_CN.png"), Sprite::createWithSpriteFrameName("menu_resume_pressed_CN.png"),[this](Ref *pSender)
                                                        {
                                                            _funcFlagPauseLayerIsClose();
                                                            removeFromParentAndCleanup(true);
                                                        }
                                                        );
    pBtnResume->setPosition(Vec2(481,417));
    
    MenuItemSprite *pBtnRstart = MenuItemSprite::create(
                                                        Sprite::createWithSpriteFrameName("menu_restart_normal_CN.png"), Sprite::createWithSpriteFrameName("menu_restart_pressed_CN.png"),[this](Ref *pSender)
                                                        {
                                                            auto enGameScene = std::make_tuple(en_GameScene,SceneManager::getInstance()->getCurLevelIndex());
                                                            NOTIFY->postNotification("changeScene",reinterpret_cast<Ref *>(&enGameScene));
                                                            
                                                        }
                                                        );
    pBtnRstart->setPosition(Vec2(481,322));
    
    MenuItemSprite *pBtnSelectLevel = MenuItemSprite::create(
                                                             Sprite::createWithSpriteFrameName("menu_quit_normal_CN.png"), Sprite::createWithSpriteFrameName("menu_quit_pressed_CN.png"),[this](Ref *pSender)
                                                             {
                                                                 auto enLevelSelectScene = std::make_tuple(en_LevelSelectScene,SceneManager::getInstance()->getCurPageIndex());
                                                                 NOTIFY->postNotification("changeScene",reinterpret_cast<Ref *>(&enLevelSelectScene));
                                                                 
                                                             }
                                                             );
    pBtnSelectLevel->setPosition(Vec2(481,227));
    
    Menu *pMenu = Menu::create(pBtnResume,pBtnRstart,pBtnSelectLevel,nullptr);
    pMenu->setPosition(Vec2::ZERO);
    addChild(pMenu,1);

}

void PauseLayer::createSharedMenu()
{
    addChild(SharedMenu::create(), 1);
}

void PauseLayer::setFuncFlagPauseLayerIsClose(const std::function<void ()> &rFuncFlagPauseLayerIsClose)
{
    _funcFlagPauseLayerIsClose = rFuncFlagPauseLayerIsClose;
}


void PauseLayer::closeTouchEvent()
{
    auto pListener = EventListenerTouchOneByOne::create();
    
    pListener->onTouchBegan = [](Touch *pTouch, Event *pEvent)
    {
        return true;
    };
    pListener->setSwallowTouches(true);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pListener, this);
}

void PauseLayer::onEnter()
{
    Layer::onEnter();
    Director::getInstance()->pause();
}

void PauseLayer::onExit()
{
    if(!GameManager::getInstance()->getIsPause()) Director::getInstance()->resume();
    Layer::onExit();
}






