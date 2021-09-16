/*===========================================================================
  @file    FieldMesh.h
  @brief  �t�B�[���h�`��
  @author �����r�I
  @date   2021/09/09
===========================================================================*/
#ifndef _FIELDMESH_H_
#define _FIELDMESH_H_

#include "mesh.h"
class LightClass;
class FieldMeshClass
{
private:
	MESH   m_Mesh;
	
public:
	FieldMeshClass();
	~FieldMeshClass();
	void Update();
	void Draw(LightClass* plight);
private:
	HRESULT MakeVertexField();
};
#endif // !_FIELDMESH_H_