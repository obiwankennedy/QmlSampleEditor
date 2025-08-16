#version 440

layout(location = 0) in vec2 texCoord;
layout(location = 1) in vec2 fragCoord;
layout(location = 0) out vec4 fragColor;

layout(std140, binding = 0) uniform buf {
    mat4 qt_Matrix;
    float qt_Opacity;
};

layout(binding = 1) uniform sampler2D iSource;


void main() {
    fragColor = texture(iSource, texCoord);
    {
            float grayColor = (fragColor.r + fragColor.g + fragColor.b) / 3.0;
            fragColor = mix(fragColor, vec4(vec3(grayColor), fragColor.a), 1.0);
    }
    fragColor = fragColor * qt_Opacity;
}
