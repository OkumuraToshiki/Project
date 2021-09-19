/*===========================================================================
  @file   TextureVs.hlsl
  @brief  テクスチャ表示の頂点シェーダー
  @author 奥村俊紀
  @date   2021/09/18
===========================================================================*/
struct VS_IN
{
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
	float4 color : COLOR0;
};
struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float3 normal : TEXCOORD1;
	float4 color : TEXCOORD2;
	float4 wPos : TEXCOORD3;
};
cbuffer global : register(b0) {
	matrix	g_View;	            // ビュー行列
	matrix  g_Proj;             // 射影行列
	matrix	g_World;			// ワールド行列
};

VS_OUT main(VS_IN VIN)
{
	VS_OUT VOUT;

	VOUT.pos = float4(VIN.pos, 1);
	VOUT.pos = mul(VOUT.pos, g_World);
	VOUT.wPos = VOUT.pos;
	VOUT.pos = mul(VOUT.pos, g_View);
	VOUT.pos = mul(VOUT.pos, g_Proj);

	VOUT.uv = VIN.uv;
	VOUT.normal = mul(VIN.normal, (float3x3)g_World);
	VOUT.color = VIN.color;

	return VOUT;
}