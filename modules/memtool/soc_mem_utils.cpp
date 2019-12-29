#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>

#include "soc_mem_utils.h"

namespace soc {

int MemoryUtils::OpenPhysicalMemoryFile()
{
	int fd = open( "/dev/mem", (O_RDWR | O_SYNC));
	return fd;
}

void MemoryUtils::ClosePhysicalMemoryFile(int fd)
{
	close (fd);
}

void* MemoryUtils::MapPhysicalMemory32Bit(int fd, unsigned int base, unsigned int span)
{
	void *virtual_base = mmap (NULL, span, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, base);
   	if (virtual_base == MAP_FAILED)
   	{
      		close (fd);
		virtual_base = NULL;
   	}
   	
	return virtual_base;
}

int MemoryUtils::UnmapPhysicalMemory32Bit(void * virtual_base, unsigned int span)
{
	if (munmap(virtual_base, span) != 0)
	{
		return -1;
	}

	return 0;
}

}
