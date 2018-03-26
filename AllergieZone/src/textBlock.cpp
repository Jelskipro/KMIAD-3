#include "textBlock.h"

textBlock::textBlock() {
}

void textBlock::setup(string textContent, string textZone, string textCategory) {
	
	text = textContent;
	zone = textZone;
	category = textCategory;

	//Kijk in welke zone deze tekstblock moet komen en zet de waarde.
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

	itemFont.load("Futura PT Book.ttf", 25);
	
	//Zorg ervoor dat hij binnen de circle wordt getekend
	float distance = ofRandom(innerCircleRadius, cricleRadius);
	float angle = ofRandom(0, 3.1415 * 2);
	ofVec2f dir(cos(angle), sin(angle));

	//Je uiteindelijke positie
	 pos = dir * distance;
}


void textBlock::update() {
	
}

void textBlock::draw() {
	
	ofNoFill();
	ofSetLineWidth(5);
	//Teken de circkel die ervoor zit en geef hem een ofset mee
	ofCircle(pos.x - 30, pos.y - 10, 0, 15);

	itemFont.drawString(text, pos.x, pos.y);
	itemFont.setLineHeight(25);
}