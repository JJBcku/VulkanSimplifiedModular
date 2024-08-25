#version 450

layout(location = 0) in vec4 inColor;

layout(location = 0) out vec4 outColor;

void main()
{
	vec3 transitionColor = inColor.rgb;
	transitionColor = (vec3(1.055) * pow(transitionColor, vec3(1.0/2.4))) - vec3(0.055);

	outColor = vec4(transitionColor, inColor.a);
}