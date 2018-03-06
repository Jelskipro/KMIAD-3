#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "SQLiteCpp.h"



class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void mouseMoved(int x, int y);


private:
	int currentYear = 0;

	int years[9] = { 1995, 2000, 2005, 2010, 2012, 2013, 2014, 2015, 2016 };

	float currentPopulation_NL;
	float hh_totaal;
	float hh_single;
	float hh_multiple;
	float hh_multiple_nokids;
	float hh_multiple_kids;
	float hh_multiple_notmarried;
	float hh_multiple_married;
	float hh_multiple_singleparent;
	float hh_multiple_other;

	float mapHeightMin;

	ofTrueTypeFont font;
	ofTrueTypeFont amountFont;

	ofEasyCam cam;

	ofRectangle rectTotaal;
	ofRectangle rectSingle;
	ofRectangle rectMultiple;
	ofRectangle rectMultipleNoKids;
	ofRectangle rectMultipleKids;
	ofRectangle rectMultipleNotMarried;
	ofRectangle rectMultipleMarried;
	ofRectangle rectMultipleSingleParent;
	ofRectangle rectMultipleOther;


	SQLite::Database* db;

	ofxPanel gui;
	ofParameter<float> BarWidth;
	ofParameter<float> mapHeightMax;
	ofParameter<float> barY;

};