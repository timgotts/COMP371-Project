#version 330 core

in vec3 vPos;
in vec4 vNorm;

out vec4 color;



void main()

{
	//color = vec4(vec3(0.2f, 0.8f, 1.0f) * vPos.y + 0.5, 1.0f);
	color = vec4(vNorm.r, vNorm.g, vNorm.b, 1.0f);
	color.b += 0.2f;
}