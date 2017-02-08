#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

uniform sampler2DRect diffuseTexture;

uniform vec2 cropPos;

uniform vec2 cropResolution;

uniform vec2 vidResolution;

uniform vec2 windowResolution;

void main() {
    //Getting coordinates of the current pixel in texture
    vec2 pos = gl_FragCoord.xy;
    pos /= windowResolution;
    pos.y = 1.0 - pos.y;
    pos *= windowResolution;
    vec3 col;
    if(pos.x < cropPos.x || pos.y < cropPos.y || pos.x > cropPos.x + cropResolution.x || pos.y > cropPos.y + cropResolution.y) {
        col = vec3(0.5);
    } else {
        pos *= vidResolution / windowResolution;
        col = texture2DRect(diffuseTexture, pos).xyz;
    }

    gl_FragColor = vec4(col, 1.0);
}
