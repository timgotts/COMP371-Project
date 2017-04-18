#version 330 core
out vec4 color;

in float DistanceFromView;

uniform float viewDistance;

void main()
{
	vec3 result = vec3(1.0f-(DistanceFromView/viewDistance)*0.2f);
    color = vec4(result,1.0f); 
}