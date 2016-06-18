// version
#version 330

// shader attributes layout
layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InTexCoord;
layout(location = 2) in vec3 InNormal;
layout(location = 3) in vec4 InColor;

// global variables
uniform mat4 MatrWVP;
uniform mat4 MatrWorld;
uniform mat4 MatrView;
uniform mat4 MatrProj;
uniform int Id;
uniform int IsPart;

// output data
out vec4 DrawColor;
out vec3 DrawPos;
out vec3 DrawNormal;

void main( void )
{
  vec3 Tun = Id * vec3(10000, 0, 0);

  if (IsPart == 0)
    Tun = vec3(0, 0, 0);
  //if (PartNo != 9 && PartNo != 18)
    //return;
  gl_Position = MatrWVP * vec4(InPosition + Tun, 1);

  DrawColor = InColor * (InTexCoord.x + InTexCoord.y); //vec4(InNormal * 2, 1);
    
  DrawPos = InPosition;
  DrawNormal = mat3(inverse(transpose(MatrWorld))) * InNormal;
}
