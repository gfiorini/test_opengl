#vertex shader
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uvCoord;
layout(location = 2) in vec3 color;

out vec2 v_UvCoord;
out vec3 v_Color;

uniform mat4 u_MVP;

void main() {
    gl_Position = u_MVP * vec4(position, 0, 1);
    v_UvCoord = uvCoord;
    v_Color = color;
}

#fragment shader
#version 330 core

uniform sampler2D u_Texture;
in vec2 v_UvCoord;
in vec3 v_Color;
out vec4 color;

void main() {
    vec4 texColor = texture(u_Texture, v_UvCoord);
    color = texColor;
}
