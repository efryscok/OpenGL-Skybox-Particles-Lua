#version 450

in vec4 exColour;
in vec3 exToEye;
in vec3 exNormal;
in vec4 exTexture;
in vec3 exEyePosition;
in vec3 exWorldPosition;

uniform bool hasTexture;
uniform bool isCubeMap;
uniform bool isImposter;
uniform sampler2D texSampler;
uniform samplerCube cubeMapSampler;

out vec4 out_Colour;

void main() {
	if (isCubeMap) {
		out_Colour = texture(cubeMapSampler, exNormal.xyz);
		out_Colour.a = 1.f;
		return;
	}
	
	if (hasTexture) {
		out_Colour = texture(texSampler, exTexture.xy);

		if (isImposter) {
			if (((out_Colour.r + out_Colour.g + out_Colour.b) / 3.f) < 0.2f) {
				out_Colour.a = 0.f;
			}
		}
		else {
			out_Colour.a = 1.f;
		}

		return;
	}

	out_Colour = vec4(exColour.xyz, 1.0f);

	//float dot = dot(normalize(exToEye), normalize(exNormal)) * 0.7 + 0.3;
	//out_Colour.x *= dot;
	//out_Colour.y *= dot;
	//out_Colour.z *= dot;
	//out_Colour.w = 1.0f;
}