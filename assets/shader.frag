#version 300 es
precision mediump float;
in vec3 vertexColor;
in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D ourTexture;
void main() {
    FragColor = texture(ourTexture, TexCoord) * vec4(vertexColor, 1.0);
   // FragColor = vec4(vertexColor, 1.0);
}
