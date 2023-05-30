#version 330 core
out vec4 fragmentColor;
uniform vec4 ourColor;
void main()
{
    fragmentColor = ourColor;
}