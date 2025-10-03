static inline void cpuid(unsigned int code, unsigned int* a, unsigned int* d, unsigned int* c, unsigned int* b) {
    asm volatile("cpuid"
            : "=a"(*a), "=d"(*d), "=c"(*c), "=b"(*b)
            : "a"(code));
}

int get_cores() {
    unsigned int eax, ebx, ecx, edx;
    cpuid(1, &eax, &edx, &ecx, &ebx);
    return (ebx >> 16) & 0xFF;
}