#pragma once



struct PhysicComponent
{
public:
	PhysicComponent()
	{
		mIsSphere = false;
	}
	PhysicComponent(const PhysicComponent* second)
	{
		mIsSphere = second->mIsSphere;
	}
	PhysicComponent& PhysicComponent::operator=(const PhysicComponent& other)
	{
		mIsSphere = other.mIsSphere;
	}
	bool mIsSphere;

};

