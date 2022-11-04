#include"BasicShaderHeader.hlsli"
//struct GSOutput
//{
//	float4 pos : SV_POSITION;
//};

[maxvertexcount(3)]
void main(
	point VSOutput input[1] : SV_POSITION, 

	inout TriangleStream< GSOutput > output
//	inout PointStream< GSOutput > output
//	inout LineStream< GSOutput > output
)
{
	GSOutput element;
//	for (uint i = 0; i < 3; i++)
//	{
	element.normal = input[0].normal;
	element.uv = input[0].uv;

	element.svpos = input[0].svpos;
	output.Append(element);
	
	element.svpos = input[0].svpos+float4(10.0f,10.0f,0,0);
	output.Append(element);

	element.svpos = input[0].svpos + float4(10.0f, 0, 0, 0);
	output.Append(element);

//	}
}