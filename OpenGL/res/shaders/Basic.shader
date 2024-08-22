#shader vertex
#version 330 core 
layout(location = 0) in vec4 position;
//layout(location = 1) in vec2 texCoord;

//out vec2 v_TexCoord; //v stands for varying.

uniform mat4 u_ModelViewProjection;

void main()                         
{                                  
	gl_Position = u_ModelViewProjection * position;
	//v_TexCoord = texCoord;
};


#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
//in vec2 v_TexCoord;

uniform vec4 u_Color;
//uniform sampler2D u_Texture;
void main()                         
{                      
	//vec4 texColor = texture(u_Texture, v_TexCoord);
	//color = texColor; Comment out to draw texture (also comment out the 3 lines in Application.cpp) 
	color = u_Color;
}; 