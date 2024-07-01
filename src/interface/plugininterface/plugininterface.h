#ifndef PLUGININTERFACE__H__
#define PLUGININTERFACE__H__

class PluginInterFace
{
public:
    //虚析构，保障内存上先释放子类
    virtual ~PluginInterFace(){};

    virtual void getname() = 0;

};

#endif
