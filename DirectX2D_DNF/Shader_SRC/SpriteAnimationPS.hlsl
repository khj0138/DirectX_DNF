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
    float4 color = (float4) 0.0f;
    
    color = albedoTexture.Sample(anisotropicSampler, In.UV);
    //if (animationType == 1)
    if (true)
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
        if (AnimFlip == 1)
        {
            UV.x = centerX + (centerX - UV.x);
        }
        if (AnimBack == 1)
        {
            UV.x = centerX + (centerX - UV.x);
            UV.x = (1 - UV.x);
        }
        color = atlasTexture.Sample(anisotropicSampler, UV);
        
        
    }
    //float4 lightColor = float4(0.2f, 0.2f, 0.2f, 1.0f);
    
    
    //for (int i = 0; i < 2; i++)
    //{
    //    CalculateLight2D(lightColor, In.WorldPos, i);
    //}
    
    //color *= lightColor;
    
    //if (Out.a <= 0.0f)
        //discard;
    //color= float4(1.0f, 1.0f, 0.2f, 1.0f);
    return color;
}