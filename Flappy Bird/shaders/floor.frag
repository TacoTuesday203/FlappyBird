#version 150

uniform sampler2D textureUniform;

in vec4 frag_Col;
in vec2 frag_UV;

out vec4 final_Col;

void main() {
    vec4 textureRGBA = texture(textureUniform, frag_UV);
    final_Col = frag_Col * textureRGBA;
}