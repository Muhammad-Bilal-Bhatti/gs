////////////////////////////////////////////////////////////////////////////////
//
//  IDEUM
//  Copyright 2011-2013 Ideum
//  All Rights Reserved.
//
//  GestureWorks
//
//  File:    Hello Multitouch.cpp
//  Authors:  Ideum
//             
//  NOTICE: Ideum permits you to use, modify, and distribute this file only
//  in accordance with the terms of the license agreement accompanying it.
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ofMain.h"
#include "Hello Multitouch.h"

//This vector keeps track of the points to be displayed on screen
std::map<int,gwc::Point> active_points;

//--------------------------------------------------------------
void helloMultitouch::setup(){

	ofSetFullscreen(true);

	last_tick_count = GetTickCount();

	active_points = std::map<int,gwc::Point>();

	if(loadGestureWorks("GestureworksCore32.dll")) { 
		std::cout << "Error loading gestureworks dll" << std::endl; 
		exit(); 
	}
	if(!loadGML("basic_manipulation.gml")) { 
		std::cout << "Could not find gml file" << std::endl; 
		exit(); 
	}

	initializeGestureWorks(1920,1080);

	if( !registerWindowForTouchByName("Hello Multitouch!") ) { 
		std::cout << "Could not register target window for touch." << std::endl; 
		exit(); 
	}

	mov.push_back(new MovableObject(0.0,0.0,0.0,0.0,0.0,1.0,"square-512.png"));
	mov.push_back(new MovableObject(0.0,512.0,0.0,0.0,0.0,1.0,"triangle-512.png"));
	mov.push_back(new MovableObject(0.0,1024.0,0.0,0.0,0.0,1.0,"circle-512.png"));

	theImg.loadImage("triangle-512.png");
}

//This function is the last to get called every cycle, and is responsible
//for generating all screen artifacts
void helloMultitouch::draw(){

	ofBackground(ofColor(169,169,169));
	ofSetColor(238, 57, 135, 100);
	//For each active point
	for(std::map<int,gwc::Point>::iterator points_it = active_points.begin(); points_it != active_points.end(); points_it++){
		float x = points_it->second.getX();
		float y = points_it->second.getY();

		//Generate a circle with a 50-pixel radius at this point's location
		ofFill();
		ofCircle(ofPoint(x, y, 0), 20);
		ofNoFill();
		ofSetLineWidth(2);
		ofCircle(ofPoint(x, y, 0), 30);


		//Generate a stringstream for each value with which we're concerned
		std::stringstream xvals; xvals << (int)x;
		std::stringstream yvals; yvals << (int)y;
		std::stringstream ids; ids << points_it->first;

		//Annotate the circle we just drew with the id, x and y values for the corresponding point
		ofDrawBitmapString("ID: " + ids.str() + "\nX: " + xvals.str() + " Y: " + yvals.str(), x + 40, y - 40, 0);
	}

	//draw the images.
	vector<MovableObject*>::iterator mIter;
	for(mIter = mov.begin(); mIter != mov.end(); ++mIter){
		(*mIter)->draw();
	}
	//theImg.draw(0.0,0.0);
}

//The update function gets called once per cycle prior to the draw function
void helloMultitouch::update(){

	//Updating once every 16 milliseconds corresponds to a rate of approximately 62.5 frames per second
	if(GetTickCount() - last_tick_count < 16) {
		return;
	} else { last_tick_count = GetTickCount(); }
  
	processFrame();

	std::vector<gwc::PointEvent> point_events = consumePointEvents();

	for(std::vector<gwc::PointEvent>::iterator event_it = point_events.begin(); event_it != point_events.end(); event_it++) {
		switch(event_it->status) {
			case gwc::TOUCHADDED:
			case gwc::TOUCHUPDATE:
				//If the point is being added, this will place it in our point map; the same line of code will update the point's
				//position if it's already present, so we can use this command to handle new points as well as point updates
				active_points[event_it->point_id] = gwc::Point(event_it->position.getX(),event_it->position.getY());
				break;
			case gwc::TOUCHREMOVED:
				//Remove the point from the map
				active_points.erase(event_it->point_id);
				break;
		}
	}
}

void helloMultitouch::keyPressed(int key){
	if(key == 'f'){
		ofToggleFullscreen();
	}
}

MovableObject::MovableObject(){
}

MovableObject::MovableObject(float _x, float _y, float _w, float _h, float _r, float _s, string _path){
	x = _x;
	y = _y;
	width = _w;
	height = _h;
	rotation = _r;
	scale = _s;
	img.loadImage(_path);
}

void MovableObject::draw(){
	img.draw(x, y, width, height);
}