#version 460 core

uniform vec3 uColor;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vUV;

out vec4 fragColor;

void main() {
    fragColor = vec4(uColor, 1.0);
}
