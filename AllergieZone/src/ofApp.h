#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "SQLiteCpp.h"
#include "textBlock.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void mouseMoved(int x, int y);


private:
	ofTrueTypeFont font;
	ofTrueTypeFont circleFont;

	ofEasyCam cam;
	ofxPanel gui;

	SQLite::Database* db;

	ofColor allergieRood = ofColor::fromHex(0xea3a44);
	ofColor allergieOranje = ofColor::fromHex(0xe8963d);
	ofColor allergieGrijs = ofColor::fromHex(0xb2b2b2);
	ofColor allergieLichtGroen = ofColor::fromHex(0x9bff41);
	ofColor allergieDonkerGroen = ofColor::fromHex(0x73b52d);

	ofParameter<float> zoneCircleRadius;

	float zoneKutRadius;

	map<string, double> annoyanceByZone;

	string zones[5] = {"kut", "irritant", "neutraal", "prima", "geweldig"};

	vector<textBlock> textBlocks;

	void dataDing(string content, string zone, string category);

	int a = 0;


};