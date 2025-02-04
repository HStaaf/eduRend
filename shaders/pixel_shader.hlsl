
Texture2D texDiffuse : register(t0);

cbuffer LightCamBuffer : register(b0)
{
    float4 CameraPosition; // vec4f for camera position
    float4 LightPosition; // vec4f for light position
};

cbuffer MaterialBuffer : register(b1)
{
    float3 AmbientColor;
    float3 DiffuseColor;
    float3 SpecularColor;
    float Shininess;
};



struct PSIn
{
	float4 Pos  : SV_Position;
	float3 Normal : NORMAL;
	float2 TexCoord : TEX;
};

//-----------------------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------------------

float4 PS_main(PSIn input) : SV_Target
{
	// Debug shading #1: map and return normal as a color, i.e. from [-1,1]->[0,1] per component
	// The 4:th component is opacity and should be = 1
	//return float4(input.Normal*0.5+0.5, 1);
	
	 // Calculate light direction
    float3 lightDir = normalize(LightPosition.xyz - input.Pos.xyz);

    // Calculate diffuse lighting
    float diffuse = max(dot(input.Normal, lightDir), 0.0);
	
    // Return the shaded color
    return float4(diffuse, diffuse, diffuse, 1.0);
	
}