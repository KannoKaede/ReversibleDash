//#include "3dSetting.h"
//
//Camera::Camera(VECTOR pos, VECTOR look) {
//	cameraPos = pos;
//	lookPos = look;
//}
//
//void Camera::StartUp() {
//	SetCameraNearFar(0, 100);
//}
//
//void Camera::Move(float moveAmount) {
//	cameraPos.x += moveAmount;
//	lookPos.x += moveAmount;
//	SetCameraPositionAndTarget_UpVecY(cameraPos, lookPos);
//}
//void Camera::Initialization() {
//	cameraPos = START_CAMERA_POS;
//	lookPos.x = START_CAMERA_POS.x;
//}
//
//Light::Light(VECTOR pos) {
//	lightPos = pos;
//}
//
//void Light::StartUp() {
//	SetUseLighting(TRUE);
//	SetLightDirection(VGet(0.0f, 0.0f, 1.0f));
//}
//
//void Light::Move(float moveAmount) {
//	lightPos.x += moveAmount;
//	SetLightPosition(lightPos);
//}
//
//void Light::Initialization() {
//	lightPos = START_LIGHT_POS;
//}