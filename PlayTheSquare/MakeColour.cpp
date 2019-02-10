#include "MakeColour.h"
#include "Arduino.h"

// Convert HSL (Hue, Saturation, Lightness) to RGB (Red, Green, Blue)
//
//   hue:        0 to 359 - position on the color wheel, 0=red, 60=orange,
//                            120=yellow, 180=green, 240=blue, 300=violet
//
//   saturation: 0 to 100 - how bright or dull the color, 100=full, 0=gray
//
//   lightness:  0 to 100 - how light the color is, 100=white, 50=color, 0=black
//
int makeColor(unsigned int hue, unsigned int saturation, unsigned int lightness)
{
  unsigned int red, green, blue;
  unsigned int var1, var2;

  if (hue > 359) hue = hue % 360;
  if (saturation > 100) saturation = 100;
  if (lightness > 100) lightness = 100;

  // algorithm from: http://www.easyrgb.com/index.php?X=MATH&H=19#text19
  if (saturation == 0) {
    red = green = blue = lightness * 255 / 100;
  } else {
    if (lightness < 50) {
      var2 = lightness * (100 + saturation);
    } else {
      var2 = ((lightness + saturation) * 100) - (saturation * lightness);
    }
    var1 = lightness * 200 - var2;
    red = h2rgb(var1, var2, (hue < 240) ? hue + 120 : hue - 240) * 255 / 600000;
    green = h2rgb(var1, var2, hue) * 255 / 600000;
    blue = h2rgb(var1, var2, (hue >= 120) ? hue - 120 : hue + 240) * 255 / 600000;
  }
  return (red << 16) | (green << 8) | blue;
}

unsigned int h2rgb(unsigned int v1, unsigned int v2, unsigned int hue)
{
  if (hue < 60) return v1 * 60 + (v2 - v1) * hue;
  if (hue < 180) return v2 * 60;
  if (hue < 240) return v1 * 60 + (v2 - v1) * (240 - hue);
  return v1 * 60;
}

// algorithm from: http://www.easyrgb.com/index.php?X=MATH&H=19#text19
unsigned int rgb2h(unsigned int R, unsigned int G, unsigned int B)
{
  //R, G and B input range = 0..255
  //H, S and L output range = 0..1.0
  float H;
  float S;
  float L;
  
  unsigned int var_R = ( R / 255 );
  unsigned int var_G = ( G / 255 );
  unsigned int var_B = ( B / 255 );
  
  unsigned int var_Min = min( var_R, min(var_G, var_B));    //Min. value of RGB
  unsigned int var_Max = max( var_R, max(var_G, var_B));    //Max. value of RGB
  unsigned int del_Max = var_Max - var_Min;             //Delta RGB value
  
  L = ( var_Max + var_Min )/ 2.0;
  
  if ( del_Max == 0 )                     //This is a gray, no chroma...
  {
      H = 0;
      S = 0;
  }
  else                                    //Chromatic data...
  {
     if ( L < 0.5 )
       S = del_Max*1.0 / ( var_Max + var_Min );
     else
       S = del_Max*1.0 / ( 2 - var_Max - var_Min );
  
     float del_R = ( ( ( var_Max - var_R ) / 6.0 ) + ( del_Max / 2.0 ) ) / del_Max;
     float del_G = ( ( ( var_Max - var_G ) / 6.0 ) + ( del_Max / 2.0 ) ) / del_Max;
     float del_B = ( ( ( var_Max - var_B ) / 6.0 ) + ( del_Max / 2.0 ) ) / del_Max;
  
     if      ( var_R == var_Max ) 
       H = del_B - del_G;
     else if ( var_G == var_Max ) 
       H = ( 1 / 3.0 ) + del_R - del_B;
     else if ( var_B == var_Max ) 
       H = ( 2 / 3.0 ) + del_G - del_R;
  
     if ( H < 0 ) 
       H += 1;
     if ( H > 1 ) 
       H -= 1;
  }  
  return H*360;
}

