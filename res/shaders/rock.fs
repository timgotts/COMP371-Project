#version 330 core

in vec3 vPos;
in vec4 vNorm;

out vec4 color;


void main()
{
	color = vec4(vNorm.r, vNorm.g, vNorm.b, 1.0f);
	color.b += 0.2f;
}