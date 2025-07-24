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

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}