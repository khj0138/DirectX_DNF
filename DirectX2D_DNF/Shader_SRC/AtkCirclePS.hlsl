#include "globals.hlsli"

struct GSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};
float4 main(GSOut In) : SV_TARGET
{
    //float2 distance = In.Pos.xy - float2(0, 0);
    //float radius = In.size / 2.0; // 원의 반지름은 점의 크기의 절반
    
    //// 점의 크기 내에 있는 픽셀에 색상 할당
    //if (length(distance) <= radius)
    //{
    //    return float4(1.0, 0.0, 0.0, 1.0); // 예시로 빨간색 할당
    //}
    //else
    //{
    //    discard; // 원의 외부 픽셀은 버립니다.
    //}
    float4 color = float4(0.5f, 0.0f, 0.0f, 0.0f);

    
    //if (bCollision != 0
    //    color = float4(1.0f, 0.0f, 0.0f, 1.0f);
    
    
    float2 UV = In.UV;
    if (UV.x <= 1.0f && UV.x >= 0.999f)
        color = float4(1.0f, 0.1f, 0.05f, 0.1f);
    else if (UV.x < 0.999f && UV.x >= 0.997f)
        color = float4(1.0f, 0.2f, 0.1f, 0.2f);
    else if (UV.x < 0.997f && UV.x >= 0.996f)
        color = float4(1.0f, 0.9f, 0.7f, 0.7f);
    else if (UV.x < 0.996f && UV.x >= 0.994f)
        color = float4(1.0f, 1.0f, 0.75f, 0.7f);
    else if (UV.x < 0.994f && UV.x >= 0.993f)
        color = float4(1.0f, 0.9f, 0.7f, 0.7f);
    else if (UV.x < 0.993f && UV.x >= 0.991f)
        color = float4(1.0f, 0.2f, 0.1f, 0.2f);
    else if (UV.x < 0.991f && UV.x >= 0.990f)
        color = float4(1.0f, 0.1f, 0.05f, 0.1f);

    if (UV.x <= curPercent && UV.x >= (curPercent - 0.001f))
        color = float4(1.0f, 0.1f, 0.05f, 0.1f);
    else if (UV.x < (curPercent - 0.001f) && UV.x >= (curPercent - 0.003f))
        color = float4(1.0f, 0.2f, 0.1f, 0.2f);
    else if (UV.x < (curPercent - 0.003f) && UV.x >= (curPercent - 0.004f))
        color = float4(1.0f, 0.9f, 0.7f, 0.7f);
    else if (UV.x < (curPercent - 0.004f) && UV.x >= (curPercent - 0.006f))
        color = float4(1.0f, 1.0f, 0.75f, 0.7f);
    else if (UV.x < (curPercent - 0.006f) && UV.x >= (curPercent - 0.007f))
        color = float4(1.0f, 0.9f, 0.7f, 0.7f);
    else if (UV.x < (curPercent - 0.007f) && UV.x >= (curPercent - 0.009f))
        color = float4(1.0f, 0.2f, 0.1f, 0.2f);
    else if (UV.x < (curPercent - 0.009f) && UV.x >= (curPercent - 0.01f))
        color = float4(1.0f, 0.1f, 0.05f, 0.1f);
    else if (UV.x < (curPercent - 0.01f))
        color = float4(0.3f, 0.1f, 0.1f, 0.2f);
    
    if (UV.x <= startPercent && UV.x >= (startPercent - 0.001f))
        color = float4(1.0f, 0.1f, 0.05f, 0.1f);
    else if (UV.x < (startPercent - 0.001f) && UV.x >= (startPercent - 0.003f))
        color = float4(1.0f, 0.2f, 0.1f, 0.2f);
    else if (UV.x < (startPercent - 0.003f) && UV.x >= (startPercent - 0.004f))
        color = float4(1.0f, 0.9f, 0.7f, 0.7f);
    else if (UV.x < (startPercent - 0.004f) && UV.x >= (startPercent - 0.006f))
        color = float4(1.0f, 1.0f, 0.75f, 0.7f);
    else if (UV.x < (startPercent - 0.006f) && UV.x >= (startPercent - 0.007f))
        color = float4(1.0f, 0.9f, 0.7f, 0.7f);
    else if (UV.x < (startPercent - 0.007f) && UV.x >= (startPercent - 0.009f))
        color = float4(1.0f, 0.2f, 0.1f, 0.2f);
    else if (UV.x < (startPercent - 0.009f) && UV.x >= (startPercent - 0.01f))
        color = float4(1.0f, 0.1f, 0.05f, 0.1f);
    else if (UV.x < (startPercent - 0.01f))
        color = float4(0.3f, 0.1f, 0.1f, 0.0f);
    

   
    //if (UV.x <= 0.5f)
    //    discard;
        return color;
}