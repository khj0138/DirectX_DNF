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
    
    if (ImageRepeat == 0)
    {
      //  if (UV.x < (Move.x / Expand.x) || (UV.x > ((Move.x / Expand.x) + 1.0f)))
        //    discard;

        //if ((UV.x < (Move.x * Move.x * 1.0f))  || (UV.x > (Move.x * Move.x * 1.0f + 1.0f)))
        if (Move.x < 0.0f)
            if ((UV.x < -1.0f) || (UV.x > 0.0f))
                discard;
            if ((UV.x < Expand.x - 1.0f) || (UV.x > Expand.x ))
        if (Move.x > 0.0f)
                discard;
        //if (UV.x < Move.x + 2.5f || UV.x > Move.x + 3.5f)
    } 
    //expand /  Expand.x * Move.x
    color = albedoTexture.Sample(pointSampler, UV);
    return color;
}

