#include "../src/Model.h"


Model::Model(ID3D11Device* dxdevice, ID3D11DeviceContext* dxdevice_context)
	: m_dxdevice(dxdevice), m_dxdevice_context(dxdevice_context) {
	InitMaterialBuffer();	
}

void Model::InitMaterialBuffer()
{
	HRESULT hr;
	D3D11_BUFFER_DESC matrixBufferDesc = { 0 };
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MaterialBuffer);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;
	ASSERT(hr = m_dxdevice->CreateBuffer(&matrixBufferDesc, nullptr, &m_material_buffer));
}

void Model::UpdateMaterialBuffer(const Material& material) const
{
	// Map the resource buffer, obtain a pointer and then write our matrices to it
	D3D11_MAPPED_SUBRESOURCE resource;
	m_dxdevice_context->Map(m_material_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	MaterialBuffer* matrixBuffer = (MaterialBuffer*)resource.pData;
	matrixBuffer->AmbientColor  = material.AmbientColour;
	matrixBuffer->DiffuseColor  = material.DiffuseColour;
	matrixBuffer->SpecularColor = material.SpecularColour;
	matrixBuffer->Shininess     = material.Shininess;
	m_dxdevice_context->Unmap(m_material_buffer, 0);

}
