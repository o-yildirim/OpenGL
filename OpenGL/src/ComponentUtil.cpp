#include "ComponentUtil.h"

Component* ComponentUtil::CreateComponentFromName(std::string name) 
{
	if (name == "Circle") return new Circle();
	else if (name == "Rectangle") return new Rectangle();
	else if (name == "Camera") return new Camera();
	else if (name == "Transform") return new Transform();
	return nullptr;
}