// version
#version 330

// output color
layout(location = 0) out vec4 OutColor;

uniform float Time;
uniform int PartNo;
 
// input data (from vertex shader)
in vec4 DrawColor;
in vec3 DrawPos;
in vec3 DrawNormal;

void main( void )
{
  /*
  if (DrawPos.z > 33.5 + 35 * sin(5 * Time))
    //discard;
    OutColor = vec4(1, 0, 0, 1);//DrawColor
  else
  */

  vec3 L = normalize(vec3(sin(Time), 1, cos(Time)));

  float nl = max(dot(L, normalize(DrawNormal)), 0);
  vec4 DrColor = DrawColor;

  //left and right shassi
  if (PartNo == 1 || PartNo == 3)
    DrColor = vec4(1, 0, 0, 1);
  //left and right shassi door
  if (PartNo == 2 || PartNo == 4 || PartNo == 2)
    DrColor = vec4(1, 1, 0, 1);
  //forward wheel(0) and shassi(5)
  if (PartNo == 0 || PartNo == 5)
    DrColor = vec4(0, 0, 1, 1);
  //?
  if (PartNo == 6)
    DrColor = vec4(1, 1, 1, 0.5);
  // engine and main corpus 
  if (PartNo == 11)
    DrColor = vec4(1, 1, 0, 1);
  // Tail vertical
  if (PartNo == 8 || PartNo == 10 || PartNo == 7)
    DrColor = vec4(0, 0, 1, 1);
  // Wings 
  if (PartNo == 12)
    DrColor = vec4(1, 0, 1, 1);

  // Engines vints 
  if (PartNo == 13 || PartNo == 14)
    DrColor = vec4(0, 1, 1, 1);
  // engine forward corpus  
  if (PartNo == 15)
    DrColor = vec4(0, 0, 1, 1);
  // engine axes, windows, Tail horizontal
  if (PartNo == 16)
    DrColor = vec4(1, 0, 0, 1);
  // engine tail
  if (PartNo == 17)
    DrColor = vec4(0.3, 0.5, 0.7, 1);

  //?
  if (PartNo == 9)
    DrColor = vec4(0.5, 0.5, 0, 1);

  /* 
  if (PartNo != 9 || PartNo != 7 || PartNo != 10 || PartNo != 18)
    return;
  */
  OutColor = DrColor * nl;
}
