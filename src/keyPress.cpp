#include "includes/keyPress.hpp"

#include <string>

void keyPressHandler_Camera_wasdSpaceX(GLFWwindow *window, Camera &camera) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, camera.deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, camera.deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, camera.deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, camera.deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, camera.deltaTime);
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, camera.deltaTime);
}

void keyPressHandler_Camera_Speed(GLFWwindow *window, Camera &camera, Object &object) {
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {
		camera.MovementSpeed -= camera.changeSpeed;
		if (camera.MovementSpeed < 1.0f) camera.MovementSpeed = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) camera.MovementSpeed += camera.changeSpeed;
	object.text.cameraSpeed = std::to_string(camera.MovementSpeed);
}

void keyPressHandler_PolygonModes(GLFWwindow *window, Object &object) {
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		object.renderMode = WIREFRAME;
		object.text.mode = "wireframe";
	} else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		object.renderMode = POINTS;
		object.text.mode = "points";
	} else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		object.renderMode = FILLED;
		object.text.mode = "filled";
	}
}

void keyPressHandler_Color_OR_Texture(GLFWwindow *window, int &version, Object &object) {
	static bool tKeyPressed = false;
	static bool yKeyPressed = false;

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) version = 3;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) version = 2;
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) version = 1;
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && !tKeyPressed) {
		if (object.textures.size() == static_cast<size_t>(object.textureType + 1) && !tKeyPressed)
			object.textureType = 0;
		else if (!tKeyPressed)
			object.textureType += 1;
		tKeyPressed = true;
	} else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE)
		tKeyPressed = false;
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS && !yKeyPressed) {
		if (object.textureType == 0 && !yKeyPressed)
			object.textureType = object.textures.size() - 1;
		else if (!yKeyPressed)
			object.textureType -= 1;
		yKeyPressed = true;
	} else if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_RELEASE)
		yKeyPressed = false;
}

float colorChange = 0.05f;

void keyPressHandler_SetColor(GLFWwindow *window, glm::vec3 &color) {
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		color.r += colorChange;
		if (color.r > 1.0f) color.r = 0.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
		color.g += colorChange;
		if (color.g > 1.0f) color.g = 0.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
		color.b += colorChange;
		if (color.b > 1.0f) color.b = 0.0f;
	}
}

void keyPressHandler_SetColorVersion(GLFWwindow *window, int &version, Object &object) {
	static bool bKeyPressed = false;
	(void)object;

	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && !bKeyPressed) {
		version++;
		if (version > 4) version = 1;
		bKeyPressed = true;
	} else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE)
		bKeyPressed = false;
}

float rotationX = 0.0f;
float rotationY = 0.0f;
float rotationZ = 0.0f;
float rotateSpeed = 1.0f;

void keyPressHandler_ObjectCenterRotation(GLFWwindow *window, Object &object) {
	object.model = glm::mat4(1.0f);
	std::vector<float> allTriangles;
	allTriangles.insert(allTriangles.end(), object.Triangles.begin(), object.Triangles.end());

	glm::vec3 objectCenter = calculateCenter(allTriangles);

	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) rotationX += rotateSpeed;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) rotationX -= rotateSpeed;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) rotationY += rotateSpeed;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) rotationY -= rotateSpeed;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) rotationZ += rotateSpeed;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) rotationZ -= rotateSpeed;
	if (rotateSpeed > 1.0f)
		if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) rotateSpeed -= 0.5f;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) rotateSpeed += 0.5f;

	object.model = glm::translate(object.model, objectCenter);
	object.model = glm::rotate(object.model, glm::radians(rotationX), glm::vec3(1.0f, 0.0f, 0.0f));
	object.model = glm::rotate(object.model, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
	object.model = glm::rotate(object.model, glm::radians(rotationZ), glm::vec3(0.0f, 0.0f, 1.0f));
	object.model = glm::translate(object.model, -objectCenter);
}

glm::vec3 calculateCenter(const std::vector<float> &triangles) {
	glm::vec3 sum(0.0f);
	size_t totalVertices = triangles.size() / 5;

	for (size_t i = 0; i < triangles.size(); i += 5) {
		sum.x += triangles[i];
		sum.y += triangles[i + 1];
		sum.z += triangles[i + 2];
	}
	return sum / static_cast<float>(totalVertices);
}

bool autoRotate = false;

void keyPressHandler_AutoRotate(GLFWwindow *window, Object &object) {
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		autoRotate = true;
	}
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
		autoRotate = false;
	}

	if (autoRotate) {
		rotationY += rotateSpeed;
	}

	object.model = glm::mat4(1.0f);
	std::vector<float> allTriangles;
	allTriangles.insert(allTriangles.end(), object.Triangles.begin(), object.Triangles.end());

	glm::vec3 objectCenter = calculateCenter(allTriangles);

	object.model = glm::translate(object.model, objectCenter);
	object.model = glm::rotate(object.model, glm::radians(rotationX), glm::vec3(1.0f, 0.0f, 0.0f));
	object.model = glm::rotate(object.model, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
	object.model = glm::rotate(object.model, glm::radians(rotationZ), glm::vec3(0.0f, 0.0f, 1.0f));
	object.model = glm::translate(object.model, -objectCenter);
}

void keyPressHandler_SetLight(GLFWwindow *window, Shader &shader, Object &object) {
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		object.lightSourcePos.x -= 0.15;
		object.text.lightX = std::to_string(object.lightSourcePos.x);
		shader.setVec3("LightPos", object.lightSourcePos);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		object.lightSourcePos.x += 0.15;
		object.text.lightX = std::to_string(object.lightSourcePos.x);
		shader.setVec3("LightPos", object.lightSourcePos);
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		object.lightSourcePos.y -= 0.15;
		object.text.lightY = std::to_string(object.lightSourcePos.y);
		shader.setVec3("LightPos", object.lightSourcePos);
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		object.lightSourcePos.y += 0.15;
		object.text.lightY = std::to_string(object.lightSourcePos.y);
		shader.setVec3("LightPos", object.lightSourcePos);
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		object.lightSourcePos.z -= 0.15;
		object.text.lightZ = std::to_string(object.lightSourcePos.z);
		shader.setVec3("LightPos", object.lightSourcePos);
	}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
		object.lightSourcePos.z += 0.15;
		object.text.lightZ = std::to_string(object.lightSourcePos.z);
		shader.setVec3("LightPos", object.lightSourcePos);
	}
}

void keyPressHandler(GLFWwindow *window, int &version, Camera &camera, Object &object, Shader &shader, glm::vec3 &color) {
	keyPressHandler_Color_OR_Texture(window, version, object);
	keyPressHandler_SetColorVersion(window, version, object);
	keyPressHandler_Camera_Speed(window, camera, object);
	keyPressHandler_ObjectCenterRotation(window, object);
	keyPressHandler_SetLight(window, shader, object);
	keyPressHandler_Camera_wasdSpaceX(window, camera);
	keyPressHandler_PolygonModes(window, object);
	keyPressHandler_AutoRotate(window, object);
	keyPressHandler_SetColor(window, color);
}