#ifndef ADMINCONTROLLER_H
#define ADMINCONTROLLER_H


class AdminController
{
public:
    AdminController();
    void createStateList();
    void shutDown();
    void setParam(int warmCool, int defaultDegree, int feeRate);
private:
    //Master_mach类
};

#endif // ADMINCONTROLLER_H
