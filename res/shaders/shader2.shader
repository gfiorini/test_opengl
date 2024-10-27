#vertex shader
#version 330 core
layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;

out vec3 vColor;

void main() {
    gl_Position = vec4(position, 0, 1.0);
    vColor = color;
}

#fragment shader
#version 330 core
out vec4 color;

void main() {
    color = vec4(1, 0, 0, 0.3);
}