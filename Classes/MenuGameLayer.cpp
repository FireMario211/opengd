#include "MenuGameLayer.h"
#include "MenuLayer.h"
#include "GroundLayer.h"
#include "GameToolbox.h"

Scene* MenuGameLayer::scene() {
    auto scene = Scene::create();
    scene->addChild(MenuGameLayer::create());
    return scene;
}

bool MenuGameLayer::init(){
    if (!Layer::init()) return false;

    startPos = Point(0, 105);

    auto dir = Director::getInstance();
    auto winSize = dir->getWinSize();
    
    addChild(GroundLayer::create(1), 2);

    auto playerTest = PlayerObject::create(1, this);
    playerTest->setMainColor(GameToolbox::randomColor3B());
    playerTest->setSecondaryColor(GameToolbox::randomColor3B());
    playerTest->setShipColor(playerTest->getMainColor());
    playerTest->setPosition({-300, 232});
    addChild(playerTest);
    this->player = playerTest;
    
    //auto bg = Sprite::create("game_bg_01_001.png");
    const Texture2D::TexParams texParams = {
        backend::SamplerFilter::LINEAR, 
        backend::SamplerFilter::LINEAR, 
        backend::SamplerAddressMode::REPEAT, 
        backend::SamplerAddressMode::REPEAT
    };

    bgSprites = Menu::create();

    // this->bgSpr = bg;
    // this->bgSpr->getTexture()->setTexParameters(texParams);
    // this->bgSpr->setTextureRect(Rect(0, 0, 2048, 1024));
    // this->bgSpr->setPosition(winSize / 2);

    for(int i = 0; i < 4; i++) {
        auto gr = Sprite::create("game_bg_01_001.png");
        gr->getTexture()->setTexParameters(texParams);
        gr->setTextureRect(Rect(0, 0, 2048, 1024));
        gr->setPosition(winSize / 2);
        auto cl = gr->getColor();
        cl.r = 0;
        cl.g = 102;
        cl.b = 255;
        gr->setColor(cl);
        // bg scale
        gr->setScale(1.185f); // epic hardcore (please fix lmao)
        bsizeX = gr->getContentSize().width;

        this->bgSprites->addChild(gr);
    }
    this->bgSprites->alignItemsHorizontallyWithPadding(0);
    this->bgStartPos = bgSprites->getPositionX();
    this->addChild(bgSprites, -3);
    sep = 0.5f;

    //this is not how it works lol
    //this->bgSpr->setColor(GameToolbox::randomColor3B());

    //this->addChild(this->bgSpr, -1);
    
    // bg->runAction(
    //     RepeatForever::create(
    //         Sequence::create(
    //             TintTo::create(4.0f, {255, 0, 0}),
    //             TintTo::create(4.0f, {255, 255, 0}),
    //             TintTo::create(4.0f, {0, 255, 0}),
    //             TintTo::create(4.0f, {0, 255, 255}),
    //             TintTo::create(4.0f, {0, 0, 255}),
    //             TintTo::create(4.0f, {255, 0, 255}),
    //             TintTo::create(4.0f, {255, 0, 0}),
    //             nullptr
    //         )
    //     )
    // );
    
    scheduleUpdate();
    
    return true;
}
void MenuGameLayer::processPlayerMovement(float delta) {
    if(this->player) {
        if (this->player->getPositionX() == 500.f) {
            // this->player->jump();
        }
        if(this->player->getPositionX() >= 1300.f) {
            player->removeFromParentAndCleanup(true);
            auto playerTest = PlayerObject::create(((rand() * 256) % 14) + 1, this);
            playerTest->setPosition({-300, 232});
            this->player = playerTest;
            playerTest->setMainColor(GameToolbox::randomColor3B());
            playerTest->setSecondaryColor(GameToolbox::randomColor3B());
            playerTest->setShipColor(playerTest->getMainColor());
            addChild(playerTest);
        }
    }
}
void MenuGameLayer::processBackground(float delta) {
    if(this->bgStartPos - bgSprites->getPositionX() < this->bsizeX) 
    {
        bgSprites->setPositionX(bgSprites->getPositionX() - this->sep);
    }
    else 
    {
        bgSprites->setPositionX(bgSprites->getPositionX() + this->bsizeX);
    }
}
void MenuGameLayer::update(float delta) {
    processBackground(delta);
    processPlayerMovement(delta);
}
