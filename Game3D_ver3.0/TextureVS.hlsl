/*===========================================================================
  @file   TextureVs.hlsl
  @brief  �e�N�X�`���\���̒��_�V�F�[�_�[
  @author �����r�I
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
	matrix	g_View;	            // �r���[�s��
	matrix  g_Proj;             // �ˉe�s��
	matrix	g_World;			// ���[���h�s��
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