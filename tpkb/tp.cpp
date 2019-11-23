#include <cstdio>
#include <cstring>
#include <cstdint>
#include <sys/ioctl.h>

#include "hidapi.h"

int main()
{
    int r;
    const uint16_t vendor_id = 0x046d;

    // TWEAK ME
    // const uint16_t product_id = 0xb330;
    // const uint16_t product_id = 0xb33c;
    const uint16_t product_id = 0xb33d;
    
    if (hid_init() == -1) {
        printf("failed at hid_init()\n");
        return -1;
    }
    
    hid_device *dev = hid_open(vendor_id, product_id, 0);

    
    if (dev == 0) {
        printf("K480 Keyboard not found. Have you run it with 'sudo'?\n");
        return 0;
    }

    // TWEAK ME
    //const char k480_seq_fkeys_on[]  = {0x10, 0xff, 0x08, 0x1c, 0x00, 0x00, 0x00};
    const unsigned char k480_seq_fkeys_on[]  = {0x10, 0xff, 0x0b, 0x1c, 0x00, 0x00, 0x00};
    // code from https://github.com/FSpark/k480_conf/blob/master/k480_conf.c

    r = hid_write(dev, k480_seq_fkeys_on, sizeof(k480_seq_fkeys_on));
    if (r == -1) {
        printf("failed at hid_write() for fn-lock\n");
        return -1;
    }
    
    hid_close(dev);
    return 0;
}
