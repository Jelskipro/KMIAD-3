#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	gui.setup("Instellingen", "settings.xml");
	gui.add(zoneCircleRadius.set("zoneCircleRadius", 100, 0, 1000));


	ofSetCircleResolution(60);

	font.load("Futura PT Book.ttf", 25);
	itemFont.load("Futura PT Book.ttf", 25);
	circleFont.load("Futura PT Heavy.ttf", 25);

	string databasePath = ofToDataPath("allergiezonedb.db", true);
	db = new SQLite::Database(databasePath);
	
	ofSetBackgroundColor(ofColor(249, 249, 225));

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	gui.draw();

	cam.setVFlip(true);
	cam.begin();
	
	SQLite::Statement query(*db, "SELECT * FROM test WHERE zone='kut'");

	//query.bind(1, zones[2]);
	while (query.executeStep())
	{
		ofLog() << query.getColumn("zone") << endl;
		//Teken de 1e circle
		ofSetColor(allergieRood);
		ofNoFill();
		ofSetLineWidth(3);
		ofCircle(0, 0, zoneCircleRadius);

		//Teken de 2e circle
		ofSetColor(allergieOranje);
		ofCircle(0, 0, zoneCircleRadius * 2);

		//Zorg ervoor dat hij binnen de circle wordt getekend
		float distance = ofRandom(zoneCircleRadius, zoneCircleRadius * 2);
		float angle = ofRandom(0, 3.1415 * 2);
		ofVec2f dir(cos(angle), sin(angle));


		ofVec2f pos = dir * distance;
		ofFill();
		ofSetLineWidth(0);
		
		ofSetColor(ofColor::black);

		string testText = "Lorem ipsum \n dolor sit amet.";
		itemFont.drawString(testText, pos.x, pos.y);
		itemFont.setLineHeight(25);
		
		circleFont.drawString("Kut", zoneCircleRadius + 10, 0);
		circleFont.drawString("Irritant", zoneCircleRadius * 2 + 10, 0);

	}
	cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}