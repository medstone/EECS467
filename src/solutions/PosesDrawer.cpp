#include "PosesDrawer.h"

using namespace std;

PosesDrawer::PosesDrawer(int argc, char** argv, int widthInPixels = 640, int heightInPixels = 480, int framesPerSecond = 15) :
	VxGtkWindowBase(argc, argv, widthInPixels, heightInPixels, framesPerSecond){
	memcpy(triangleColor, vx_red, sizeof(float)*4);
	memcpy(lineColor, vx_green, sizeof(float)*4);
}

int PosesDrawer::onKeyEvent(vx_layer_t* layer, vx_key_event_t* event){
	cout << event->key_code << endl;
	if(event->key_code == VX_KEY_UP){
		if(memcmp(lineColor, vx_green, sizeof(float)*4) == 0){
			memcpy(lineColor, vx_blue, sizeof(float)*4);
		}
		else if(memcmp(lineColor, vx_red, sizeof(float)*4)){
			memcpy(lineColor, vx_green, sizeof(float)*4);
		}
		else{
			memcpy(lineColor, vx_red, sizeof(float)*4);
		}
	}
	if(event->key_code == VX_KEY_DOWN){
		if(memcmp(lineColor, vx_green, sizeof(float)*4) == 0){
			memcpy(lineColor, vx_red, sizeof(float)*4);
		}
		else if(memcmp(lineColor, vx_red, sizeof(float)*4)){
			memcpy(lineColor, vx_blue, sizeof(float)*4);
		}
		else{
			memcpy(lineColor, vx_green, sizeof(float)*4);
		}
	}
	if(event->key_code == VX_KEY_LEFT){
		if(memcmp(triangleColor, vx_green, sizeof(float)*4) == 0){
			memcpy(triangleColor, vx_red, sizeof(float)*4);
		}
		else if(memcmp(triangleColor, vx_red, sizeof(float)*4)){
			memcpy(triangleColor, vx_blue, sizeof(float)*4);
		}
		else{
			memcpy(triangleColor, vx_green, sizeof(float)*4);
		}
	}
	if(event->key_code == VX_KEY_RIGHT){
		if(memcmp(triangleColor, vx_green, sizeof(float)*4) == 0){
			memcpy(triangleColor, vx_blue, sizeof(float)*4);
		}
		else if(memcmp(triangleColor, vx_red, sizeof(float)*4)){
			memcpy(triangleColor, vx_green, sizeof(float)*4);
		}
		else{
			memcpy(triangleColor, vx_red, sizeof(float)*4);
		}
	}
	return 0;
}

int PosesDrawer::onMouseEvent(vx_layer_t* layer, vx_camera_pos_t* cameraPosition, vx_mouse_event_t* event){
	xPos = event->x;
	yPos = event->y;
	return 0;
}

void PosesDrawer::render(){
	float points[3*triX.size()];
	string mousePos = "X: ";
	mousePos += to_string(xPos);
	mousePos += " Y: ";
	mousePos += to_string(yPos);
	vx_buffer_t* helloBuf = vx_world_get_buffer(world_, "hello");
	vx_buffer_t* triBuf = vx_world_get_buffer(world_, "triangle");
    vx_object_t* posText = vxo_text_create(VXO_TEXT_ANCHOR_BOTTOM_RIGHT, mousePos.c_str());
    vx_buffer_add_back(helloBuf, vxo_chain(vxo_pix_coords(VX_ORIGIN_BOTTOM_RIGHT, posText), posText));
	for(unsigned int i = 0; i < triX.size(); ++i){
		vx_object_t* tri = vxo_triangle(vxo_lines_style(triangleColor,2));
		vx_buffer_add_back(triBuf, vxo_chain(vxo_mat_translate3(triX[i],triY[i],0), vxo_mat_scale2(1, .5), vxo_mat_rotate_z(omega[i]), tri));
		points[(3*i)+0] = triX[i];
		points[(3*i)+1] = triY[i];
		points[(3*i)+2] = 0;
	}
	vx_buffer_add_back(triBuf, vxo_lines(vx_resc_copyf(points, 3*triX.size()), triX.size(), GL_LINE_LOOP, vxo_lines_style(lineColor, 1.0f)));
	vx_buffer_swap(triBuf);
	vx_buffer_swap(helloBuf);
}

void PosesDrawer::getPoints(){
	ifstream pointsFile("../../data/robot_poses.txt");
	float posX, posY, mega;
	while(pointsFile >> posX >> posY >> mega){
		triX.push_back(posX);
		triY.push_back(posY);
		omega.push_back(mega);
	}
}

int main(int argc, char** argv){
	PosesDrawer pose(argc, argv);
	pose.getPoints();
	pose.run();
	return 0;
}
