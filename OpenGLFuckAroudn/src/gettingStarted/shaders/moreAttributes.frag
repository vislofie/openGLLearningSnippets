#version 330 core
out vec4 fragmentColor;
in vec3 ourColor;
void main()
{
    fragmentColor = vec4(ourColor, 1.0);
}