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
    float4 color = (float4) 0.0f;
    
    color = albedoTexture.Sample(anisotropicSampler, In.UV);
    if (animationType == 1)
    {
        float2 diff = (AtlasSize - SpriteSize) / 2.0f;
        float2 UV = (SpriteLeftTop - diff - SpriteOffset)
                + (AtlasSize * In.UV);
    
        float centerX = (2.0f * SpriteLeftTop.x + SpriteSize.x) / 2.0f;
        //if (UV.x < SpriteLeftTop.x - SpriteOffset.x / 2.0f || UV.x > SpriteLeftTop.x + SpriteSize.x - SpriteOffset.x / 2.0f
        //    || UV.y < SpriteLeftTop.y - SpriteOffset.y / 2.0f || UV.y > SpriteLeftTop.y - SpriteOffset.y / 2.0f + SpriteSize.y)
        if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x
            || UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
            discard;
        else if (AnimFlip == 1)
        {
            UV.x = centerX + (centerX - UV.x);
        }
        else if (AnimBack == 1)
        {
            UV.x = centerX + (centerX - UV.x);
            UV.x = (1 - UV.x);
        }
        color = atlasTexture.Sample(anisotropicSampler, UV);
    }
    //discard;
    return color;
}