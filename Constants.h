#ifndef CONSTANTS_H_INCLUDED
    #define CONSTANTS_H_INCLUDED

    #ifdef PRE_32_BIT
        const char * const szClassName = "ListerPluginsTester";
        const char * const menoDLL     = "CharsOccurrences.wlx";
    #else
        const char * const szClassName = "ListerPluginsTester 64-bit";
        const char * const menoDLL     = "CharsOccurrences.wlx64";
    #endif

    const char * const menoSuboru1     = "C:\\LoremIpsum1.txt";
    const char * const menoSuboru2     = "C:\\LoremIpsum2.txt";

#endif // CONSTANTS_H_INCLUDED
