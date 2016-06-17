// version
#version 330

// output color
layout(location = 0) out vec4 OutColor;

uniform float Time;
uniform int PartNo;
uniform int IsNor;
uniform int IsPart;
 
// input data (from vertex shader)
in vec4 DrawColor;
in vec3 DrawPos;
in vec3 DrawNormal;

void main( void )
{
  int i = PartNo;
  /*
  if (DrawPos.z > 33.5 + 35 * sin(5 * Time))
    //discard;
    OutColor = vec4(1, 0, 0, 1);//DrawColor
  else
  */

  vec3 L = normalize(vec3(sin(Time), 1, cos(Time)));

  float nl = max(dot(L, normalize(DrawNormal)), 0);
  vec4 DrColor = DrawColor;

  while (i >= 20)
    i -= 20;

  if (i == 0)
    DrColor = vec4(0, 0, 0, 1);
  else if (i == 1)
    DrColor = vec4(1, 1, 1, 1);
  else if (i == 2)
    DrColor = vec4(1, 0, 0, 1);
  else if (i == 3)
    DrColor = vec4(0, 1, 0, 1);
  else if (i == 4)
    DrColor = vec4(0, 0, 1, 1);
  else if (i == 5)
    DrColor = vec4(1, 1, 0, 1);
  else if (i == 6)
    DrColor = vec4(0, 1, 1, 1);
  else if (i == 7)
    DrColor = vec4(1, 0, 1, 1);
  else if (i == 8)
    DrColor = vec4(0.5, 0.5, 0.5, 1);
  else if (i == 9)
    DrColor = vec4(0.5, 0, 0, 1);
  else if (i == 10)
    DrColor = vec4(0, 0.5, 0, 1);
  else if (i == 11)
    DrColor = vec4(0, 0, 0.5, 1);
  else if (i == 12)
    DrColor = vec4(0.5, 0.5, 0, 1);
  else if (i == 13)
    DrColor = vec4(0, 0.5, 0.5, 1);
  else if (i == 14)
    DrColor = vec4(0.5, 0, 0.5, 1);
  else if (i == 15)
    DrColor = vec4(0.7, 0.7, 0.7, 1);
  else if (i == 16)
    DrColor = vec4(0.7, 0, 0, 1);
  else if (i == 17)
    DrColor = vec4(0, 0.7, 0, 1);
  else if (i == 18)
    DrColor = vec4(0, 0, 0.7, 1);
  else if (i == 19)
    DrColor = vec4(0.7, 0.7, 0, 1);

  if (IsNor == 0)
    nl = 1;
  /* 
  if (PartNo != 9 || PartNo != 7 || PartNo != 10 || PartNo != 18)
    return;
  */
  OutColor = DrColor * nl;
}
