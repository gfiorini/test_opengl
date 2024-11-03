#vertex shader
#version 330 core
layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uvCoord;
layout(location = 2) in vec3 color;

out vec2 v_UvCoord;
out vec3 v_Color;

void main() {
    gl_Position = vec4(position, 0, 1.0);
    v_UvCoord = uvCoord;
    v_Color = color;
}

#fragment shader
#version 330 core

in vec2 v_UvCoord;
in vec3 v_Color;
out vec4 color;

void main() {
    //color = vec4(1, 1, 0, 1);
    color = vec4(v_Color, 1);
}
