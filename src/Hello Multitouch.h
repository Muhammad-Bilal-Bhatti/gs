////////////////////////////////////////////////////////////////////////////////
//
//  IDEUM
//  Copyright 2011-2013 Ideum
//  All Rights Reserved.
//
//  GestureWorks
//
//  File:    Hello Multitouch.h
//  Authors:  Ideum
//             
//  NOTICE: Ideum permits you to use, modify, and distribute this file only
//  in accordance with the terms of the license agreement accompanying it.
//
////////////////////////////////////////////////////////////////////////////////

#include "ofMain.h"
#include "GestureWorksCore.h"
#include <math.h>

class MovableObject{
public:
	float x;
	float y;
	float height;
	float width;
	float rotation;
	float scale;
	ofImage img;
	MovableObject();
	MovableObject(float _x, float _y, float _w, float _h, float _r, float _s, string _path);
	void draw();
};

class helloMultitouch : public ofBaseApp{

	public:

		DWORD last_tick_count;

		void setup();
		void update();
		void draw();	

		void keyPressed(int key);

		ofImage theImg;
		vector<MovableObject*> mov;
};

