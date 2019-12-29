#include <unistd.h>

namespace soc {
class MemoryUtils{
public:
	static int OpenPhysicalMemoryFile();
	static void ClosePhysicalMemoryFile(int file_desc);

	static void* MapPhysicalMemory32Bit(int file_desc, unsigned int starting_addr, unsigned int range);
	static int UnmapPhysicalMemory32Bit(void *, unsigned int);
};
}

