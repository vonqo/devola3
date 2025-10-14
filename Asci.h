//
//  Asci.h
//  devola3
//
//  Created by Vonqo on 2025.05.27.
//

#ifndef ofxPostGlitchExample_Asci_h
#define ofxPostGlitchExample_Asci_h

#include "ofMain.h"
#include "PGShaderConstants.h"

class Asci : public ofShader
{
public:
    
    Asci() : ofShader()
    {
        string vertexShader;
        string fragmentShader;
        
        if(ofIsGLProgrammableRenderer())
        {
            vertexShader = gl330VertShader;
            fragmentShader = GLSL330(
                                    #ifdef GL_ES
                                     precision mediump float;
                                    #endif
                                     
                                     uniform sampler2DRect image;
                                     uniform int imgWidth;
                                     uniform int imgHeight;
                                     uniform int trueWidth;
                                     uniform int trueHeight;
                                     uniform float weight;
                                     
                                     in vec3 pos;
                                     out vec4 outputColor;
                                     
                                     float character(int n, vec2 p)
                                     {
                                         p = floor(p*vec2(-4.0, 4.0) + 2.5);
                                         if (clamp(p.x, 0.0, 4.0) == p.x)
                                         {
                                             if (clamp(p.y, 0.0, 4.0) == p.y)
                                             {
                                                 int a = int(round(p.x) + 5.0 * round(p.y));
                                                 if (((n >> a) & 1) == 1) return 1.0;
                                             }
                                         }
                                         return 0.0;
                                     }
                                     
                                     void main (void)
                                     {
                                         vec2 resolution = vec2(float(trueWidth),float(trueHeight));
                                         vec2 pix = gl_FragCoord.xy;
                                         vec2 texCoord = vec2(pos.x, pos.y);
                                         vec2 uv = texCoord.xy/resolution.xy;
                                         
                                         outputColor = texture(image, uv);
                                         
//                                         vec3 col = texture(image, floor(pix/8.0)*8.0/resolution.xy).rgb;
//                                         float gray = 0.3 * col.r + 0.59 * col.g + 0.11 * col.b;
//                                         int n = 4096;
//                                         
//                                         if (gray > 0.1326) n = 17318431; // L
//                                         if (gray > 0.3209) n = 18732593; // M
//                                         if (gray > 0.5605) n = 32032318; // D
//                                         if (gray > 0.7302) n = 32045630; // B
//                                         
//                                         vec2 p = (mod(pix/12, 2.0)) - vec2(1.0);
//                                         
//                                         col = col*character(n, p);
//                                         outputColor = vec4(col, 1.0);
                                     }
                                     
                                     );
        }
        else
        {
            vertexShader = gl120VertShader;
            fragmentShader = GLSL120(
                                     uniform sampler2DRect image;
                                     uniform int imgWidth;
                                     uniform int imgHeight;
                                     uniform float weight;
                                     
                                     varying vec3 pos;
                                     
                                     float character(int n, vec2 p)
                                     {
                                         p = floor(p*vec2(-4.0, 4.0) + 2.5);
                                         if (clamp(p.x, 0.0, 4.0) == p.x)
                                         {
                                             if (clamp(p.y, 0.0, 4.0) == p.y)
                                             {
                                                 int a = int(round(p.x) + 5.0 * round(p.y));
                                                 if (((n >> a) & 1) == 1) return 1.0;
                                             }
                                         }
                                         return 0.0;
                                     }
                                     
                                     void main (void) {
                                         gl_FragColor.rgba = vec4(0.0,0.0,0.0,0.0);
                                     }
                                     );
        }
        
        setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
        setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader);
        bindDefaults();
        linkProgram();
    }
    
    ~Asci() { unload(); }
};

#endif
