// Globals
float4x4 worldMatrix;
float4x4 viewMatrix;
float4x4 projectionMatrix;

//////////////
// TYPEDEFS //
//////////////
struct VertexInputType
{
    float3 position : POSITION;
    float4 color : COLOR;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType ColorVertexShader(VertexInputType input)
{
    PixelInputType output;
    
	// Takes verts and transforms to worldMatrix
	// takes color and passes it along
    
    // Change the position vector to be 4 units for proper matrix calculations.
    //input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(float4(input.position,1.0f), worldMatrix);
	//float4x4 WVP = worldMatrix*viewMatrix*projectionMatrix;
	//output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
    //output.position = mul(output.position, viewMatrix);
   // output.position = mul(output.position, projectionMatrix);
    
    // Store the input color for the pixel shader to use.
    output.color = input.color;
	output.color = float4(1.0f, 1.0f, 1.0f, 0.5f);
    
    return output;
}

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 ColorPixelShader(PixelInputType input) : SV_Target
{
    //return input.color;
	    return float4(1.0f, 1.0f, 1.0f, 0.5f);
}

////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////
technique10 ColorTechnique
{
    pass pass0
    {
        SetVertexShader(CompileShader(vs_4_0, ColorVertexShader()));
        SetPixelShader(CompileShader(ps_4_0, ColorPixelShader()));
        SetGeometryShader(NULL);
    }
}
