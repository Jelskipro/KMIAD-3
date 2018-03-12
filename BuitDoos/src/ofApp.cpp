#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetCircleResolution(50);
	font.load("SourceSansPro-Regular.ttf", 25);

	string databasePath = ofToDataPath("lootboxdb.db", true);
	db = new SQLite::Database(databasePath);
	ofSetBackgroundColor(ofColor(19, 19, 19));

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	cam.setVFlip(true);
	cam.begin();
	
	SQLite::Statement query(*db, "SELECT * FROM lootstest WHERE id=?");
	
	int rarity = rarities[chosenRarity];
	
	//ofLog() << "year = " << year << endl;
	
	query.bind(1, rarity);

	while (query.executeStep())
	{
		ofSetColor(ofColor::white);

		//hh_totaal = ofLerp(hh_totaal, query.getColumn("huishoudens_totaal").getInt(), 0.02);
		content = query.getColumn("content").getText();
		
		ofLog() << query.getColumn("id").getInt() << endl;

		font.drawString(content, -25, 0);

		string rarityText;
		rarityText = ofToString(roundf(rarities[chosenRarity]));
		font.drawString(rarityText, -25, 15);


	}
	cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

	chosenRarity = ofMap(x, 0, ofGetWidth(), 0, 3);
}