#version 330 core
layout(location = 0) out vec4 FragColor;

//in vec2 v_TexCoord;
in vec3 v_Color;

//uniform sampler2D u_Texture;

void main(){
    //vec4 texColor = texture(u_Texture, v_TexCoord);
    FragColor = vec4(v_Color, 1.0);
    //FragColor = texColor;
}