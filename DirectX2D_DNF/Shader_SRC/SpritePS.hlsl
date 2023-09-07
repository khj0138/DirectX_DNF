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
    float3 WorldPos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_TARGET
{
    //return In.Color;
    float4 color = (float) 0.0f;

    float2 UV = In.UV;
    if (ImageFlip == 1)
    {
        UV.x = 1.0f - UV.x;
    }
    color = albedoTexture.Sample(pointSampler, UV);
    
    //float4 lightColor = float4(0.2f, 0.2f, 0.2f, 1.0f);
    
    //for (int i = 0; i < 2; i++)
    //{
    //    CalculateLight2D(lightColor, In.WorldPos, i);
    //}
    
    //color *= lightColor;
    return color;
}