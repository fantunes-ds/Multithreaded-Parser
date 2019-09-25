#version 460 core

out vec4 color;

in vec3 frag_pos;
in vec3 o_normal;
in vec3 alightColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    vec3 objectColor = vec3(1.0, 1.0, 1.0);
    vec3 lightColor = alightColor;
	vec3 ambientColor = alightColor;

    vec3 viewDir = normalize(viewPos - frag_pos);
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * ambientColor;
  	
    // diffuse 
    vec3 norm = o_normal;

    vec3 lightDir = normalize(lightPos - frag_pos);

    float checkSide = dot(viewDir, norm);
    
    if(checkSide < 0.0)
        norm = -norm;

    float diff = dot(norm, lightDir) / (length(lightDir) * length(norm));
    diff = clamp(diff, 0, 1);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.8;
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
    float dist = distance(frag_pos, lightPos);
    vec3 result = (ambient + (diffuse * 8) / (dist*dist / 2) + specular) * objectColor;
    vec4 FragColor = vec4(result, 1.0);
    color = FragColor;
};