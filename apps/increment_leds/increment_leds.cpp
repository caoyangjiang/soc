#include "default_address_map_arm.h"
#include "soc_mem_utils.h"

/* This program increments the contents of the red LED parallel port */
int main(void)
{
   volatile unsigned int * LEDR_ptr;   // virtual address pointer to red LEDs

   int fd = -1;               // used to open /dev/mem for access to physical addresses
   void *LW_virtual;          // used to map physical addresses for the light-weight bridge
    
   // Create virtual memory access to the FPGA light-weight bridge
   if ((fd = soc::MemoryUtils::OpenPhysicalMemoryFile()) == -1)
      return (-1);
   if ((LW_virtual = soc::MemoryUtils::MapPhysicalMemory32Bit(fd, LW_BRIDGE_BASE, LW_BRIDGE_SPAN)) == NULL)
      return (-1);

   // Set virtual address pointer to I/O port
   LEDR_ptr = (unsigned int *) (LW_virtual + LEDR_BASE);
    
   // Add 1 to the I/O register
   *LEDR_ptr = *LEDR_ptr + 1;
    
   soc::MemoryUtils::UnmapPhysicalMemory32Bit(LW_virtual, LW_BRIDGE_SPAN);   // release the physical-memory mapping
   soc::MemoryUtils::ClosePhysicalMemoryFile(fd);   // close /dev/mem
   return 0;
}

