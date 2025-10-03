#include "../../../include/kernel/system/sysinfo.h"
#include "../../../include/kernel/cpu/cpu.h"
#include "../../../include/kernel/stdlib/stdmem.h"

sysinfo* get_sysinfo() {
    sysinfo* sysinfo = (sysinfo*)std_malloc(sizeof(sysinfo));
    sysinfo->cores = get_cores();
}