#version 460 core

out vec4 fragColor;

uniform vec3 albedo;

void main() {
    fragColor = vec4(albedo, 1.0);
}
