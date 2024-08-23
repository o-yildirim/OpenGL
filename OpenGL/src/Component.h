#pragma once
class Component 
{
private:
	bool disabled = false;

public:
	virtual ~Component() = default; //Virtual destructor to make Component polymorphic. 
};