#include "globals.hlsli"

struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_TARGET
{
    //return In.Color;
    float4 color = (float) 0.0f;
    //color = albedoTexture.Sample(pointSampler, In.UV);
    float2 UV = In.UV;
    if (ImageFlip == 1)
    {
        UV.x = 1.0f - UV.x;
    }
    color = albedoTexture.Sample(pointSampler, UV);
    return color;
}