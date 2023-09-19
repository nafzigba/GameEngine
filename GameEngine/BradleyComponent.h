#pragma once
#include "Component.h"
class BradleyComponent : public Component {
public:
	BradleyComponent();
private:
	virtual void initialize() override;
	virtual void update(const float& deltaTime) override;
	virtual void processInput() override;
};

