#include "includes/mouse.hpp"

#include "includes/headers.hpp"
#include "includes/object.hpp"

void MouseHandler::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	MouseHandler* handler = static_cast<MouseHandler*>(glfwGetWindowUserPointer(window));
	_xpos = xpos, _ypos = ypos;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		updatePosition(handler);
		calculateRotationSpeed(handler);
		preventFlip(handler);
		updateHandler(handler);
	} else
		stopRotation(handler);
	xpos = _xpos, ypos = _ypos;
}

void MouseHandler::updatePosition(MouseHandler* handler) {
	sensitivity = 0.005f;
	if (handler->lastXPos != 0.0 && handler->lastYPos != 0.0 &&
		(handler->lastXPos != _xpos || handler->lastYPos != _ypos)) {
		handler->mouseMoved = true;
	} else {
		handler->mouseMoved = false;
		sensitivity = 0.0f;
	}
	deltaX = _xpos - handler->lastXPos;
	deltaY = _ypos - handler->lastYPos;
}

void MouseHandler::preventFlip(MouseHandler* handler) {
	if (handler->rotationAngleX > 360.0f)
		handler->rotationAngleX -= 360.0f;
	else if (handler->rotationAngleX < -360.0f)
		handler->rotationAngleX += 360.0f;

	if (handler->rotationAngleY > 360.0f)
		handler->rotationAngleY -= 360.0f;
	else if (handler->rotationAngleY < -360.0f)
		handler->rotationAngleY += 360.0f;
}

void MouseHandler::calculateRotationSpeed(MouseHandler* handler) {
	handler->rotationAngleX += deltaX * sensitivity;
	handler->rotationAngleY += deltaY * sensitivity;
}

void MouseHandler::updateHandler(MouseHandler* handler) {
	handler->lastXPos = _xpos;
	handler->lastYPos = _ypos;
}

void MouseHandler::stopRotation(MouseHandler* handler) {
	handler->rotationAngleX = 0.0f;
	handler->rotationAngleY = 0.0f;
	handler->mouseMoved = false;
}
