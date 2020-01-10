#include <stdio.h>
#include <stdlib.h>

#include "physical.h"
#include "address_map_arm.h"

typedef unsigned char uint8_t;
typedef unsigned int  uint32_t;

void ApplySegCodeToHexDisplays(uint32_t* hex_addr_0, uint32_t* hex_addr_1, uint8_t hex[6])
{

    *hex_addr_0 = hex[3] << 24 | hex[2] << 16 | hex[1] << 8 | hex[0];
    *hex_addr_1 = hex[5] << 8  | hex[4];
}

int main()
{
    printf("Start loop");

    int fd = -1;
    fd = open_physical(fd);

    if(fd==-1)
    {
        printf("Open physical memory failed.");
        return -1;
    }

    // map to virtual memory
    void* virtual_addr = map_physical(fd, LW_BRIDGE_BASE, LW_BRIDGE_SPAN);

    void* hex_addr_0 = virtual_addr + HEX3_HEX0_BASE;
    void* hex_addr_1 = virtual_addr + HEX5_HEX4_BASE;
    void* push_key_base_addr = virtual_addr + KEY_BASE;
    uint32_t* push_key_ec_addr = push_key_base_addr + 0x0C;

    uint8_t words[] = {0x39, 0x76, 0x79, 0x38, 0x6D, 0x79, 0x77, 0, 0x07, 0x06, 0x77, 0x37, 0x6F, 0, 0, 0, 0, 0, 0};
    uint8_t display[6] = {0,0,0,0,0,0};

    int i = 0;
    int enabled = 0;
    while(1)
    {
        usleep(200000);

        if((*push_key_ec_addr & 0x01) != 0)
        {
            enabled = enabled == 0 ? 1 : 0;
            *push_key_ec_addr |= 0x01;
        }

        if(enabled > 0) {
            display[5] = display[4];
            display[4] = display[3];
            display[3] = display[2];
            display[2] = display[1];
            display[1] = display[0];
            display[0] = words[i];
            i = (i == sizeof(words)-1) ? 0 : i + 1;
            ApplySegCodeToHexDisplays(hex_addr_0, hex_addr_1, display);
        }
    }

    // unmap the mapped virtual memory
    int ret = unmap_physical(virtual_addr, LW_BRIDGE_SPAN);
    if(ret == -1)
    {
        printf("Unmap physical memory failed.");
    }
    close_physical(fd);
    return 0;
}
