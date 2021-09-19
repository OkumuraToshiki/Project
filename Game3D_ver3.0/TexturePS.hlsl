/*===========================================================================
  @file   TexturePS.hlsl
  @brief  �e�N�X�`���\���̃s�N�Z���V�F�[�_�[
  @author �����r�I
  @date   2021/09/18
===========================================================================*/
struct PS_IN
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float3 normal : TEXCOORD1;
	float4 color : TEXCOORD2;
	float4 wPos : TEXCOORD3;
};

Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN PIN) : SV_Target
{
	float4 color = tex.Sample(samp, PIN.uv);
	color *= PIN.color;
	return color;
	//return float4(1, 0, 0, 1);
}