#include <Windows.h>
#include <iostream>
#include <string>
#include <random>

enum class LogitechSerialType {
    Device, // ends with '8'
    Box     // ends with '9'
};

std::string RandomStr(
    std::size_t length = 10,
    LogitechSerialType type = LogitechSerialType::Device)
{
    if (length < 8) length = 8;
    if (length > 11) length = 11;

    static constexpr char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    static thread_local std::mt19937 engine{ std::random_device{}() };
    std::uniform_int_distribution<std::size_t> dist(0, sizeof(charset) - 2);

    std::string serial;
    serial.reserve(length);

    // generate all but last character
    for (std::size_t i = 0; i < length - 1; ++i)
        serial += charset[dist(engine)];

    // enforce ending digit convention
    serial += (type == LogitechSerialType::Device) ? '8' : '9';

    return serial;
}

#include "./Makcu/include/makcu.h"
makcu::Device device;

//void mouseButtonCallback(makcu::MouseButton button, bool isPressed) {
//    //std::string buttonName = makcu::mouseButtonToString(button);
//    //std::string state = isPressed ? "PRESSED" : "RELEASED";
//    //std::cout << "Button " << buttonName << " " << state << std::endl;
//}
//void connectionCallback(bool connected) {
//    //std::cout << "Device " << (connected ? "CONNECTED" : "DISCONNECTED") << std::endl;
//}

bool InitMakcu()
{
    auto devices = makcu::Device::findDevices();
    if (devices.empty())
    {
        std::cout << ("\n (!) Makcu is not connected. Connect your device and try again.") << std::endl;
        return false;
    }
    else
    {
        // initializing makcu
        if (!device.connect(devices[0].port))
        {
            std::cout << ("\n (!) Failed to connect to your makcu.") << std::endl;
            return false;
        }
        else
        {
            // High performance
            device.enableHighPerformanceMode(true);
            makcu::PerformanceProfiler::enableProfiling(true);

            // Set up callbacks
            device.setMouseButtonCallback(nullptr);
            device.setConnectionCallback(nullptr);
        }

        std::cout << ("\n (+) Makcu initialized.") << std::endl;
        return true;
    }

    return false;
}
int main()
{
    SetWindowTextA(GetConsoleWindow(), "Makcu Mouse Serial Changer. Made With <3 by Mhatt");

    if (InitMakcu())
    {
        // storing and printing current/old serial
        std::string CurrentSerial = device.getMouseSerial();
        std::cout << "\n (-) Current Mouse Serial: " << CurrentSerial << std::endl;

        // asking input from user to determinate serial lenght to avoid weird ah serials
        int lenght = 11;
        std::cout << "\n (.) Type the desidered serial lenght. BETWEEN 8-11, TYPE 0 TO RESET THE SERIAL\n (.) lenght: ";
        std::cin >> lenght;

        // reset serial
        if (lenght == 0)
        {
            // check if the function fails
            if (!device.resetMouseSerial())
                std::cout << "\n (!) Failed to reset the mouse serial." << std::endl;
            else
                std::cout << "\n (+) Successfully resetted your mouse serial <3" << std::endl;

            // early exit cuz we dont need to spoof it
            std::cout << "\n (x) Exiting..." << std::endl;
            Sleep(3000);
            return 0;
        }

        // spoofing the serial
        std::string NewSerial = RandomStr(lenght);
        std::cout << "\n ciao: " << NewSerial;
        bool s = device.setMouseSerial(NewSerial);

        // wait a bit for makcu to change it then get a copy of the new serial
        Sleep(200);
        std::string c = device.getMouseSerial();

        // check if "device.setMouseSerial" failed and if the serial is different from the old one
        if (!s || c == CurrentSerial)
            std::cout << "\n (!) Failed to set the mouse serial." << std::endl;
        else
            std::cout << "\n (+) Successfully changed your mouse serial <3\n (-) New Mouse Serial: " << c << std::endl;
    }

    // exit
    std::cout << "\n (x) Exiting..." << std::endl;
    Sleep(3000);
    return 0;
}