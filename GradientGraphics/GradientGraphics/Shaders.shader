struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

cbuffer ConstantBuffer : register(b0)
{
    matrix World;
};
cbuffer ColorBuffer : register(b1)
{
    float4 colorShift;
};

VOut VShader(float4 position : POSITION, float4 color : COLOR)
{
    VOut output;

    output.position = mul(position, World);
    output.color = color;

    return output;
}



float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
    float normalizedValue = clamp((position.r / colorShift.g) + colorShift.r, 0.0f, 1.0f);;

    float4 red = float4(color.r, 0.0, 0.0, 1.0);
    float4 green = float4(0.0, color.g, 0.0, 1.0);
    float4 blue = float4(0.0, 0.0, color.b, 1.0);

    float t1 = smoothstep(0.0, 0.5, normalizedValue);
    float t2 = smoothstep(0.5, 1.0, normalizedValue);

    float4 finalColor = lerp(lerp(red, green, t1), lerp(green, blue, t2), t2);

    return finalColor;
}