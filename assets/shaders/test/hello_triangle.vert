#version 460 core

out vec3 vColor;

void main() {
    vec2 positions[3] = vec2[3](
        vec2(-0.6, -0.5),
        vec2( 0.6, -0.5),
        vec2( 0.0,  0.6)
    );
    vec3 colors[3] = vec3[3](
        vec3(0.95, 0.97, 1.00),
        vec3(0.85, 0.90, 0.98),
        vec3(0.70, 0.80, 0.95)
    );

    gl_Position = vec4(positions[gl_VertexID], 0.0, 1.0);
    vColor = colors[gl_VertexID];
}