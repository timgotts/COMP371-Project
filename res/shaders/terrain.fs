

#version 330 core

in vec3 vPos;

out vec4 color;



void main()

{
	
	color = vec4(
		0.961f - max(0, ((-vPos.y/1.0f) * 0.0195f)), 
		0.840f - max(0, ((-vPos.y/1.0f) * 0.02734f)),
		0.6875f - max(0, ((-vPos.y/1.0f) * 0.0234f)), 
		1.0f
		);
}

