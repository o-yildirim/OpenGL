#include "Shapes.h"


void Shape::to_json(nlohmann::json& json)
{
	json = 
	{
		{this->GetClassName(), {
		{"color", {
			{"r", color[0]},
			{"g", color[1]},
			{"b", color[2]},
			{"a", color[3]}
		}}
	}}
	};
}

void Shape::from_json(nlohmann::json& json)
{
	std::cout << "Adding shape" << std::endl;
	this->color[0] = json.at("color").at("r").get<float>();
	this->color[1] = json.at("color").at("g").get<float>();
	this->color[2] = json.at("color").at("b").get<float>();
	this->color[3] = json.at("color").at("a").get<float>();
}

//RECTANGLE BELOW
Rectangle::Rectangle()
{
    this->_className = "Rectangle";

    this->xLength = 100.0f;
    this->yLength = 100.0f;

    this->positions = new float[24];
    this->indices = new unsigned int[6];
    this->color[0] = 1.0f;//r
    this->color[1] = 1.0f;//g
    this->color[2] = 1.0f;//b
    this->color[3] = 1.0f;//a


    this->SetPositions();
    this->SetIndices();
    this->SetColor();

    this->InitBuffers();
}

void Rectangle::InitBuffers()
{
    this->vertexBuffer.AddData(this->positions, 4 * 6 * sizeof(float));
    this->layout.Push<float>(2);
    this->layout.Push<float>(4);

    this->vertexArray.AddBuffer(this->vertexBuffer, layout);
    this->indexBuffer.AddData(this->indices, 6);

}

bool Rectangle::isInside(float x, float y)
{

    //Transform* transform = this->GetParent()->GetComponent<Transform>();
	Transform* objTransform = this->GetGameObject()->GetComponent<Transform>();
	
	std::cout << "Pos rect: " << objTransform->worldPosition.x << ", " << objTransform->worldPosition.y << ", " << objTransform->worldPosition.z<<std::endl;
    float halfLengthX = (xLength * objTransform->worldScale.x) / 2.0f;
    float halfLengthY = (yLength * objTransform->worldScale.y) / 2.0f;


    float relX = x - objTransform->worldPosition.x;
    float relY = y - objTransform->worldPosition.y;


    float angle = glm::radians(objTransform->worldRotation.z);


    float rotatedX = relX * glm::cos(angle) + relY * glm::sin(angle);
    float rotatedY = -relX * glm::sin(angle) + relY * glm::cos(angle);


    if (rotatedX >= -halfLengthX && rotatedX <= halfLengthX &&
        rotatedY >= -halfLengthY && rotatedY <= halfLengthY)
    {
        std::cout << "Inside square." << std::endl;
        return true;
    }
    return false;

}

void Rectangle::SetPositions()
{
	this->positions[0] = -this->xLength / 2.0f;//x
	this->positions[1] = -this->yLength / 2.0f;//y

	this->positions[6] = this->xLength / 2.0f; //x
	this->positions[7] = -this->yLength / 2.0f; //y

	this->positions[12] = this->xLength / 2.0f; //x
	this->positions[13] = this->yLength / 2.0f;//y

	this->positions[18] = -this->xLength / 2.0f; //x
	this->positions[19] = this->yLength / 2.0f; //y
}

void Rectangle::SetIndices()
{
	this->indices[0] = 0;
	this->indices[1] = 1;
	this->indices[2] = 2;
	this->indices[3] = 2;
	this->indices[4] = 3;
	this->indices[5] = 0;
}


size_t Rectangle::GetVertexCount()
{
	return 24; //6 floats per vertex (2 pos, 4 colors) and we have 4 vertices.
}





//CIRCLE BELOW
Circle::Circle()
{

	this->_className = "Circle";

	this->deltaAngle = 10;
	this->color[0] = 0.0f;
	this->color[1] = 0.5f;
	this->color[2] = 0.0f;
	this->color[3] = 1.0f;



	this->radius = 50.0f;

	unsigned int numVertices = this->GetVertexCount(); //+1 is the origin. I will use it in the index buffer.
	unsigned int numIndices = this->GetIndexCount();

	//std::cout << "Num vertices: " << numVertices << ", Num indices: " << numIndices << std::endl;

	this->positions = new float[numVertices];
	this->indices = new unsigned int[numIndices];

	this->SetPositions();
	this->SetIndices();
	this->SetColor();


	this->InitBuffers();

}


void Circle::InitBuffers()
{
	this->vertexBuffer.AddData(this->positions, this->GetVertexCount() * sizeof(float));
	this->layout.Push<float>(2);
	this->layout.Push<float>(4);

	this->vertexArray.AddBuffer(this->vertexBuffer, layout);
	this->indexBuffer.AddData(this->indices, this->GetIndexCount());
}

size_t Circle::GetIndexCount()
{
	return 3 * (360.0f / this->deltaAngle);
}

size_t Circle::GetVertexCount()
{
	return 6 * ((360.0f / this->deltaAngle) + 1); //The reason we say 6 is 2 for x,y and 4 for color.
}

bool Circle::isInside(float x, float y)
{
	//Transform* transform = this->GetParent()->GetComponent<Transform>();
	Transform* objTransform = this->GetGameObject()->GetComponent<Transform>();


	float halfLengthX = (this->radius * objTransform->worldScale.x);
	float halfLengthY = (this->radius * objTransform->worldScale.y);


	float relX = x - objTransform->worldPosition.x;
	float relY = y - objTransform->worldPosition.y;


	float angle = glm::radians(objTransform->worldRotation.z);


	float rotatedX = relX * glm::cos(angle) + relY * glm::sin(angle);
	float rotatedY = -relX * glm::sin(angle) + relY * glm::cos(angle);


	if (rotatedX >= -halfLengthX && rotatedX <= halfLengthX &&
		rotatedY >= -halfLengthY && rotatedY <= halfLengthY)
	{
		std::cout << "Inside circle." << std::endl;
		return true;
	}
	return false;
}

void Circle::SetIndices()
{
	unsigned int counter = 1;
	int numIndices = this->GetIndexCount();
	for (int i = 0; i < numIndices; i += 3)
	{
		this->indices[i] = 0;
		this->indices[i + 1] = counter;
		this->indices[i + 2] = counter + 1;
		counter++;
	}
	this->indices[numIndices - 1] = 1;
}

void Circle::SetPositions()
{
	this->positions[0] = 0.0f;
	this->positions[1] = 0.0f;

	float currentAngle = 0;
	int numVertices = this->GetVertexCount();
	//std::cout << "x: " << this->positions[0] << ", y:" << this->positions[1] << std::endl;
	for (int i = 6; i < numVertices; i += 6)
	{
		float currentAngleInRadians = glm::radians(currentAngle);
		float x = this->radius * glm::cos(currentAngleInRadians);
		float y = this->radius * glm::sin(currentAngleInRadians);
		this->positions[i] = x;
		this->positions[i + 1] = y;


		currentAngle += deltaAngle;

		//std::cout << "x: " << this->positions[i] << ", y:" << this->positions[i + 1] << std::endl;
	}

}

