#pragma once
#include <string>
#include <functional>

namespace Hid {
    void setDevice(const std::string& dev);
    void setErrorCallback(std::function<void()> cb);
    bool sendToHidrawPins(const std::string& macro_body);
}
