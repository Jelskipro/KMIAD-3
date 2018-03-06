#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	gui.setup("Instellingen", "settings.xml");
	gui.add(BarWidth.set("BarWidth", 25, 0, 100));
	gui.add(mapHeightMax.set("mapHeightMax", 300, 0, 20000));
	gui.add(barY.set("barY", 55, 0, 100));

	ofSetCircleResolution(50);
	font.load("SourceSansPro-Regular.ttf", 25);
	amountFont.load("SourceSansPro-Regular.ttf", 25);

	string databasePath = ofToDataPath("roslingdb.db", true);
	db = new SQLite::Database(databasePath);
	ofSetBackgroundColor(ofColor(19, 19, 19));
	
}

//--------------------------------------------------------------
void ofApp::update() {
	
}

//--------------------------------------------------------------
void ofApp::draw() {
	gui.draw();

	cam.setVFlip(true);
	cam.begin();
    SQLite::Statement query(*db, "SELECT * FROM huishoudens WHERE year=?");
	int year = years[currentYear];
	//ofLog() << "year = " << year << endl;
	query.bind(1, year);
	while (query.executeStep())
	{
	
		hh_totaal = ofLerp(hh_totaal, query.getColumn("huishoudens_totaal").getInt(), 0.02);
		hh_single = ofLerp(hh_single, query.getColumn("hh_single").getInt(), 0.02);
		hh_multiple = ofLerp(hh_multiple, query.getColumn("hh_multiple").getInt(), 0.02);
		hh_multiple_nokids = ofLerp(hh_multiple_nokids, query.getColumn("hh_multiple_nokids").getInt(), 0.02);
		hh_multiple_kids = ofLerp(hh_multiple_kids, query.getColumn("hh_multiple_kids").getInt(), 0.02);
		hh_multiple_notmarried = ofLerp(hh_multiple_notmarried, query.getColumn("hh_multiple_notmarried").getInt(), 0.02);
		hh_multiple_married = ofLerp(hh_multiple_married, query.getColumn("hh_multiple_married").getInt(), 0.02);
		hh_multiple_singleparent = ofLerp(hh_multiple_singleparent, query.getColumn("hh_multiple_singleparent").getInt(), 0.02);
		hh_multiple_other = ofLerp(hh_multiple_other, query.getColumn("hh_multiple_other").getInt(), 0.02);
		
		string totalText = "Totaal";
		string singleText = "single";
		string multipleText = "multiple";
		string multipleNoKidsText = "multiple no kids";
		string multiplKidsText = "multiple kids";
		string multipleNotMarriedText = "multiple not married";
		string multipleMarriedText = "multiple married";
		string multipleSingleParentText = "multiple single parent";
		string multipleOtherText = "multiple other";

		ofSetColor(255);
		ofNoFill();
		ofSetLineWidth(5);
		ofSetCircleResolution(60);
		ofCircle(0, 0, ofMap(hh_totaal, 0, 7720787, 0, mapHeightMax));
		ofCircle(0, 0, 0.5 * ofMap(hh_totaal, 0, 7720787, 0, mapHeightMax));
		ofFill();
		ofSetLineWidth(0);
		ofSetCircleResolution(50);

		//Total Bar
		ofSetColor(ofColor::white);
		rectTotaal.x = -12.5;
		rectTotaal.y = -50;
		rectTotaal.width = BarWidth;

		rectTotaal.height = ofMap(hh_totaal, 0, 7720787, 0, mapHeightMax);

		//ofDrawRectangle(rectTotaal);

		//Single Bar
		ofSetColor(ofColor::blue);
		rectSingle.x = -12.5;
		rectSingle.y = barY;
		rectSingle.width = BarWidth;
		rectSingle.height = ofMap(hh_single, 0, 7720787, 0, mapHeightMax);
		ofRotateZ(0);
		amountFont.drawString(singleText, -2.7 * ofMap(hh_single, 0, 7720787, 0, mapHeightMax), 12.5);
		ofRotateZ(90);

		ofDrawRectangle(rectSingle);
		

		//Multiple Bar
		ofSetColor(ofColor::red);
		rectMultiple.x = -12.5;
		rectMultiple.y = barY;
		rectMultiple.width = BarWidth;
		rectMultiple.height = ofMap(hh_multiple, 0, 7720787, 0, mapHeightMax);
		ofRotateZ(45);
		
		ofDrawRectangle(rectMultiple);

		//Multiple No Kids Bar
		ofSetColor(ofColor::green);
		rectMultipleNoKids.x = -12.5;
		rectMultipleNoKids.y = barY;
		rectMultipleNoKids.width = BarWidth;
		rectMultipleNoKids.height = ofMap(hh_multiple, 0, 7720787, 0, mapHeightMax);
		ofRotateZ(45);
		ofDrawRectangle(rectMultipleNoKids);
		
		//Multiple Kids Bar
		ofSetColor(ofColor::pink);
		rectMultipleKids.x = -12.5;
		rectMultipleKids.y = barY;
		rectMultipleKids.width = BarWidth;
		rectMultipleKids.height = ofMap(hh_multiple_kids, 0, 7720787, 0, mapHeightMax);
		ofRotateZ(45);
		ofDrawRectangle(rectMultipleKids);
		
		//Multiple Married Bar
		ofSetColor(ofColor::purple);
		rectMultipleMarried.x = -12.5;
		rectMultipleMarried.y = barY;
		rectMultipleMarried.width = BarWidth;
		rectMultipleMarried.height = ofMap(hh_multiple_married, 0, 7720787, 0, mapHeightMax);
		ofRotateZ(45);
		ofDrawRectangle(rectMultipleMarried);
		//Center Circle
		ofSetColor(ofColor(255, 255, 255, 100));
		ofDrawCircle(0, 0, 60);

		//Multiple Not Married Bar
		ofSetColor(ofColor::yellow);
		rectMultipleNotMarried.x = -12.5;
		rectMultipleNotMarried.y = barY;
		rectMultipleNotMarried.width = BarWidth;
		rectMultipleNotMarried.height = ofMap(hh_multiple_notmarried, 0, 7720787, 0, mapHeightMax);
		ofRotateZ(45);
		ofDrawRectangle(rectMultipleNotMarried);

		//Multiple Single Parent Bar
		ofSetColor(ofColor::cyan);
		rectMultipleSingleParent.x = -12.5;
		rectMultipleSingleParent.y = barY;
		rectMultipleSingleParent.width = BarWidth;
		rectMultipleSingleParent.height = ofMap(hh_multiple_singleparent, 0, 7720787, 0, mapHeightMax);
		ofRotateZ(45);
		ofDrawRectangle(rectMultipleSingleParent);
		//Center Circle
		ofSetColor(ofColor(255, 255, 255, 100));
		ofDrawCircle(0, 0, 60);

		//Multiple Other Bar
		ofSetColor(ofColor::orange);
		rectMultipleOther.x = -12.5;
		rectMultipleOther.y = barY;
		rectMultipleOther.width = BarWidth;
		rectMultipleOther.height = ofMap(hh_multiple_other, 0, 7720787, 0, mapHeightMax);
		ofRotateZ(45);
		ofDrawRectangle(rectMultipleOther);
		
		//Center Circle
		ofSetColor(ofColor(255, 255, 255, 255));
		ofDrawCircle(0, 0, 60);

		string yearText;
		yearText = ofToString(roundf(years[currentYear]));
		ofSetColor(ofColor(000, 000, 000));
		ofRotateZ(-45);
		font.drawString(yearText, -25, 15);

		ofSetColor(ofColor(255, 255, 255));

		ofRotateZ(45);
		ofSetColor(ofColor::red);
		amountFont.drawString(multipleText, -2.1 * ofMap(hh_multiple, 0, 7720787, 0, mapHeightMax), 12.5);
		ofSetColor(ofColor::white);
		amountFont.drawString(totalText, 25 + ofMap(hh_totaal, 0, 7720787, 0, mapHeightMax), 0);


	}
	cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

	currentYear = ofMap(x, 0, ofGetWidth(), 0, 5);
}