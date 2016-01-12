#ifndef POSESDRAWER_H
#define POSESDRAWER_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>

//base class
#include <eecs467/vx_gtk_window_base.hpp>

// core api
#include <vx/vx.h>
#include "vx/vx_util.h"
#include "vx/vx_remote_display_source.h"
#include "vx/gtk/vx_gtk_display_source.h"

// drawables
#include "vx/vxo_drawables.h"

// common
#include "common/getopt.h"
#include "common/pg.h"
#include "common/zarray.h"
 
class PosesDrawer : public eecs467::VxGtkWindowBase {
public: 
	
	PosesDrawer(int argc, char** argv, int widthInPixels, int heightInPixels, int framesPerSecond);

	virtual int onKeyEvent(vx_layer_t* layer, vx_key_event_t* event);

	virtual int onMouseEvent(vx_layer_t* layer, vx_camera_pos_t* cameraPosition, vx_mouse_event_t* event);

	void getPoints();

private:
	
	virtual void render();

	int xPos, yPos;

	float lineColor[4];
	float triangleColor[4];
	
	std::vector<float> triX;
	std::vector<float> triY;
	std::vector<float> omega;
};
#endif
