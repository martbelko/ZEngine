#type vertex
#version 460 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoords;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec4 v_Color;
out vec2 v_TexCoords;

void main()
{
	v_TexCoords = vec2(a_TexCoords.x, 1.0 - a_TexCoords.y);
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 460 core

in vec2 v_TexCoords;
			
uniform sampler2D u_Texture;

out vec4 o_Color;

void main()
{
	o_Color = texture(u_Texture, v_TexCoords);
}