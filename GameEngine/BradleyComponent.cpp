#include "BradleyComponent.h"

BradleyComponent::BradleyComponent() :Component(500) {

}
void BradleyComponent::initialize() {
	cout << "initialize method called" << endl;
}
void BradleyComponent::update(const float& deltaTime) {
	//cout << "update method called, dt:"<< deltaTime << endl;
}
void BradleyComponent::processInput() {
	//cout << "Process input method called bradley" << endl;
}
