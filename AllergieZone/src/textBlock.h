#pragma once

#include "ofMain.h"

class textBlock {

public:

	textBlock();

	void setup(string textContent, string textZone, string textCategory);

	void update();

	void draw();
	
	string text;
	string zone;
	string category;
	
	float cricleRadius;
	float innerCircleRadius;

	ofTrueTypeFont itemFont;
	ofVec2f pos;
private:

};