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
    
    float4 world = mul(float4(In.Pos, 1.0f), WorldMatrix);
    float4 view = mul(world, ViewMatrix);
    float4 proj = mul(view, ProjectionMatrix);
    
    
    Out.Pos = proj;
    Out.Color = In.Color;
    // Out.UV = float2(In.UV.x, In.UV.y);
    //if Time 
    if (ImageRepeat == 0)
    {
       //Out.UV = float2((In.UV.x + Move.x) * (Expand.x), (In.UV.y + Move.y) * Expand.y);
       //Out.UV = float2((In.UV.x + Move.x) * (Expand.x), (In.UV.y + Move.y) * Expand.y);
        Out.UV = float2((In.UV.x + Move.x) * (Expand.x), (In.UV.y + Move.y) * Expand.y);
       // Out.UV = float2(In.UV.x * Expand.x + Move.x, In.UV.y * Expand.y + Move.y);
        
    }
    else
    {
        Out.UV = float2(In.UV.x * Expand.x + Move.x, In.UV.y * Expand.y + Move.y);
    }
    //Out.UV = float2(In.UV.x * Expand.x + Move.x, In.UV.y * Expand.y + Move.y);
        //Out.UV = float2(In.UV.x * Expand.x , In.UV.y * Expand.y);
    
    //Out.UV = float2(In.UV.x / Expand.x, In.UV.y * Expand.y);
    //Out.UV = In.UV;
    
    return Out;
}