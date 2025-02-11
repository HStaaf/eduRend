#include "cube.h"


Cube::Cube(ID3D11Device* dxdevice, ID3D11DeviceContext* dxdevice_context) : Model(dxdevice, dxdevice_context)
{
	m_material.DiffuseColour = { 1.0f, 0.0f, 0.0f }; 
	m_material.SpecularColour = { 1.0f, 1.0f, 1.0f }; 

	// Vertex and index arrays
	// Once their data is loaded to GPU buffers, they are not needed anymore
	std::vector<Vertex> vertices;
	std::vector<unsigned> indices;

	// Populate the vertex array with 4 Vertices
	Vertex v0, v1, v2, v3, v4, v5, v6, v7;

	#pragma region These things are fine, dont worry about it

	#pragma region Creating Front face
	v0.Position = { -0.5, -0.5f, 0.0f };
	v0.Normal = { 0, 0, 1 };
	v0.TexCoord = { 0, 0 };
	
	v1.Position = { 0.5, -0.5f, 0.0f };
	v1.Normal = { 0, 0, 1 };
	v1.TexCoord = { 0, 1 };
	
	v2.Position = { 0.5, 0.5f, 0.0f };
	v2.Normal = { 0, 0, 1 };
	v2.TexCoord = { 1, 1 };

	v3.Position = { -0.5, 0.5f, 0.0f };
	v3.Normal = { 0, 0, 1 };
	v3.TexCoord = { 1, 0 };
	#pragma endregion

	#pragma region Push Top face to vertex and triangle indices
	vertices.push_back(v0); // [0]
	vertices.push_back(v1); // [1]
	vertices.push_back(v2); // [2]
	vertices.push_back(v3); // [3]

	// Triangle #1
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);

	// Triangle #2
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);
	#pragma endregion

	#pragma region Creating Back face
	v4.Position = { -0.5, -0.5f, -1.0f };
	v4.Normal = { 0, 0, -1 };
	v4.TexCoord = { 0, 0 };

	v5.Position = { 0.5, -0.5f, -1.0f };
	v5.Normal = { 0, 0, -1 };
	v5.TexCoord = { 0, 1 };

	v6.Position = { 0.5, 0.5f, -1.0f };
	v6.Normal = { 0, 0, -1 };
	v6.TexCoord = { 1, 1 };

	v7.Position = { -0.5, 0.5f, -1.0f };
	v7.Normal = { 0, 0, -1 };
	v7.TexCoord = { 1, 0 };
	#pragma endregion

	#pragma region Push Back face to vertex and triangle indices
	// Push Back face to vertex index
	vertices.push_back(v4); // [4]
	vertices.push_back(v5); // [5]
	vertices.push_back(v6); // [6]
	vertices.push_back(v7); // [7]

	// Triangle #3
	indices.push_back(4);
	indices.push_back(7);
	indices.push_back(5);

	// Triangle #4
	indices.push_back(5);
	indices.push_back(7);
	indices.push_back(6);
	#pragma endregion
	
	#pragma region Creating Right face
	v1.Normal = v2.Normal = v5.Normal = v6.Normal = { 1, 0, 0 };
	#pragma endregion

	#pragma region Push Right face to vertex and triangle indices
	vertices.push_back(v1); // [8]
	vertices.push_back(v2); // [9]
	vertices.push_back(v5); // [10]
	vertices.push_back(v6); // [11]

	// Triangle #4
	indices.push_back(10);
	indices.push_back(9);
	indices.push_back(8);

	// Triangle #5
	indices.push_back(9);
	indices.push_back(10);
	indices.push_back(11);
	#pragma endregion

	#pragma region Creating Left face
	v0.Normal = v3.Normal = v4.Normal = v7.Normal = { -1, 0, 0 };
	#pragma endregion

	#pragma region Push Left face to vertex and triangle indices
	vertices.push_back(v0); // [12]
	vertices.push_back(v3); // [13]
	vertices.push_back(v4); // [14]
	vertices.push_back(v7); // [15]

	// Triangle #6
	indices.push_back(12);
	indices.push_back(13);
	indices.push_back(14);

	// Triangle #7
	indices.push_back(15);
	indices.push_back(14);
	indices.push_back(13);
	#pragma endregion

	#pragma region Creating Top face
	v2.Normal = v3.Normal = v6.Normal = v7.Normal = { 0, 1, 0 };
	#pragma endregion

	#pragma region Push Top face to vertex and triangle indices
	vertices.push_back(v2); // [16]
	vertices.push_back(v3); // [17]
	vertices.push_back(v6); // [18]
	vertices.push_back(v7); // [19]

	// Triangle #8
	indices.push_back(18);
	indices.push_back(17);
	indices.push_back(16);

	// Triangle #9
	indices.push_back(17);
	indices.push_back(18);
	indices.push_back(19);
	#pragma endregion

	#pragma region Creating Bottom face
	v0.Normal = v1.Normal = v4.Normal = v5.Normal = { 0, 1, 0 };
	#pragma endregion

	#pragma region Push Bottom face to vertex and triangle indices
	vertices.push_back(v0); // [20]
	vertices.push_back(v1); // [21]
	vertices.push_back(v4); // [22]
	vertices.push_back(v5); // [23]

	// Triangle #10
	indices.push_back(22);
	indices.push_back(21);
	indices.push_back(20);

	// Triangle #11
	indices.push_back(21);
	indices.push_back(22);
	indices.push_back(23);
	#pragma endregion

	#pragma region Loading the vertex and index buffers
	// Vertex array descriptor
	D3D11_BUFFER_DESC vertexbufferDesc{ 0 };
	vertexbufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexbufferDesc.CPUAccessFlags = 0;
	vertexbufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexbufferDesc.MiscFlags = 0;
	vertexbufferDesc.ByteWidth = (UINT)(vertices.size() * sizeof(Vertex));
	// Data resource
	D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	vertexData.pSysMem = &vertices[0];
	// Create vertex buffer on device using descriptor & data
	dxdevice->CreateBuffer(&vertexbufferDesc, &vertexData, &m_vertex_buffer);
	SETNAME(m_vertex_buffer, "VertexBuffer");

	//  Index array descriptor
	D3D11_BUFFER_DESC indexbufferDesc = { 0 };
	indexbufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexbufferDesc.CPUAccessFlags = 0;
	indexbufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexbufferDesc.MiscFlags = 0;
	indexbufferDesc.ByteWidth = (UINT)(indices.size() * sizeof(unsigned));
	// Data resource
	D3D11_SUBRESOURCE_DATA indexData{ 0 };
	indexData.pSysMem = &indices[0];
	// Create index buffer on device using descriptor & data
	dxdevice->CreateBuffer(&indexbufferDesc, &indexData, &m_index_buffer);
	SETNAME(m_index_buffer, "IndexBuffer");
	#pragma endregion

	#pragma endregion
	
	m_number_of_indices = (unsigned int)indices.size();

	if (m_material.DiffuseTextureFilename.size()) {

		HRESULT hr;

		hr = LoadTextureFromFile(
			dxdevice,
			m_material.DiffuseTextureFilename.c_str(),
			&m_material.DiffuseTexture);
		std::cout << "\t" << m_material.DiffuseTextureFilename
			<< (SUCCEEDED(hr) ? " - OK" : "- FAILED") << std::endl;
	}

}

void Cube::Render() const
{
	// Update the material buffer
	UpdateMaterialBuffer(m_material);

	// Bind the material buffer to slot b1 of the pixel shader
	m_dxdevice_context->PSSetConstantBuffers(1, 1, &m_material_buffer);


	// Bind our vertex buffer
	const UINT32 stride = sizeof(Vertex); //  sizeof(float) * 8;
	const UINT32 offset = 0;
	m_dxdevice_context->IASetVertexBuffers(0, 1, &m_vertex_buffer, &stride, &offset);

	// Bind our index buffer
	m_dxdevice_context->IASetIndexBuffer(m_index_buffer, DXGI_FORMAT_R32_UINT, 0);

	// Make the drawcall
	m_dxdevice_context->DrawIndexed(m_number_of_indices, 0, 0);
}


