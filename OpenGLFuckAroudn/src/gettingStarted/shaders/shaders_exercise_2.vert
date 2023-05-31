#version 330 core
layout (location = 0) in vec3 pos;
uniform float horizontalOffset;

void main()
{
    gl_Position = vec4(pos.x + horizontalOffset, pos.yz, 1.0);
}