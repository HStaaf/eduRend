
Texture2D texDiffuse : register(t0);
SamplerState texSampler : register(s0);

cbuffer LightCamBuffer : register(b0)
{
    float4 CameraPosition; 
    float4 LightPosition; 
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
    float3 PosWorld : WORLD;
};

//-----------------------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------------------

float4 PS_main(PSIn input) : SV_Target
{

    float2 scaledTexCoord = input.TexCoord * 2.0;
    float4 texColor = texDiffuse.Sample(texSampler, scaledTexCoord);
    
    // Calculating L 
    float3 lightDirection = normalize(LightPosition.xyz - input.PosWorld.xyz);

    // Calculating V
    float3 viewDirection = normalize(CameraPosition.xyz - input.PosWorld.xyz);

    // Ambient lighting
    float3 ambient = AmbientColor;

    // Calculate L * N
    float diffuseFactor = max(dot(input.Normal, lightDirection), 0.0);

    //Calculating k_d(L*N)
    float3 diffuse = DiffuseColor * diffuseFactor;

    // Calculating (R*V)^a
    float3 reflectDirection = reflect(-lightDirection, input.Normal);
    float specFactor = pow(max(dot(viewDirection, reflectDirection), 0.0), Shininess);

    //Calculating k_s(R*V)^a
    float3 specular = SpecularColor * specFactor;
    
    // Add results
    float3 color = ambient + diffuse + specular;

    // Return the shaded color
    return float4(color, 1.0) * texColor;
    	
}