#include <iostream>
#include <cpuid.h>
#include <iostream>
#include <fstream>
#include <string>

bool isSSE42Supported() {
    unsigned int eax, ebx, ecx, edx;
    if (__get_cpuid(1, &eax, &ebx, &ecx, &edx)) {
        return (ecx & (1 << 20)) != 0; // Checking for SSE4.2 support
    }
    return false;
}

bool isAVX2Supported() {
    unsigned int eax, ebx, ecx, edx;
    if (__get_cpuid_count(7, 0, &eax, &ebx, &ecx, &edx)) {
        return (ebx & (1 << 5)) != 0; // Checking for AVX2 support
    }
    return false;
}

bool isNEONSupported() {
    std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line;
    while (std::getline(cpuinfo, line)) {
        if (line.find("neon") != std::string::npos) {
            return true;
        }
    }
    return false;
}

int main() {
    if (isSSE42Supported()) {
        std::cout << "SSE4.2 is supported." << std::endl;
    } else {
        std::cout << "SSE4.2 is not supported." << std::endl;
    }

    if (isAVX2Supported()) {
        std::cout << "AVX2 is supported." << std::endl;
    } else {
        std::cout << "AVX2 is not supported." << std::endl;
    }
    if (isNEONSupported()) {
        std::cout << "NEON is supported." << std::endl;
    } else {
        std::cout << "NEON is not supported." << std::endl;
    }
    return 0;
}


