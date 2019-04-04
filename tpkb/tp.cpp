#include <cstdio>
#include <cstring>
#include <cstdint>

#include "hidapi.h"

int main()
{
    const uint16_t vendor_id = 0x17EF;
    const uint16_t product_id = 0x6048;
    
    if (hid_init()) {
        return -1;
    }
    
    hid_device *dev = hid_open(vendor_id, product_id, 0);
    
    if (dev == 0) {
        printf("TP Keyboard not found. Possible solutions:\n"
               " * Have you run tpkb with 'sudo'?\n"
               " * Make sure you don't have keyboard customizers running (for example Karabiner)\n");
        return 0;
    }
    
    unsigned char buf[4];
    
    // Fn lock ON
    buf[0] = 0x18;
    buf[1] = 0x05;
    buf[2] = 0x01;
    hid_write(dev, buf, 3);
    
    // Middle button
    buf[0] = 0x18;
    buf[1] = 0x09;
    buf[2] = 0x00;
    hid_write(dev, buf, 3);
    
    hid_close(dev);
    return 0;
}
