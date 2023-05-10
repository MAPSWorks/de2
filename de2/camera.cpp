#include "pch.h"
#include "camera.h"
#include <algorithm>


float map_range(float s, float a1, float a2, float b1, float b2) {
	return b1 + ((s-a1)*(b2-b1))/(a2-a1);
}

euler_orbit::euler_orbit() {
	distance_ = 5;
}
glm::mat4 euler_orbit::getview(){

	return glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -distance_))
		* glm::eulerAngleXY((float)pitch , (float)yaw );
}
glm::vec3 euler_orbit::getpos(){
	return inverse(getview())[3];
}
void euler_orbit::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		ldown = true;
		glfwGetCursorPos(window, &lastx, &lasty);
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		ldown = false;
	}
}
void euler_orbit::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos){
	if (ldown)
	{
		double sensivity = (0.002 * distance_);

		pitch -= ( lasty - ypos ) * sensivity;
		yaw -= (lastx - xpos) * sensivity;

		lastx = xpos;
		lasty = ypos;
	}
}
void euler_orbit::mouse_wheel_callback(GLFWwindow* window, double xoffset, double yoffset){
	distance_ = std::clamp(distance_ - yoffset, 1.0, std::numeric_limits<double>::max());
}

//euler_angle_orbit
euler_angle_orbit::euler_angle_orbit() {
	zoom_ = 14;
}
glm::mat4 euler_angle_orbit::getview() {
	return glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -get_altitude(zoom_)))
		* glm::eulerAngleXY((float)std::clamp(pitch, -glm::pi<double>()/2*0.85, glm::pi<double>() / 2 * 0.85), (float)yaw);
}

glm::vec3 euler_angle_orbit::getpos() {
	return inverse(getview())[3];
}

void euler_angle_orbit::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		ldown = true;
		glfwGetCursorPos(window, &lastx, &lasty);		
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		ldown = false;
	}
}
void euler_angle_orbit::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	if (ldown)
	{
		double sensivity = (0.00099 * get_altitude(zoom_));
		yaw -= (lastx - xpos) * sensivity;
		pitch -= (lasty - ypos) * sensivity;

		lastx = xpos;
		lasty = ypos;
	}
}
void euler_angle_orbit::mouse_wheel_callback(GLFWwindow* window, double xoffset, double yoffset) {
	zoom_ = std::clamp(zoom_ + yoffset, 1.0, std::numeric_limits<double>::max());
}

//glm::vec3 euler_angle_orbit::get_arcball_vector(int x, int y) {
//	//map -1 to 1
//	double ax = 1.0 * x / 800 * 2 - 1.0;
//	double bx = 1.0 * y / 800 * 2 - 1.0;
//
//	glm::vec3 P = glm::vec3(1.0 * x / 800 * 2 - 1.0, 1.0 * y / 800 * 2 - 1.0,
//		0);
//	P.y = -P.y;
//	float OP_squared = P.x * P.x + P.y * P.y;
//
//	if (OP_squared <= 1 * 1)
//		P.z = sqrt(1 * 1 - OP_squared);  // Pythagoras
//	else
//		P = glm::normalize(P);  // nearest point
//	return P;
//}

double euler_angle_orbit::get_altitude(int map_zoom) {
	return 20000000 / std::pow(2, map_zoom - 1);
}