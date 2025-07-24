#include "application.h"
#include <iostream>

Application::Application(DeviceDriver* driver) : m_device_driver(driver)
{
}

void Application::readAndPrint(long startAddr, long endAddr) {
	for (long addr = startAddr; addr <= endAddr; ++addr) {
		std::cout << "Addr(" << addr << ") : " << m_device_driver->read(addr) << std::endl;
	}
}

void Application::writeAll(int data) {
	for (long addr = 0x00; addr <= 0x04; ++addr) {
		m_device_driver->write(addr, data);
	}
}
