#shader vertex
#version 450 core 
layout(location = 0) in vec4 position;


uniform mat4 u_ModelViewProjection;


void main()                         
{                                  
	gl_Position = u_ModelViewProjection * position;
};


#shader fragment
#version 450 core

out vec4 FragColor;
void main()                         
{                      
	FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}; 