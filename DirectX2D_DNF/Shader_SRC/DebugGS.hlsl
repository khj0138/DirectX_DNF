#include "globals.hlsli"



struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};


struct GSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

[maxvertexcount(3)]
void main(line VSOut In[2], inout TriangleStream<GSOut> OutputStream)
{
    //GSOut output;
    //output.Pos = In[0].Pos;
    //output.Color = In[0].Color;
    //output.UV = In[0].UV;
    //output.size = 100.0f;
    //OutputStream.Append(output);
    
    
    
    GSOut Out[3] = { (GSOut) 0.0f, (GSOut) 0.0f, (GSOut) 0.0f };
    Out[0].Pos = In[0].Pos;
    Out[1].Pos = In[1].Pos;
    Out[2].Pos = In[0].Pos;
    //Out[3].Pos = In[1].Pos;
    
    Out[0].Color = In[0].Color;
    Out[1].Color = In[1].Color;
    Out[2].Color = In[1].Color;
    //Out[3].Color = In[1].Color;
    
    Out[0].UV = In[0].UV;
    Out[1].UV = In[1].UV;
    Out[2].UV = In[1].UV;
    //Out[3].UV = In[1].UV;
    //float thickness = 0.02; // ���ϴ� �β��� ����
    
    // LineStrip�� ù ��° �� (������)
    float4 p0 = In[0].Pos;
    
    // LineStrip�� �� ��° �� (����)
    float4 p1 = In[1].Pos;

    // ȸ�� ���� (����)
    float rotationAngle = radians(0.75); // 45�� ȸ�� (���ϴ� ������ ���� ����)

    // �β� ���� ���� ��� (���� ����)
    float2 direction = (p1.xy - p0.xy);
    //float2 thicknessDirection = float2(-direction.y, direction.x) * thickness;

    //Out[0].Pos.xy = In[0].Pos.xy + thicknessDirection;
    //Out[1].Pos.xy = In[0].Pos.xy - thicknessDirection;
    Out[2].Pos.x += direction.x * cos(rotationAngle) - direction.y * sin(rotationAngle);
    Out[2].Pos.y += direction.x * sin(rotationAngle) + direction.y * cos(rotationAngle);
    
    OutputStream.Append(Out[0]);
    OutputStream.Append(Out[1]);
    OutputStream.Append(Out[2]);
    OutputStream.RestartStrip();

   // OutputStream.Append(Out[1]);
   // OutputStream.Append(Out[2]);
   // OutputStream.Append(Out[3]);
   // OutputStream.RestartStrip();
}