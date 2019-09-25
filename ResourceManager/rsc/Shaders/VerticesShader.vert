#version 460 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 aNormal;


out vec4 o_color;
out vec3 alightColor;

out vec3 frag_pos;
out vec3 o_normal;

uniform vec3 lightColor;
uniform mat4 ModelMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 CameraMatrix;

void main()
{
	mat4 m_matrix = transpose(ModelMatrix);
	mat4 v_matrix = transpose(CameraMatrix);;
	mat4 p_matrix = transpose(ProjectionMatrix);

    gl_Position = p_matrix * v_matrix * m_matrix * position;

	frag_pos = vec3(m_matrix * position);

	vec3 normal = normalize(transpose(inverse(mat3(m_matrix))) * aNormal);  
	o_normal = normal;
    
	alightColor = lightColor;
};
