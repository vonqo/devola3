#version 330

// Robin Green, Dec 2016,
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// Vonqo, modified

uniform vec2 resolution;
uniform sampler2D texture1;
uniform float noiser;

in vec2 vTexCoord;
out vec4 outputColor;

//Darken
vec3 darken (vec3 target, vec3 blend){
    return min (target, blend);   
}

//Multiply
vec3 multiply (vec3 target, vec3 blend){
    return target*blend;
}

//Color Burn
vec3 colorBurn (vec3 target, vec3 blend){
    return 1.0 - (1.0 - target)/ blend;
}

//Linear Burn
vec3 linearBurn (vec3 target, vec3 blend){
    return target + blend - 1.0;
}

//Lighten
vec3 lighten (vec3 target, vec3 blend){
    return max (target, blend);
}

//Screen
vec3 screen (vec3 target, vec3 blend){
    return 1.0 - (1.0 - target) * (1.0 - blend);
}

//Color Dodge
vec3 colorDodge (vec3 target, vec3 blend){
    return target / (1.0 - blend);
}

//Linear Dodge
vec3 linearDodge (vec3 target, vec3 blend){
    return target + blend;
}

//Overlay
vec3 overlay (vec3 target, vec3 blend){
    vec3 temp;
    temp.x = (target.x > 0.5) ? (1.0-(1.0-2.0*(target.x-0.5))*(1.0-blend.x)) : (2.0*target.x)*blend.x;
    temp.y = (target.y > 0.5) ? (1.0-(1.0-2.0*(target.y-0.5))*(1.0-blend.y)) : (2.0*target.y)*blend.y;
    temp.z = (target.z > 0.5) ? (1.0-(1.0-2.0*(target.z-0.5))*(1.0-blend.z)) : (2.0*target.z)*blend.z;
    return temp;
}

//Soft Light
vec3 softLight (vec3 target, vec3 blend){
 vec3 temp;
    temp.x = (blend.x > 0.5) ? (1.0-(1.0-target.x)*(1.0-(blend.x-0.5))) : (target.x * (blend.x + 0.5));
    temp.y = (blend.y > 0.5) ? (1.0-(1.0-target.y)*(1.0-(blend.y-0.5))) : (target.y * (blend.y + 0.5));
    temp.z = (blend.z > 0.5) ? (1.0-(1.0-target.z)*(1.0-(blend.z-0.5))) : (target.z * (blend.z + 0.5));
    return temp;   
}

//Hard Light
vec3 hardLight (vec3 target, vec3 blend){
    vec3 temp;
    temp.x = (blend.x > 0.5) ? (1.0-(1.0-target.x)*(1.0-2.0*(blend.x-0.5))) : (target.x * (2.0*blend.x));
    temp.y = (blend.y > 0.5) ? (1.0-(1.0-target.y)*(1.0-2.0*(blend.y-0.5))) : (target.y * (2.0*blend.y));
    temp.z = (blend.z > 0.5) ? (1.0-(1.0-target.z)*(1.0-2.0*(blend.z-0.5))) : (target.z * (2.0*blend.z));
    return temp;
}

//Vivid Light
vec3 vividLight (vec3 target, vec3 blend){
     vec3 temp;
    temp.x = (blend.x > 0.5) ? (1.0-(1.0-target.x)/(2.0*(blend.x-0.5))) : (target.x / (1.0-2.0*blend.x));
    temp.y = (blend.y > 0.5) ? (1.0-(1.0-target.y)/(2.0*(blend.y-0.5))) : (target.y / (1.0-2.0*blend.y));
    temp.z = (blend.z > 0.5) ? (1.0-(1.0-target.z)/(2.0*(blend.z-0.5))) : (target.z / (1.0-2.0*blend.z));
    return temp;
}

//Linear Light
vec3 linearLight (vec3 target, vec3 blend){
    vec3 temp;
    temp.x = (blend.x > 0.5) ? (target.x)+(2.0*(blend.x-0.5)) : (target.x +(2.0*blend.x-1.0));
    temp.y = (blend.y > 0.5) ? (target.y)+(2.0*(blend.y-0.5)) : (target.y +(2.0*blend.y-1.0));
    temp.z = (blend.z > 0.5) ? (target.z)+(2.0*(blend.z-0.5)) : (target.z +(2.0*blend.z-1.0));
    return temp;
}

//Pin Light
vec3 pinLight (vec3 target, vec3 blend){
     vec3 temp;
    temp.x = (blend.x > 0.5) ? (max (target.x, 2.0*(blend.x-0.5))) : (min(target.x, 2.0*blend.x));
    temp.y = (blend.y > 0.5) ? (max (target.y, 2.0*(blend.y-0.5))) : (min(target.y, 2.0*blend.y));
    temp.z = (blend.z > 0.5) ? (max (target.z, 2.0*(blend.z-0.5))) : (min(target.z, 2.0*blend.z));
    return temp;
}

//Difference
vec3 difference (vec3 target, vec3 blend){
    return abs (target - blend);
    
}
//Exclusion
vec3 exclusion (vec3 target, vec3 blend){
    return 0.5 - 2.0*(target-0.5)*(blend-0.5);
}

//Subtract (thanks to Brandondorf9999)
vec3 subtract (vec3 target, vec3 blend){
    return target - blend;
}

//Divide (thanks to Brandondorf9999)
vec3 divide (vec3 target, vec3 blend){
 return target/blend;   
}

void main()
{
	vec2 uv = gl_FragCoord.xy / resolution.xy;
       
    // calculate the intensity bucket for this pixel based on column height (padded at the top)
    const float max_value = 270.0;
    const float buckets = 512.0;
    float bucket_min = log( max_value * floor(uv.y * buckets) / buckets );
    float bucket_max = log( max_value * floor((uv.y * buckets) + 1.0) / buckets );
    
    // count the count the r,g,b and luma in this column that match the bucket
    vec4 count = vec4(0.0, 0.0, 0.0, 0.0);
    for( int i=0; i < 512; ++i ) {
        float j = float(i) / buckets;
        vec4 pixel = texture(texture1, vec2(uv.x, j )) * 256.0;
        
        // calculate the Rec.709 luma for this pixel
        pixel.a = pixel.r * 0.2126 + pixel.g * 0.7152 + pixel.b * 0.0722;

        vec4 logpixel = log(pixel);
        if( logpixel.r >= bucket_min && logpixel.r < bucket_max) count.r += 1.0;
        if( logpixel.g >= bucket_min && logpixel.g < bucket_max) count.g += 1.0;
        if( logpixel.b >= bucket_min && logpixel.b < bucket_max) count.b += 1.0;
        if( logpixel.a >= bucket_min && logpixel.a < bucket_max) count.a += 1.0;
    }
    
    // sum luma into RGB, tweak log intensity for readability
    const float gain = 0.4;
    const float blend = 0.6;
    count.rgb = log( mix(count.rgb, count.aaa, blend) ) * (gain);


    // output
    // outputColor = count;
    vec3 src = texture(texture1, uv).xyz;
    // vec3 mixed = vividLight(count.xyz, src);
    // vec3 mixed = linearLight(count.xyz, src);
    vec3 mixed = darken(count.xyz, src);
    outputColor = vec4(mixed, 1.0f);

}