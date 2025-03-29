#pragma once

/** The CHECK_NUM_FIELDS macro compares the expected number of fields in a class/struct
 * with the actual number of fields in that class/struct.
 *
 * Parameters:
 * - ExpectedCount: The expected number of fields in the class/struct.
 * - Class: The class/struct type whose fields are being counted.
*/
#if !UE_BUILD_SHIPPING
#define CHECK_NUM_FIELDS(ExpectedCount, Class) \
    { \
        uint16 PropertyCount = 0; \
        for (TFieldIterator<FProperty> PropertyIt(Class::StaticStruct()); PropertyIt; ++PropertyIt) \
        { \
            PropertyCount++; \
        } \
        if(PropertyCount != ExpectedCount) \
        { \
            UE_LOGFMT(LogTemp, Error, "Mismatch between the expected and actual number of fields in the given class/struct. Please update the code. File: %hs, Line: %d", __FILE__, __LINE__); \
        } \
    }
#endif