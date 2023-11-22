#version 330 core
layout(location = 0) out vec4 color;

uniform vec2 resolution;
uniform float zoom;
uniform vec2 position;

const float MAX_ITER = 500.0;

float mandelbrot(vec2 uv) {
    vec2 c = 4 * uv - vec2(0.7, 0.0);
    c = c / pow(zoom, 4.0) - position;
    vec2 z = vec2(0.0);
    float iter = 0.0;
    for (float i; i < MAX_ITER; ++i){
        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
        if (dot(z, z) > 4.0)
            return iter/ MAX_ITER; 
        iter++;
    }
    return 0.0;
}
vec3 hash13(float m) {
    float x = fract(sin(m));
    float y = fract(sin(m+x));
    float z = fract(sin(m+y));
    return vec3(x,y,z);
}


void main(){
    vec2 uv = (gl_FragCoord.xy - 0.5*resolution.xy) / resolution.y;
    vec3 col = vec3(0.0);

    float m = mandelbrot(uv);
    col += hash13(m);
    col = pow(col, vec3(0.8));
    color = vec4(col, 1.0);
};