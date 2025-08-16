#version 440

layout(location = 0) in vec2 texCoord;
layout(location = 1) in vec2 fragCoord;
layout(location = 0) out vec4 fragColor;

layout(std140, binding = 0) uniform buf {
    mat4 qt_Matrix;
    float qt_Opacity;
    float pixelSize;
    vec3 iResolution;
};

layout(binding = 1) uniform sampler2D iSource;

void main() {

    vec2 uv = fragCoord/iResolution.xy;
    float px = pixelSize *(1./iResolution.x);
    float py = pixelSize *(1./iResolution.y);
    vec2 c = vec2(px*floor(uv.x/px), py*floor(uv.y/py));
    fragColor = texture(iSource, c);

    /*int sx = int(texCoord.x/pixelSize);
    int sy = int(texCoord.y/pixelSize);
    int dx = int(sx*pixelSize);
    int dy = int(sy*pixelSize);

    vec4 color = texture(iSource, texCoord);
    for(int ix = 0; ix< pixelSize; ++ix) {
        if(dx+ix < iResolution.x) {
            for(int iy = 0; iy< pixelSize; ++iy) {
                if(dy+iy < iResolution.y) {
                    vec2 pos = vec2(float(dx+ix), float(dy+iy));
                    if(ix == 0 && iy == 0)
                        color = texture(iSource, pos);
                    else
                        color = mix(color, texture(iSource, pos), 0.5);
                }
            }
        }
    }

    fragColor = color * qt_Opacity;*/
}
