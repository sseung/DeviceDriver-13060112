#include "gmock/gmock.h"
#include "device_driver.h"
#include "application.h"

using namespace testing;

class MockFlashMemory : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class MockDeviceDriver : public DeviceDriver {
public:
    MockDeviceDriver(FlashMemoryDevice* hardware) : DeviceDriver(hardware) {}

    MOCK_METHOD(int, read, (long address), (override));
    MOCK_METHOD(void, write, (long address, int data), (override));
};

TEST(DeviceDriver, ReadFromHW) {
	MockFlashMemory mockHardware;
	DeviceDriver driver{ &mockHardware };

	EXPECT_CALL(mockHardware, read(_))
		.Times(5);

	int data = driver.read(0xFF);
}

TEST(DeviceDriver, ReadFromHWAbnormal) {
    MockFlashMemory mockHardware;
    DeviceDriver driver{ &mockHardware };

    EXPECT_CALL(mockHardware, read(_))
        .WillOnce(Return(0xA))
        .WillOnce(Return(0xA))
        .WillOnce(Return(0xA))
        .WillOnce(Return(0xA))
        .WillOnce(Return(0xB));

    EXPECT_THROW(driver.read(0xFF), ReadFailException);
}

TEST(DeviceDriver, WriteToHWNormal) {
    MockFlashMemory mockHardware;
    DeviceDriver driver{ &mockHardware };

    EXPECT_CALL(mockHardware, read(_))
        .Times(1)
        .WillRepeatedly(Return(0xFF));  // none value

    EXPECT_CALL(mockHardware, write(_, _))
        .Times(1);

    driver.write(0xFF, 1);
}

TEST(DeviceDriver, WriteToHWAbnormal) {
    MockFlashMemory mockHardware;
    DeviceDriver driver{ &mockHardware };

    EXPECT_CALL(mockHardware, read(_))
        .Times(1)
        .WillRepeatedly(Return(0x01));  // already existing value

    EXPECT_THROW(driver.write(0xFF, 1), WriteFailException);
}

TEST(Application, readAndPrint) {
    MockFlashMemory mockHardware;
    MockDeviceDriver mockDriver{ &mockHardware };
    Application application{ &mockDriver };

    EXPECT_CALL(mockDriver, read(_))
        .Times(5);

    application.readAndPrint(0x00, 0x04);
}

TEST(Application, writeAll) {
    MockFlashMemory mockHardware;
    MockDeviceDriver mockDriver{ &mockHardware };
    Application application{ &mockDriver };

    EXPECT_CALL(mockDriver, write(_, _))
        .Times(5);

    application.writeAll(0x01);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}