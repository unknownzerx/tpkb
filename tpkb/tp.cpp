#include <cstdio>
#include <cstring>
#include <cstdint>

#include "hidapi.h"

int main()
{
    const uint16_t vendor_id = 0x17EF;
    const uint16_t product_ids[] = {0x6048, 0x60E1};
    
    if (hid_init()) {
        return -1;
    }
    
    hid_device *dev = 0;
    for (int i = 0; i < sizeof(product_ids)/sizeof(uint16_t); ++i) {
        dev = hid_open(vendor_id, product_ids[i], NULL);
        if (dev != 0) {
            break;
        }
    }
    
    if (dev == 0) {
        printf("TP Keyboard not found. Possible solutions:\n"
               " * Have you run tpkb with 'sudo'?\n"
               " * Make sure you don't have keyboard customizers running (for example Karabiner)\n");

        //Debug support
        printf("Detected devices:\n");
        hid_device_info *devs = hid_enumerate(0,0);
        for (;devs; devs = devs->next) {
            printf("VID: 0x%04X\tPID: 0x%04X\tManufacturer: %ls\n", 
                devs->vendor_id, 
                devs->product_id, 
                devs->manufacturer_string);
        }    
        hid_free_enumeration(devs);
        devs = NULL;
       
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
