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

	int chosenRarity = 0;
	int rarities[3] = { 0, 1, 2 };

	string content;

	ofTrueTypeFont font;
	ofEasyCam cam;

	SQLite::Database* db;

};