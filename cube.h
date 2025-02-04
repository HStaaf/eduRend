#pragma once
#include "../src/model.h"

class Cube : public Model
{
	unsigned m_number_of_indices = 0;
	Material m_material;

public:
	/**
	 * @brief Create a model of a quad.
	 * @param dxdevice Valid ID3D11Device.
	 * @param dxdevice_context Valid ID3D11DeviceContext.
	*/
	Cube(ID3D11Device* dxdevice, ID3D11DeviceContext* dxdevice_context);

	/**
	 * @brief Render the model.
	*/
	virtual void Render() const;

	/**
	 *@brief Destructor.
	*/
	~Cube() {}
};
