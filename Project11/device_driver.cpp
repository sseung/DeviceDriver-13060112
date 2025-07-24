#include "device_driver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    int result = (int)(m_hardware->read(address));  // 1st read
    for (int i = 1; i < 5; ++i) {                   // additionl 4 times of read
        int current = (int)(m_hardware->read(address));
        if (current != result) {
            throw ReadFailException();
        }
    }
    return result;
}

void DeviceDriver::write(long address, int data)
{
    if ((int)(m_hardware->read(address) != 0xFF)) {
        throw WriteFailException();
    }
    m_hardware->write(address, (unsigned char)data);
}
