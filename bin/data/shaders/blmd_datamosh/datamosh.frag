#version 330

#ifdef GL_ES
precision mediump float;
precision mediump int;
#endif

#define PI 3.14159265359
uniform float time;

uniform vec2 resolution;
uniform sampler2D texturePre;
uniform sampler2D textureCur;
uniform float minVel; 
uniform float maxVel; 
uniform float offsetInc;
uniform vec2 offset;
uniform float lambda;
uniform vec2 scale;
uniform float threshold;
uniform float intensity;

in vec2 vTexCoord;
out vec4 outputColor;

vec4 packFlowAsColor(float fx ,float fy, vec2 scale) {
	vec2 flowX = vec2(max(fx, 0.0), abs(min(fx, 0.0))) * scale.x;
	vec2 flowY = vec2(max(fy, 0.0), abs(min(fy, 0.0))) * scale.y;
	float dirY = 1.0;
	if(flowY.x > flowY.y){
		dirY = 0.9;
	}
	vec4 rgbaPacked = vec4(flowX.x, flowX.y, max(flowY.x, flowY.y), dirY);

	return rgbaPacked;
}

vec2 getFlowVector(float fx ,float fy, vec2 scale){
	vec2 flowX = vec2(max(fx, 0.0), abs(min(fx, 0.0))) * scale.x;
	vec2 flowY = vec2(max(fy, 0.0), abs(min(fy, 0.0))) * scale.y;
	float dirY = 1.0;
	if(flowY.x > flowY.y) {
		dirY = -1.0;
	}
	//vec4 rgbaPacked = vec4(flowX.x, flowX.y, max(flowY.x, flowY.y), dirY);

	float x = flowX.x + flowX.y * -1.0;
	float y = max(flowY.x, flowY.y) * dirY;

	return vec2(x, y);
}

vec4 getGray(vec4 inputPix){
	float gray = dot(vec3(inputPix.x, inputPix.y, inputPix.z), vec3(0.3, 0.59, 0.11));
	return vec4(gray, gray, gray, 1.0);
}

vec4 getGrayTexture(sampler2D tex, vec2 texCoord){
	return getGray(texture(tex, texCoord));
}

vec4 getGradientAt(sampler2D current, sampler2D previous, vec2 texCoord, vec2 offset){
	vec4 gradient = getGrayTexture(previous, texCoord + offset) - getGrayTexture(previous, texCoord - offset);
	gradient += getGrayTexture(current, texCoord + offset) - getGrayTexture(current, texCoord - offset);
	return gradient;
}

void main()
{
	vec2 uv = gl_FragCoord.xy/resolution.xy;
    uv.y = 1.0 - uv.y;

	vec4 current = texture(textureCur, uv);
	vec4 prev = texture(texturePre, uv);
	
	vec2 offsetX = vec2(offset.x * offsetInc, 0.0);
	vec2 offsetY = vec2(0.0, offset.y * offsetInc);

	//Frame Differencing (dT)
	vec4 differencing = prev - current;
	float vel = (differencing.r + differencing.g + differencing.b)/3.0;
	// float vel = (differencing.r + (differencing.g * 0.2) + (differencing.b * 0.2));
	float movement = smoothstep(minVel, maxVel, vel);
	vec4 newDifferencing = vec4(movement);
	//movement = pow(movement, 1.0);

	//Compute the gradient (movement Per Axis) (look alike sobel Operation)
	vec4 gradX = getGradientAt(textureCur, texturePre, uv, offsetX);
	vec4 gradY = getGradientAt(textureCur, texturePre, uv, offsetY);

	//Compute gradMagnitude
	vec4 gradMag = sqrt((gradX * gradX) + (gradY * gradY) + vec4(lambda));

	//compute Flow
	vec4 vx = newDifferencing * (gradX / gradMag);
	vec4 vy = newDifferencing * (gradY / gradMag);

	//vec4 flowCoded = packFlowAsColor(vx.r, vy.r, scale);
	vec2 flow = getFlowVector(vx.x, vy.x, vec2(intensity));
	float flowMag = length(flow.xy);

	float stepper = step(threshold, flowMag);
	flow.x = clamp(flow.x, -1.0, 1.0);
	flow.y = clamp(flow.y, -1.0, 1.0);

	vec2 st;
	vec2 texel = vec2(1.0) / resolution;
	// vec2 texel = uv;
	st.x = uv.x + flow.x * texel.x * intensity;
	st.y = uv.y + flow.y * texel.y * intensity;

	//shift rgb
	vec2 shift = vec2(cos(flow.x * PI + time * 0.1), sin(flow.y * PI + time * 0.1)) * 0.0025;
	float r = texture(texturePre, st + shift).r;
	float g = texture(texturePre, st ).g;
	float b = texture(texturePre, st - shift).b;

	vec4 datamosh = texture(texturePre, st);
	datamosh.rgb = vec3(r, g, b) * stepper;

	vec4 color = texture(textureCur, uv); // * vec4(1,0.2,0.2,1);
    outputColor = (color * (1.0 - stepper) + datamosh * stepper);
}
 
