//
//  SharedMenu.cpp
//  CarrotFantasy
//
//  Created by Yan on 14-9-30.
//
//

#include "SharedMenu.h"
#include "SoundUtil.h"
#include "PublicSourceDefine.h"
bool SharedMenu::init()
{
    bool bRet = false;
    
    do
    {
        createMenu();
        
        bRet = true;
    }
    while (0);
    return bRet;
}

void SharedMenu::createMenu()
{
    auto tVisibleSize = Director::getInstance()->getVisibleSize();
    auto pBg = Sprite::createWithSpriteFrameName("share_bg.png");
    addChild(pBg);
    pBg->setOpacity(140);
    pBg->setPosition(Vec2(tVisibleSize.width / 2, pBg->getContentSize().height / 2));
    
    auto pTitle = Sprite::createWithSpriteFrameName("share_bg_CN.png");
    addChild(pTitle);
    pTitle->setPosition(Vec2(480, 52));
    
    auto pSinaSharedItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("share_tweibo_normal.png"), Sprite::createWithSpriteFrameName("share_tweibo_press.png"), [](Ref *pSender){
        log("Sina");});
    pSinaSharedItem->setPosition(Vec2(340, 37));
    
    auto pWeChatSharedItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("share_wechat_normal.png"), Sprite::createWithSpriteFrameName("share_wechat_press.png"), [](Ref *pSender){
        log("Weixin");});
    pWeChatSharedItem->setPosition(Vec2(480, 37));
    
    auto pWeiBoSharedItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("share_weibo_normal.png"), Sprite::createWithSpriteFrameName("share_weibo_normal.png"), [](Ref *pSender){
        log("Weibo");});
    pWeiBoSharedItem->setPosition(Vec2(620, 37));
    
    auto pMenu = Menu::create(pSinaSharedItem, pWeChatSharedItem, pWeiBoSharedItem, nullptr);
    addChild(pMenu);
}