#include <string.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

void property_override(char const prop[], char const value[], bool add = false) {
    auto pi = (prop_info *) __system_property_find(prop);

    if (pi != nullptr) {
        __system_property_del(prop);
        __system_property_add(prop, strlen(prop), value, strlen(value));
    } else if (add) {
        __system_property_add(prop, strlen(prop), value, strlen(value));
    }
}

int main(int argc, char *argv[]) {
    if (__system_properties_init()) {
        return -1;
    }

    // Default to root shell
    property_override("ro.secure", "0");

    // Disable ADB auth
    property_override("ro.adb.secure", "0");

    // Enable ADB
    property_override("ro.force.debuggable", "1");

    return 0;
}
