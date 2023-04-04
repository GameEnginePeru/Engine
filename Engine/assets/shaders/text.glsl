#shader vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in int a_EntityID;

layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
};

struct VertexOutput
{
	vec4 color;
	vec2 texCoord;
	float texIndex;
};

layout(location = 0) out VertexOutput v_Output;
layout(location = 3) out flat int v_EntityID;


void main()
{
	v_Output.texCoord = a_TexCoord;
	v_Output.color = a_Color;
	v_Output.texIndex = a_TexIndex;
	v_EntityID = a_EntityID;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#shader fragment
#version 450 core

layout(location = 0) out vec4 color;
layout(location = 1) out int color2;

struct VertexOutput
{
	vec4 color;
	vec2 texCoord;
	float texIndex;
};

layout(location = 0) in VertexOutput v_Input;
layout(location = 3) in flat int v_EntityID;

uniform sampler2D[32] u_Texture;

void main()
{
	int tid = int(v_Input.texIndex + 0.5);
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_Texture[tid], v_Input.texCoord).r);
	
	color = v_Input.color * sampled;
	color2 = v_EntityID;
}