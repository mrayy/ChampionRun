
attribute vec4 a_position;
attribute vec2 a_texCoord;							
attribute vec4 a_color;

#ifdef GL_ES
varying lowp vec4 v_fragmentColor;					
varying mediump vec2 v_texCoord;					
#else												
varying vec4 v_fragmentColor;						
varying vec2 v_texCoord;							
#endif			


uniform float u_time;

const float speed=1.0;
const float bendFactor=2.0;

void main()
{
    float height=1.0-a_texCoord.y;
    float offset=pow(height,2.5);
    offset*=sin(u_time*speed)*bendFactor;
    
    gl_Position = CC_MVPMatrix * (a_position+vec4(offset,0,0,0));
    v_fragmentColor = a_color;
    v_texCoord = a_texCoord;
}
