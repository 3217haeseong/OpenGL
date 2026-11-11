#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// Sampler 텍스처 객체를 위한 내장 데이터 타입
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0f - TexCoord.x, TexCoord.y)), 0.2);
}