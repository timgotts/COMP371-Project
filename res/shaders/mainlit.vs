#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 Normal;
out vec3 FragPos;
out float Opacity;
out float DistanceFromView;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;
uniform vec3 viewPos;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	FragPos = vec3(model * vec4(position, 1.f));
	Normal = normalMatrix * normal;
	vec4 realPos = model * vec4(position,1.0f);
	DistanceFromView  = distance(vec2(realPos.x, realPos.z), vec2(viewPos.x, viewPos.z));
	Opacity = 1.0f;

}