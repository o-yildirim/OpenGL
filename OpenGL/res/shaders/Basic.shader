#shader vertex
#version 450 core 
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 a_Color;


uniform mat4 u_ModelViewProjection;

out vec4 v_Color;

void main()                         
{                                  
	v_Color = a_Color;	
	gl_Position = u_ModelViewProjection * position;
};


#shader fragment
#version 450 core

in vec4 v_Color;
out vec4 color;
void main()                         
{                      
	color = v_Color;
}; 