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

cbuffer Transform : register(b0)
{
    float4 Position;
}
VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
    
    
    Out.Pos = float4(In.Pos, 1.0f);
    //Out.Pos.xy += Position.xy;
    Out.UV = In.UV;
    Out.Color = In.Color;
    
    return Out;
}