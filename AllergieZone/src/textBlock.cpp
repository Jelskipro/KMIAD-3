#include "textBlock.h"

textBlock::textBlock() {
}

void textBlock::setup(string textContent, string textZone, string textCategory) {
	
	text = textContent;
	zone = textZone;
	category = textCategory;
	

	if (zone == "kut")
	{
		cricleRadius = 180;
		innerCircleRadius = 0;
	}
	else if (zone == "irritant")
	{
		cricleRadius = 360;
		innerCircleRadius = 180;
	}
	else if (zone == "neutraal")
	{
		cricleRadius = 540;
		innerCircleRadius = 360;
	}
	else if (zone == "prima")
	{
		cricleRadius = 720;
		innerCircleRadius = 540;
	}
	else if (zone == "geweldig")
	{
		cricleRadius = 900;
		innerCircleRadius = 720;
	}

	ofLog() << zone << endl;
	itemFont.load("Futura PT Book.ttf", 25);
	
	//Zorg ervoor dat hij binnen de circle wordt getekend
	float distance = ofRandom(innerCircleRadius, cricleRadius);
	float angle = ofRandom(0, 3.1415 * 2);
	ofVec2f dir(cos(angle), sin(angle));


	 pos = dir * distance;
}


void textBlock::update() {
	
}

void textBlock::draw() {
	
	ofFill();
	ofSetLineWidth(0);

	ofSetColor(ofColor::black);

	//string testText = "Lorem ipsum \n dolor sit amet.";
	itemFont.drawString(text, pos.x, pos.y);
	itemFont.setLineHeight(25);
}