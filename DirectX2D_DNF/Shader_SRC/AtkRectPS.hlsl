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
    
    float2 UV = In.UV;
    if (ImageFlip == 1)
        UV.x = 1.0f - UV.x;
    
    float cur = curPercent;
    cur *= 0.5f;
    cur += 0.5f;
    float start = startPercent;
    start *= 0.5f;
    start += 0.5f;
    float end = endPercent;
    end *= 0.5f;
    end += 0.5f;
    if (start == end)
    {
        cur *= end;
        if (UV.y <= 0.5f)
        {
            UV.y = 1.0f - UV.y;
        }
        if (UV.y <= end && UV.y >= (end - 0.001f))
            color = float4(1.0f, 0.1f, 0.05f, 0.2f);
        else if (UV.y <= (end - 0.001f) && UV.y >= (end - 0.003f))
            color = float4(1.0f, 0.2f, 0.1f, 0.4f);
        else if (UV.y <= (end - 0.003f) && UV.y >= (end - 0.004f))
            color = float4(1.0f, 0.9f, 0.7f, 0.8f);
        else if (UV.y <= (end - 0.004f) && UV.y >= (end - 0.006f))
            color = float4(1.0f, 1.0f, 0.75f, 0.8f);
        else if (UV.y <= (end - 0.006f) && UV.y >= (end - 0.007f))
            color = float4(1.0f, 0.9f, 0.7f, 0.8f);
        else if (UV.y <= (end - 0.007f) && UV.y >= (end - 0.009f))
            color = float4(1.0f, 0.2f, 0.1f, 0.4f);
        else if (UV.y <= (end - 0.009f) && UV.y >= (end - 0.01f))
            color = float4(1.0f, 0.1f, 0.05f, 0.2f);
        
        if (UV.y <= cur && UV.y >= (cur - 0.001f))
            color = float4(1.0f, 0.1f, 0.05f, 0.2f);
        else if (UV.y < (cur - 0.001f) && UV.y >= (cur - 0.003f))
            color = float4(1.0f, 0.2f, 0.1f, 0.4f);
        else if (UV.y < (cur - 0.003f) && UV.y >= (cur - 0.004f))
            color = float4(1.0f, 0.9f, 0.7f, 0.8f);
        else if (UV.y < (cur - 0.004f) && UV.y >= (cur - 0.006f))
            color = float4(1.0f, 1.0f, 0.75f, 0.8f);
        else if (UV.y < (cur - 0.006f) && UV.y >= (cur - 0.007f))
            color = float4(1.0f, 0.9f, 0.7f, 0.8f);
        else if (UV.y < (cur - 0.007f) && UV.y >= (cur - 0.009f))
            color = float4(1.0f, 0.2f, 0.1f, 0.4f);
        else if (UV.y < (cur - 0.009f) && UV.y >= (cur - 0.01f))
            color = float4(1.0f, 0.1f, 0.05f, 0.2f);
        else if (UV.y < (cur - 0.01f))
            color = float4(0.3f, 0.1f, 0.1f, 0.2f);
    }
    else
    {
        float curStart = cur * start;
        float curEnd = cur * end;
        if (UV.y <= 0.5f)
        {
            UV.y = 1.0f - UV.y;
        }
        float2 maxLineVector = float2(1.0, end) - float2(0.0f, start);
        float2 maxLinePoint = float2(0.0f, start);
        float2 normalizedMaxLine = normalize(maxLineVector);
        
        float2 curLineVector = float2(1.0, curEnd) - float2(0.0f, curStart);
        float2 curLinePoint = float2(0.0f, curStart);
        float2 normalizedCurLine = normalize(curLineVector);
       
        float2 colorPoint = float2(UV.x, UV.y);
        float2 pointToCurLine = colorPoint - curLinePoint;
        float2 pointToMaxLine = colorPoint - maxLinePoint;
        
        float maxDistance = abs(pointToMaxLine.x * normalizedMaxLine.y - pointToMaxLine.y * normalizedMaxLine.x);
        float maxCrossProduct = pointToMaxLine.x * normalizedMaxLine.y - pointToMaxLine.y * normalizedMaxLine.x;
        
        if (maxDistance >= 0.0f && maxDistance <= 0.001f)
            color = float4(1.0f, 0.1f, 0.05f, 0.2f);
        else if (maxDistance >= 0.001f && maxDistance < 0.003f)
            color = float4(1.0f, 0.2f, 0.1f, 0.4f);
        else if (maxDistance >= 0.003f && maxDistance < 0.004f)
             color = float4(1.0f, 0.9f, 0.7f, 0.8f);
        else if (maxDistance >= 0.004f && maxDistance < 0.006f)
             color = float4(1.0f, 1.0f, 0.75f, 0.8f);
        else if (maxDistance >= 0.006f && maxDistance < 0.007f)
             color = float4(1.0f, 0.9f, 0.7f, 0.8f);
        else if (maxDistance >= 0.007f && maxDistance < 0.009f)
            color = float4(1.0f, 0.2f, 0.1f, 0.4f);
        else if (maxDistance >= 0.009f && maxDistance < 0.01f)
            color = float4(1.0f, 0.1f, 0.05f, 0.2f);
        
        else
        {
            if (maxCrossProduct < 0.0f)
                color = float4(0.3f, 0.1f, 0.1f, 0.0f);
            
            float curDistance = abs(pointToCurLine.x * normalizedCurLine.y - pointToCurLine.y * normalizedCurLine.x);
            float curCrossProduct = pointToCurLine.x * normalizedCurLine.y - pointToCurLine.y * normalizedCurLine.x;
            
            if (curDistance >= 0.0f && curDistance < 0.001f)
                color = float4(1.0f, 0.1f, 0.05f, 0.2f);
            else if (curDistance >= 0.001f && curDistance < 0.003f)
                color = float4(1.0f, 0.2f, 0.1f, 0.4f);
            else if (curDistance >= 0.003f && curDistance < 0.004f)
                color = float4(1.0f, 0.9f, 0.7f, 0.8f);
            else if (curDistance >= 0.004f && curDistance < 0.006f)
                color = float4(1.0f, 1.0f, 0.75f, 0.8f);
            else if (curDistance >= 0.006f && curDistance < 0.007f)
                color = float4(1.0f, 0.9f, 0.7f, 0.8f);
            else if (curDistance >= 0.007f && curDistance < 0.009f)
                color = float4(1.0f, 0.2f, 0.1f, 0.4f);
            else if (curDistance >= 0.009f && curDistance < 0.01f)
                color = float4(1.0f, 0.1f, 0.05f, 0.2f);
            else if (curDistance >= 0.01f)
            {
                if(curCrossProduct < 0.0f)
                    discard;
                else
                    color = float4(0.3f, 0.1f, 0.1f, 0.4f);
                
            }
        }
    }
    color.w *= 2.0f;
    return color;
}