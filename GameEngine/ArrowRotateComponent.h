#pragma once
#include "Component.h"
class ArrowRotateComponent : public Component
{
	public:
		ArrowRotateComponent(float rotRateDegreesPerSec = 30.0f, int updateOrder = 150);
		virtual void update(const float& deltaTime) override;

	protected:
		/** @brief	The rotation rate in radians per second */
		float radianRotRate;
};

