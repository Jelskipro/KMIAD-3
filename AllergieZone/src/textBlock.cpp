#include "textBlock.h"

textBlock::textBlock() {
}

void textBlock::setup(string textContent, string textZone, string textCategory) {
	
	text = textContent;
	zone = textZone;
	category = textCategory;

	if (zone == "Kut")
	{
		cricleRadius = 350;
		innerCircleRadius = 0;
	}
	else if (zone == "Irritant")
	{
		cricleRadius = 700;
		innerCircleRadius = 350;
	}
	else if (zone == "Neutraal")
	{
		cricleRadius = 1050;
		innerCircleRadius = 700;
	}
	else if (zone == "Prima")
	{
		cricleRadius = 1400;
		innerCircleRadius = 1050;
	}
	else if (zone == "Geweldig")
	{
		cricleRadius = 1750;
		innerCircleRadius = 1400;
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
	
	//string testText = "Lorem ipsum \n dolor sit amet.";
	ofNoFill();
	ofSetLineWidth(5);
	ofCircle(pos.x - 30, pos.y - 10, 0, 15);

	itemFont.drawString(text, pos.x, pos.y);
	itemFont.setLineHeight(25);
}