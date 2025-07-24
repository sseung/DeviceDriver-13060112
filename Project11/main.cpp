#include "gmock/gmock.h"
#include "device_driver.h"

using namespace testing;

class MockFlashMemory : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriver, ReadFromHW) {
	MockFlashMemory mockHardware;
	DeviceDriver driver{ &mockHardware };

	EXPECT_CALL(mockHardware, read(_))
		.Times(5);

	int data = driver.read(0xFF);
}

TEST(DeviceDriver, WriteToHWNormal) {
    MockFlashMemory mockHardware;
    DeviceDriver driver{ &mockHardware };

    EXPECT_CALL(mockHardware, read(_))
        .Times(5)
        .WillRepeatedly(Return(0xFF));  // none value

    EXPECT_CALL(mockHardware, write(_, _))
        .Times(1);

    driver.write(0xFF, 1);
}

TEST(DeviceDriver, WriteToHWAbnormal) {
    MockFlashMemory mockHardware;
    DeviceDriver driver{ &mockHardware };

    EXPECT_CALL(mockHardware, read(_))
        .Times(5)
        .WillRepeatedly(Return(0x01));  // already existing value

    EXPECT_THROW(driver.write(0xFF, 1), WriteFailException);
}


int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}