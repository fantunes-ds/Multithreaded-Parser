#version 450 core

struct LightSource
{
	vec3 Position;
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	vec3 Direction;
};

uniform LightSource lightSource;

uniform vec3 ViewPos;

uniform sampler2D objectTexture;

uniform bool useTexture;

out vec4 FragColor;
  
const float shininess = 64.0f;
const vec3 diffuseColor = vec3(1.0f);
const vec3 specularColor = vec3(1.0f);

in VS_OUT
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

vec3 Phong(vec3 lightDirection, vec3 diffuseMapRGB, vec3 specularMapRGB, float luminosity, vec3 viewDir)
{
    vec3 reflectDir = reflect(-lightDirection, fs_in.Normal);
    float diffuseCoef = max(dot(fs_in.Normal, lightDirection), 0.0);
    float specularCoef = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    return 
        diffuseMapRGB * diffuseCoef * luminosity +
        specularMapRGB * specularCoef * luminosity;
}

vec3 CalcDirectionalLight(LightSource light, vec3 diffuseMapRGB, vec3 specularMapRGB, vec3 viewDir)
{
    return Phong
    (
        -light.Direction,
        diffuseMapRGB * light.Diffuse,
        specularMapRGB * light.Specular,
        1.0,
        viewDir
    );
}

void main()
{
    vec3 viewDir = normalize(ViewPos - fs_in.FragPos);

    vec4 diffuseMap     = vec4(diffuseColor, 1.0);
    vec4 specularMap    = vec4(specularColor, 1.0);

    vec3 diffuseMapRGB = diffuseMap.rgb;
    vec3 specularMapRGB = specularMap.rgb;

    if (useTexture)
    {
        FragColor = texture(objectTexture, fs_in.TexCoords) * vec4(CalcDirectionalLight(lightSource, diffuseMapRGB, specularMapRGB, viewDir),1);
    }
    else
    {
        FragColor = vec4(CalcDirectionalLight(lightSource, diffuseMapRGB, specularMapRGB, viewDir),1);
    }
}   