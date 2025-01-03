#vertex shader
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uvCoord;
layout(location = 2) in vec3 color;

out vec2 v_UvCoord;
out vec3 v_Color;

uniform mat4 u_MVP;

void main() {
    gl_Position = u_MVP * vec4(position, 1);
    v_UvCoord = uvCoord;
    v_Color = color;
}

#fragment shader
#version 330 core

in vec2 v_UvCoord;
in vec3 v_Color;
out vec4 color;

void main() {
    color = vec4(1, 1, 0, 1);
}
