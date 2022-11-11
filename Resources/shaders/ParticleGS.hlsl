#include"Particle.hlsli"
//struct GSOutput
//{
//	float4 pos : SV_POSITION;
//};

static const uint vnum = 4;

static const float4 offset_array[vnum] =
{
	float4(-0.5f,-0.5f,0,0),//左下
	float4(-0.5f,+0.5f,0,0),//左上
	float4(+0.5f,-0.5f,0,0),//右下
	float4(+0.5f,+0.5f,0,0),//右上
};
static const float2 uv_array[vnum] =
{
	float2(0,1),//左下
	float2(0,0),//左上
	float2(1,1),//右下
	float2(1,0),//右上
};

[maxvertexcount(vnum)]
void main(
	point VSOutput input[1] : SV_POSITION,

	inout TriangleStream< GSOutput > output

)
{
	GSOutput element;
	for (uint i = 0; i < vnum; i++)
	{

		float4 offset = mul(matBillboard, offset_array[i]);
		element.svpos = input[0].pos + offset;

		element.svpos = mul(mat, element.svpos);
		element.uv = uv_array[i];
		output.Append(element);
	}
}

//	}