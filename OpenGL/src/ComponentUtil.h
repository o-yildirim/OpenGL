#pragma once
#include "Camera.h"
#include "Shapes.h"
#include "Transform.h"


class ComponentUtil
{
public:
	static Component* CreateComponentFromName(std::string name);

	template <typename T>
	static void CastToComponentType(T* component)
	{
		if (Circle* circle = dynamic_cast<Circle*>(component))
		{
			component = circle;
		}
		else if (Rectangle* rectangle = dynamic_cast<Rectangle*>(component))
		{
			component = rectangle;
		}
		else if (Camera* camera = dynamic_cast<Camera*>(component))
		{
			component = camera;
		}
		else if (Transform* transform = dynamic_cast<Transform*>(component))
		{
			component = transform;
		}
	}
	
};