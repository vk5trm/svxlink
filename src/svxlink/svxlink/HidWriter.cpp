#include "HidWriter.h"
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cerrno>
#include <cstring>

namespace Hid {

static std::string g_device = "/dev/hidraw0";
static std::function<void()> g_errorCallback = nullptr;

void setDevice(const std::string& dev) {
    if (!dev.empty()) g_device = dev;
}

void setErrorCallback(std::function<void()> cb) {
    g_errorCallback = std::move(cb);
}

bool sendToHidrawPins(const std::string& macro_body) {
    char *endptr = nullptr;
    long value = std::strtol(macro_body.c_str(), &endptr, 10);

    if (*endptr != '\0' || value < 0 || value > 16) {
        std::cerr << "*** ERROR: Invalid HID macro (must be 0–16 decimal): "
                  << macro_body << std::endl;
        if (g_errorCallback) g_errorCallback();
        return false;
    }

    uint16_t mask = static_cast<uint16_t>(value);

    uint8_t report[2] = {
        static_cast<uint8_t>(mask & 0x00FF),
        static_cast<uint8_t>((mask >> 8) & 0x00FF)
    };

    int fd = open(g_device.c_str(), O_WRONLY | O_CLOEXEC);
    if (fd < 0) {
        std::cerr << "*** ERROR: Cannot open HID device " << g_device << std::endl;
        if (g_errorCallback) g_errorCallback();
        return false;
    }

    ssize_t n = write(fd, report, sizeof(report));
    int savedErrno = (n < 0) ? errno : 0;
    close(fd);

    if (n != sizeof(report)) {
        std::cerr << "*** ERROR: HID write failed";
        if (savedErrno) std::cerr << ": " << strerror(savedErrno);
        std::cerr << std::endl;
        if (g_errorCallback) g_errorCallback();
        return false;
    }

    return true;
}

} // namespace Hid
