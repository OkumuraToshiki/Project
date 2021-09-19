#ifndef _SHADER_RESOURCE_H_
#define _SHADER_RESOURCE_H_
#include <vector>
#include "ShaderBase.h"
enum VSKind
{
	VS_NORMAL,
	VS_MAX
};
enum PSKind
{
	PS_NORMAL,
	PS_MAX
};

class ShaderResource
{
private:
	/*std::vector<VertexShader*> m_VSList;
	std::vector<PixelShader*> m_PSList;*/
	VertexShader* m_pVShader;
	PixelShader* m_pPShader;
public:
	ShaderResource(VertexShader::Layout layout, const char* vertex, const char* pixel);
	~ShaderResource();
	//シェーダー設定
	void Bind();
};
#endif // !_SHADER_RESOURCE_H_