#version 330 core
out vec4 color;

in float DistanceFromView;

uniform float viewDistance;

void main()
{
    color = vec4((1.0f-(DistanceFromView/viewDistance))); // Set all 4 vector values to 1.0f
}