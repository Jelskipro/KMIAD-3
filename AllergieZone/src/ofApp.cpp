#include "ofApp.h"

void ofApp::setup() {
	gui.setup("Instellingen", "settings.xml");
	gui.add(xPos.set("xPos", 0, 0, -3000));
	gui.add(yPos.set("yPos", 0, 0, 3000));

	ofSetCircleResolution(60);

	font.load("Futura PT Heavy.ttf", 200);
	circleFont.load("Futura PT Heavy.ttf", 50);
	ripple.load("Ripple.png");

	string databasePath = ofToDataPath("allergiezonedb.db", true);
	db = new SQLite::Database(databasePath);
	
	ofSetBackgroundColor(ofColor(249, 249, 225));
	cam.setPosition(0, 0, 4000);

	query = new SQLite::Statement(*db, "select gk.name, s.stellingid, s.stelling, c.categorie, gk.zone from stellingen s left join GebruikerKeuze gk on s.stellingId = gk.stellingId left join categorie c on c.categorieId = s.categorieId where gk.name=?");
	queryCompare = new SQLite::Statement(*db, "select gk.name, s.stellingid, s.stelling, c.categorie, gk.zone from stellingen s left join GebruikerKeuze gk on s.stellingId = gk.stellingId left join categorie c on c.categorieId = s.categorieId where gk.name=?");
}

void ofApp::update() {
	for (unsigned int i = 0; i < textBlocks.size(); i++) {
		textBlocks[i].update();
	}
	for (unsigned int i = 0; i < textBlocksCompare.size(); i++) {
		textBlocksCompare[i].update();
	}

	SQLite::Statement usersQuery(*db, "Select * FROM Gebruiker");
	maxUsers = db->execAndGet("SELECT COUNT(Name) FROM Gebruiker").getInt();
	while (usersQuery.executeStep())
	{	
		userNames.push_back(usersQuery.getColumn("Name")); // add an element

	}

}

void ofApp::draw() {
	gui.draw();

	cam.setVFlip(true);
	cam.begin();
	
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


	ofSetColor(allergieRood);
	ripple.draw(-205, 20, 410, 25);
	
	ofSetColor(tekstZwart);
	circleFont.drawString("Allergie zone", -200, 0);
	circleFont.drawString("Kut", zoneCircleRadius + 10, 0);
	circleFont.drawString("Irritant", zoneCircleRadius * 2 + 10, 0);
	circleFont.drawString("Neutraal", zoneCircleRadius * 3 + 10, 0);
	circleFont.drawString("Prima", zoneCircleRadius * 4 + 10, 0);
	circleFont.drawString("Geweldig", zoneCircleRadius * 5 + 10, 0);
	
	font.drawString(userNames[currentUser], -2000, -2000);
	ofSetColor(tekstBlauw);
	font.drawString(userNames[currentUserCompare], 2000, -2000);
	ofSetColor(tekstZwart);


	query->bind(1, userNames[currentUser]);
	while (query->executeStep())
	{
		
		for (unsigned int i = 0; i < textBlocks.size(); i++) {
			textBlocks[i].draw();
		}
		if (a < 13) {
			dataDing(query->getColumn("stelling"), query->getColumn("zone"), query->getColumn("categorie"));
			
		}
		

	}
	query->reset();

	ofSetColor(tekstBlauw);

	queryCompare->bind(1, userNames[currentUserCompare]);
	while (queryCompare->executeStep())
	{

		for (unsigned int i = 0; i < textBlocksCompare.size(); i++) {
			textBlocksCompare[i].draw();
		}
		if (b < 13) {
			dataDingCompare(queryCompare->getColumn("stelling"), queryCompare->getColumn("zone"), queryCompare->getColumn("categorie"));

		}


	}
	queryCompare->reset();

	//ofLog() << currentUser << endl;
	//cout << userNames[currentUser] << endl;
	mousePos = ofVec3f(ofGetMouseX(), ofGetMouseY(), 4000);

	worldMousePos = cam.screenToWorld(ofVec3f(ofGetMouseX(), ofGetMouseY(), 0), ofGetCurrentViewport());

	ofLog() << worldMousePos << endl;
	
	cam.end();


}

void ofApp::keyPressed(int key) {
	if (key == OF_KEY_RIGHT && currentUser < (maxUsers - 1)) {
		currentUser += 1;
		textBlocks.clear();
		a = 0;

	}
	if (key == OF_KEY_LEFT && currentUser > 0) {
		currentUser -= 1;
		textBlocks.clear();
		a = 0;
	}

	if (key == OF_KEY_UP && currentUserCompare < (maxUsers - 1)) {
		currentUserCompare += 1;
		textBlocksCompare.clear();
		b = 0;

	}
	if (key == OF_KEY_DOWN && currentUserCompare > 0) {
		currentUserCompare -= 1;
		textBlocksCompare.clear();
		b = 0;
	}

}

void ofApp::mouseMoved(int x, int y) {

}
void ofApp::mousePressed(int x, int y, int button) {
	if (button == 0 && zoomedIn == false) {

		//cam.setPosition(mousePos.x, mousePos.y, 2000);
		zoomIn();
		zoomedIn = true;
	}
	else
	{
		cam.setPosition(0, 0, 4000);
		zoomedIn = false;

	}
	
}
void ofApp::dataDing(string content, string zone, string category) {
	
	textBlock newTextBlock;
	newTextBlock.setup(content, zone, category);
	textBlocks.push_back(newTextBlock);
	a++;
}
void ofApp::dataDingCompare(string content, string zone, string category) {

	textBlock newTextBlockCompare;
	newTextBlockCompare.setup(content, zone, category);
	textBlocksCompare.push_back(newTextBlockCompare);
	b++;


}
void ofApp::zoomIn()
{
	cam.setPosition(worldMousePos.x, worldMousePos.y, 2000);

}