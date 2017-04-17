#version 330 core
layout(location = 0) in vec3 position;

out float DistanceFromView;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPos;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	vec4 realPos = model * vec4(position,1.0f);
	DistanceFromView  = distance(vec2(realPos.x, realPos.z), vec2(viewPos.x, viewPos.z));
}