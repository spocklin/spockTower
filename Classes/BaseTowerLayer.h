//界面上的默认塔选择层

#ifndef __aStar__BaseTowerLayer__
#define __aStar__BaseTowerLayer__

class BaseTowerLayer:public Layer
{
public:
    CREATE_FUNC(BaseTowerLayer);
protected:
    virtual bool init();
    virtual void initTower();
};

#endif
