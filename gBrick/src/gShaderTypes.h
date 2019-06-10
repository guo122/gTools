
#ifndef GSHADERTYPES_H_ED11A4AC25766C09C40C0448CF00ECB9
#define GSHADERTYPES_H_ED11A4AC25766C09C40C0448CF00ECB9

typedef struct
{
    vector_float4 position;
    vector_float3 color;
} GVertex;

typedef struct
{
    matrix_float4x4 projectionMatrix;
    matrix_float4x4 modelViewMatrix;
} GMatrix;

typedef enum GVertexInputIndex
{
    GVertexInputIndexVertices     = 0,
    GVertexInputIndexMatrix       = 1,
} GVertexInputIndex;

#endif // GSHADERTYPES_H_ED11A4AC25766C09C40C0448CF00ECB9
