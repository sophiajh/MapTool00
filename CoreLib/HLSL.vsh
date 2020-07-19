
cbuffer cb0 : register(b0)
{
	matrix g_MatWorld : packoffset(c0);
	matrix g_MatView : packoffset(c4);
	matrix g_MatProj : packoffset(c8);
	float4 g_Color : packoffset(c12);
	float g_fTime : packoffset(c13.x);
}
//
cbuffer cb1 : register(b1)
{
	matrix	matWorldInverse : packoffset(c0);

	float4	AmbientMaterial : packoffset(c4);
	float4	DiffuseMaterial : packoffset(c5);

	float4	AmbientLight : packoffset(c6);
	float4	DiffuseLight : packoffset(c7);

	float4	LightPos : packoffset(c8);
	float3	LightDir : packoffset(c9);
	float3	vEveDir : packoffset(c10);
	float3	vEyePos	: packoffset(c11);
}
//


cbuffer cb2 : register(b2)
{
	float	g_Coordx : packoffset(c0.x);
	float	g_Coordy : packoffset(c0.y);
	float	g_Coordz : packoffset(c0.z);
	float	temp : packoffset(c0.w);
	float	g_Radius : packoffset(c1.x);
}

struct VS_INstruct
{
	float3 Position		: POSITION;
	float3 Normal		: NORMAL;
	float4 Color		: COLOR;
	float2 Texture		: TEXTURE;
};

struct VS_OUTstruct
{
	float4 Position		: SV_POSITION;
	float3 Normal		: NORMAL;
	float4 Color		: COLOR0;
	float2 Texture		: TEXTUREO;
	///
	float4 Diffuse		: TEXTURE1;
	float3 IncAng		: TEXTURE2;
};

//
float3 Reflect(float3 incident, float3 normal)
{
	float cosI = dot(normal, incident);
	return incident - 2 * cosI * normal;
}
//
VS_OUTstruct VS(VS_INstruct vIn)
{
	VS_OUTstruct vOut = (VS_OUTstruct)0;
	
	vOut.Position = mul(float4(vIn.Position,1.0f), g_MatWorld);
	vOut.IncAng = normalize(vOut.Position.xyz - vEyePos);
	vOut.Position = mul(vOut.Position, g_MatView);
	//vOut.IncAng = mul(vOut.IncAng, g_MatView);
	vOut.Position = mul(vOut.Position, g_MatProj);
	vOut.Normal = vIn.Normal;
	//vOut.IncAng = mul(vOut.IncAng, g_MatProj);

	//vOut.Normal =  normalize(mul(vIn.Normal, (float3x3)matWorldInverse)); //vIn.Normal;//
	//vOut.Normal = vIn.Normal;
	//reflect 연산을 위한 normal필요...

	//vOut.Texture = vIn.Texture * 10;
	vOut.Texture = vIn.Texture;
	//vOut.Color.x = dot(vOut.Normal, normalize(-LightDir));
	//vOut.Color.y = dot(vOut.Normal, normalize(-LightDir));// vIn.c * g_MeshColor;
	//vOut.Color.z = dot(vOut.Normal, normalize(-LightDir));
	//vOut.Color.w = 1.0f;
	vOut.Color = vIn.Color;
	return vOut;
}

VS_OUTstruct VS_Line(VS_INstruct input)
{
	VS_OUTstruct Output = (VS_OUTstruct)0;
	float3 vPos;
	vPos.x = input.Position.x;
	vPos.y = input.Position.y;
	vPos.z = input.Position.z;
	Output.Position = float4(vPos, 1.0f);
	//Output.Position = float4(input.Position, 1.0f);
	Output.Position = mul(Output.Position, g_MatWorld);
	Output.Position = mul(Output.Position, g_MatView);
	Output.Position = mul(Output.Position, g_MatProj);
	//Output.Normal = input.Normal;
	Output.Color = input.Color;
	//Output.Texture = input.Texture;
	return Output;
}