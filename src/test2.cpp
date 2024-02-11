#include <iostream>

#if defined(__i386__) || defined(__x86_64__)
#include <cpuid.h> // Include cpuid.h only for x86 and x86_64 architectures

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

// Main function
int main() {
    #if defined(__arm__)
    std::cout << "Compiled for ARM (32-bit)." << std::endl;
    std::cout << "NEON support is generally assumed for ARMv7 and later." << std::endl;
    #elif defined(__aarch64__)
    std::cout << "Compiled for ARM64 (AArch64)." << std::endl;
    std::cout << "NEON support is generally assumed for ARM64." << std::endl;
    #elif defined(__i386__) || defined(__x86_64__)
    #if defined(__x86_64__)
    std::cout << "Compiled for x86_64 (64-bit)." << std::endl;
    #else
    std::cout << "Compiled for x86 (32-bit)." << std::endl;
    #endif
    // Check for SSE4.2 and AVX2 support
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
    #else
    std::cout << "Architecture not identified." << std::endl;
    #endif

    return 0;
}

