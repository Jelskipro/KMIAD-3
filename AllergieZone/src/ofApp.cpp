#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	gui.setup("Instellingen", "settings.xml");
	gui.add(zoneCircleRadius.set("zoneCircleRadius", 180, 0, 1000));

	ofSetCircleResolution(60);

	font.load("Futura PT Book.ttf", 25);
	circleFont.load("Futura PT Heavy.ttf", 25);

	string databasePath = ofToDataPath("allergiezonedb.db", true);
	db = new SQLite::Database(databasePath);
	
	ofSetBackgroundColor(ofColor(249, 249, 225));
	cam.setDistance(1500);
	
}

//--------------------------------------------------------------
void ofApp::update() {
	for (unsigned int i = 0; i < textBlocks.size(); i++) {
		textBlocks[i].update();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	gui.draw();

	cam.setVFlip(true);
	cam.begin();
	
	SQLite::Statement query(*db, "SELECT * FROM test WHERE");

	//query.bind(1, zones[2]);
	while (query.executeStep())
	{
		//Teken de 1e circle
		ofSetColor(allergieRood);
		ofNoFill();
		ofSetLineWidth(3);
		ofCircle(0, 0, 0, zoneCircleRadius);

		//Teken de 2e circle
		ofSetColor(allergieOranje);
		ofCircle(0, 0, zoneCircleRadius * 2);

		//Teken de 3e circle
		ofSetColor(allergieGrijs);
		ofCircle(0, 0, zoneCircleRadius * 3);
		
		//Teken de 4e circle
		ofSetColor(allergieLichtGroen);
		ofCircle(0, 0, zoneCircleRadius * 4);

		//Teken de 5e circle
		ofSetColor(allergieDonkerGroen);
		ofCircle(0, 0, zoneCircleRadius * 5);

		//ofLog() << query.getColumn("zone") << endl;

		for (unsigned int i = 0; i < textBlocks.size(); i++) {
			textBlocks[i].draw();
		}
		if (a < 13) {
			dataDing(query.getColumn("inhoud"), query.getColumn("zone"), query.getColumn("categorie"));
		}
		circleFont.drawString("Kut", zoneCircleRadius + 10, 0);
		circleFont.drawString("Irritant", zoneCircleRadius * 2 + 10, 0);
		circleFont.drawString("Neutraal", zoneCircleRadius * 3 + 10, 0);
		circleFont.drawString("Prima", zoneCircleRadius * 4 + 10, 0);
		circleFont.drawString("Geweldig", zoneCircleRadius * 5 + 10, 0);

	}
	//cout << textBlocks.size() << endl;
	cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'e') {
		cam.setPosition(100, 100, 300);
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

void ofApp::dataDing(string content, string zone, string category) {
	textBlock newTextBlock;
	newTextBlock.setup(content, zone, category);
	textBlocks.push_back(newTextBlock);
	a++;
	
}