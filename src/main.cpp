#include <iostream>
#include <fstream>
#include <string>

#ifdef __linux__
    #define OS_IS_LINUX 1
#else
    #define OS_IS_LINUX 0
#endif

#if defined(_WIN32) || defined(_WIN64)
    #define OS_IS_WINDOWS 1
#else
    #define OS_IS_WINDOWS 0
#endif

#if defined(__i386__) || defined(__x86_64__)
    #define ARCH_IS_X86 1
#else
    #define ARCH_IS_X86 0
#endif

#if defined(__arm__) || defined(__aarch64__)
    #define ARCH_IS_ARM 1
#else
    #define ARCH_IS_ARM 0
#endif

#if defined(__x86_64__) || defined(__aarch64__)
    #define ARCH_IS_64_BIT 1
#else
    #define ARCH_IS_64_BIT 0
#endif

#if OS_IS_LINUX && ARCH_IS_X86
    #include <cpuid.h>  // Include cpuid.h only for x86 and x86_64 architectures
#endif

#if ARCH_IS_X86 && OS_IS_LINUX
// Function to check for SSE4.2 support on x86/x86_64
bool isSSE42Supported() {
    unsigned int eax, ebx, ecx, edx;
    __get_cpuid(1, &eax, &ebx, &ecx, &edx);
    return (ecx & (1 << 20)) != 0;
}

// Function to check for AVX2 support on x86/x86_64
bool isAVX2Supported() {
    unsigned int eax, ebx, ecx, edx;
    __get_cpuid_count(7, 0, &eax, &ebx, &ecx, &edx);
    return (ebx & (1 << 5)) != 0;
}
#endif

#if ARCH_IS_ARM && OS_IS_LINUX
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
#endif


// Main function
int main() {

#if OS_IS_WINDOWS
    std::cout << "Compiled for Windows." << std::endl;  
#elif OS_IS_LINUX
    std::cout << "Compiled for Linux." << std::endl;
#endif

#if ARCH_IS_X86 && !ARCH_IS_64_BIT
    std::cout << "Compiled for x86 (32 bit)." << std::endl; 
#elif ARCH_IS_X86 && ARCH_IS_64_BIT
    std::cout << "Compiled for x86_64 (64 bit)." << std::endl;
#endif

#if ARCH_IS_ARM && !ARCH_IS_64_BIT
    std::cout << "Compiled for ARM (32 bit)." << std::endl;
#elif ARCH_IS_ARM && ARCH_IS_64_BIT
    std::cout << "Compiled for ARM64 (64 bit)." << std::endl;
#endif

#if ARCH_IS_X86 && OS_IS_LINUX
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
#endif

#if ARCH_IS_ARM && OS_IS_LINUX
    if (isNEONSupported()) {
        std::cout << "NEON is supported." << std::endl;   
    } else {
        std::cout << "NEON is not supported." << std::endl;
    }
#endif

    return 0;
}

