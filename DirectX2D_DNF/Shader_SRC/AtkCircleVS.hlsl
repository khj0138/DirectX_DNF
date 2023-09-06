#include "globals.hlsli"

//structedBuffer
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


VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
    
    float4x4 worldm = (float4x4) WorldMatrix;
    
    worldm._12 = worldm._12 * 0.7143f;
    worldm._22 = worldm._22 * 0.7143f;
    worldm._32 = worldm._32 * 0.7143f;
    worldm._42 = worldm._42 * 0.7143f;
    //worldm._42 = worldm._42 - abs(worldm._42 / (float) (cosh(0.78f)) * (1.0f - (float) cosh(0.78f)));// * 5.0f;
    float4 world = mul(float4(In.Pos, 1.0f), worldm);
    //world.y = world.y / cosh(0.78f);
    float4 view = mul(world, ViewMatrix);
    float4 proj = mul(view, ProjectionMatrix);
    
    Out.Pos = proj;
    //Out.Pos.y = Out.Pos.y / cosh(0.78f);
    //Out.Pos.y = Out.Pos.y / cosh(0.78f);
    Out.Color = In.Color;
    Out.UV = In.UV;
    
    return Out;
}

