#pragma once

typedef struct _SEGMENT_DESCRIPTOR
{
    union
    {
        unsigned __int64 control;
        struct
        {
            unsigned __int16 limitlow;        // [0:15]
            unsigned __int16 baselow;         // [16:31]
            unsigned __int32 basemiddle : 8;  // [32:39]
            unsigned __int32 type : 4;        // [40:43]
            unsigned __int32 system : 1;      // [44]
            unsigned __int32 dpl : 2;         // [45:46]
            unsigned __int32 present : 1;     // [47]
            unsigned __int32 limithigh : 4;   // [48:51]
            unsigned __int32 avl : 1;         // [52]
            unsigned __int32 longmode : 1;    // [53]
            unsigned __int32 defaultbit : 1;  // [54]
            unsigned __int32 granularity : 1; // [55]
            unsigned __int32 basehigh : 8;    // [56:63]
        } bits;
    };
} SEGMENT_DESCRIPTOR, *PSEGMENT_DESCRIPTOR;

typedef struct _SEGMENT_ATTRIBUTE
{
    union
    {
        unsigned __int16 control;
        struct
        {
            unsigned __int16 type : 4;        // [0:3]
            unsigned __int16 system : 1;      // [4]
            unsigned __int16 dpl : 2;         // [5:6]
            unsigned __int16 present : 1;     // [7]
            unsigned __int16 avl : 1;         // [8]
            unsigned __int16 longmode : 1;    // [9]
            unsigned __int16 defaultbit : 1;  // [10]
            unsigned __int16 granularity : 1; // [11]
            unsigned __int16 reserved1 : 4;   // [12:15]
        } bits;
    };
} SEGMENT_ATTRIBUTE, *PSEGMENT_ATTRIBUTE;


