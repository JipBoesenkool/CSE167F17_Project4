#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct DirLight {
    vec3 direction;
    vec3 color;
};

struct PointLight {
    vec3 position;
    vec3 color;
};

// Functions prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

#define NR_POINT_LIGHTS 4

in vec3 FragPos;
in vec3 Normal;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLight;

void main()
{
    // Properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Phase 1: Directional lighting
    vec3 result;// = CalcDirLight(dirLight, norm, viewDir);

    // Phase 2: Point lights
    result += CalcPointLight(pointLight, norm, FragPos, viewDir);

    // Phase 3: Spot light
    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    color = vec4(result, 1.0);
}

// Calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light.color * material.ambient;

    // Diffuse
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.color * material.diffuse;

    // Specular
    float specularStrength = 0.5;
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = specularStrength * light.color * spec * material.specular;

    //Result
    vec3 result = ambient + diffuse + specular;
    return result;
}

// Calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light.color * material.ambient;

    // Diffuse
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.color * diff * material.diffuse;

    // Specular
    float specularStrength = 0.5;
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = specularStrength * light.color * spec * material.specular;

    // Attenuation
    float distance    = length(light.position - FragPos);
    //float k = 0.09f;
    //float linearAttenuation = k * length( (light.position-fragPos) );
    float attenuation = 1.0f / (1.0f + 0.09f * distance + 0.0032f * (distance * distance));

    //combined
    vec3 result = ambient + diffuse + specular;
    result *= attenuation;
    return result;
}