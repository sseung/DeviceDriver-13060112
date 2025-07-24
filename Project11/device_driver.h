#pragma once
#include "flash_memory_device.h"
#include <stdexcept>

class ReadFailException : public std::exception {

};

class WriteFailException : public std::exception {

};

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    virtual int read(long address);
    virtual void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
};
