#pragma once
#include "device_driver.h"

class Application
{
public:
    Application(DeviceDriver* driver);
    void readAndPrint(long startAddr, long endAddr);
    void writeAll(int data);

protected:
    DeviceDriver* m_device_driver;
};
