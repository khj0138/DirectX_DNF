#include "globals.hlsli"

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};
float4 main(VSOut In) : SV_TARGET
{
    //float2 distance = In.Pos.xy - float2(0, 0);
    //float radius = In.size / 2.0; // ���� �������� ���� ũ���� ����
    
    //// ���� ũ�� ���� �ִ� �ȼ��� ���� �Ҵ�
    //if (length(distance) <= radius)
    //{
    //    return float4(1.0, 0.0, 0.0, 1.0); // ���÷� ������ �Ҵ�
    //}
    //else
    //{
    //    discard; // ���� �ܺ� �ȼ��� �����ϴ�.
    //}
    float4 color = float4(0.5f, 0.0f, 0.0f, 0.0f);
    
    
    float2 UV = In.UV;
    float cur = curPercent;
    float start = startPercent;
    float end = endPercent;
    cur *= 0.5f;
    cur += 0.5f;
    if (start == end)
    {
        cur *= end;
        if (UV.y <= 0.5f)
        {
            UV.y = 1.0f - UV.y;
        }
        if (UV.y <= end && UV.y >= (end - 0.001f))
            color = float4(1.0f, 0.1f, 0.05f, 0.05f);
        else if (UV.y <= (end - 0.001f) && UV.y >= (end - 0.003f))
            color = float4(1.0f, 0.2f, 0.1f, 0.1f);
        else if (UV.y <= (end - 0.003f) && UV.y >= (end - 0.004f))
            color = float4(1.0f, 0.9f, 0.7f, 0.5f);
        else if (UV.y <= (end - 0.004f) && UV.y >= (end - 0.006f))
            color = float4(1.0f, 1.0f, 0.75f, 0.5f);
        else if (UV.y <= (end - 0.006f) && UV.y >= (end - 0.007f))
            color = float4(1.0f, 0.9f, 0.7f, 0.5f);
        else if (UV.y <= (end - 0.007f) && UV.y >= (end - 0.009f))
            color = float4(1.0f, 0.2f, 0.1f, 0.1f);
        else if (UV.y <= (end - 0.009f) && UV.y >= (end - 0.01f))
            color = float4(1.0f, 0.1f, 0.05f, 0.05f);
        
        if (UV.y <= cur && UV.y >= (cur - 0.001f))
            color = float4(1.0f, 0.1f, 0.05f, 0.05f);
        else if (UV.y < (cur - 0.001f) && UV.y >= (cur - 0.003f))
            color = float4(1.0f, 0.2f, 0.1f, 0.1f);
        else if (UV.y < (cur - 0.003f) && UV.y >= (cur - 0.004f))
            color = float4(1.0f, 0.9f, 0.7f, 0.5f);
        else if (UV.y < (cur - 0.004f) && UV.y >= (cur - 0.006f))
            color = float4(1.0f, 1.0f, 0.75f, 0.5f);
        else if (UV.y < (cur - 0.006f) && UV.y >= (cur - 0.007f))
            color = float4(1.0f, 0.9f, 0.7f, 0.5f);
        else if (UV.y < (cur - 0.007f) && UV.y >= (cur - 0.009f))
            color = float4(1.0f, 0.2f, 0.1f, 0.1f);
        else if (UV.y < (cur - 0.009f) && UV.y >= (cur - 0.01f))
            color = float4(1.0f, 0.1f, 0.05f, 0.05f);
        else if (UV.y < (cur - 0.01f))
            color = float4(0.3f, 0.1f, 0.1f, 0.1f);
    }
    color.w *= 2.0f;
    return color;
}