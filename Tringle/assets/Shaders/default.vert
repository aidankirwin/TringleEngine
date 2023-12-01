#version 330 core

layout(location = 0) in vec3 AHHHH;
layout(location = 1) in vec2 uv;

out vec2 texCoord;



void main(void)
{
	texCoord = uv;
    gl_Position = vec4(AHHHH, 1.0);
}