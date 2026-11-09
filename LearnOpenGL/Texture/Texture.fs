#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// Sampler 텍스처 객체를 위한 내장 데이터 타입
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // texture : 텍스처의 색상을 샘플링하기 위해 사용
    // 첫 번째 인수 - 텍스처 샘플러
    // 두 번째 인수 - 해당 텍스처 좌표를 받음.
    //FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);

    // mix - 두 값을 입력으로 받아 세 번째 인수를 기준으로 두 값 사이를 선형 보간함.
    //       세 번째 값이 0.0이면 첫 번째를, 1.0이면 두 번째 입력값을 반환

    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);

}