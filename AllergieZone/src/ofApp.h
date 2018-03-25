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
	void ofApp::mousePressed(int x, int y, int button);


private:
	ofTrueTypeFont font;
	ofTrueTypeFont circleFont;

	ofEasyCam cam;
	ofxPanel gui;

	SQLite::Database* db;
	SQLite::Statement* query;
	SQLite::Statement* queryCompare;

	ofColor tekstZwart = ofColor::fromHex(000000);
	ofColor tekstBlauw = ofColor::fromHex(0x539dba);
	ofColor allergieRood = ofColor::fromHex(0xea3a44);
	ofColor allergieOranje = ofColor::fromHex(0xe8963d);
	ofColor allergieGrijs = ofColor::fromHex(0xb2b2b2);
	ofColor allergieLichtGroen = ofColor::fromHex(0x9bff41);
	ofColor allergieDonkerGroen = ofColor::fromHex(0x73b52d);
	
	ofParameter<float> xPos;
	ofParameter<float> yPos;

	
	int a = 0;
	int b = 0;
	int maxUsers;
	int currentUser;
	int currentUserCompare;
	float zoneKutRadius;
	float zoneCircleRadius = 350;
	bool zoomedIn = false;

	map<string, double> annoyanceByZone;

	string zones[5] = {"kut", "irritant", "neutraal", "prima", "geweldig"};

	vector<textBlock> textBlocks;
	vector<textBlock> textBlocksCompare;
	vector<string> userNames;

	void dataDing(string content, string zone, string category);
	void dataDingCompare(string content, string zone, string category);


};