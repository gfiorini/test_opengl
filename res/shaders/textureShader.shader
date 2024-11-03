#vertex shader
#version 330 core
layout(location = 0) in vec2 position;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoords;

void main() {
    gl_Position = vec4(position, 0, 1.0);
    v_TexCoords = texCoord;
}

#fragment shader
#version 330 core
uniform sampler2D u_Texture;

in vec2 v_TexCoord;
layout(location = 0) out vec4 color;

void main() {
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = texColor;
}
