/*===========================================================================
  @file    FieldMesh.h
  @brief  ÉtÉBÅ[ÉãÉhï`âÊ
  @author âúë∫èrãI
  @date   2021/09/09
===========================================================================*/
#ifndef _FIELDMESH_H_
#define _FIELDMESH_H_

#include "mesh.h"
class FieldMeshClass
{
private:
	MESH   m_Mesh;
	HRESULT MakeVertexField();
public:
	FieldMeshClass();
	~FieldMeshClass();

	void Draw();
};
#endif // !_FIELDMESH_H_