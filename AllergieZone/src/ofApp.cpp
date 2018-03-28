#include "ofApp.h"

void ofApp::setup() {
	ofSetCircleResolution(60);

	//Laad de fonts.
	font.load("Futura PT Heavy.ttf", 200);
	circleFont.load("Futura PT Heavy.ttf", 50);
	blockFont.load("Futura PT Book.ttf", 25);

	//Laad de foto voor het ribbel lijntje. 
	ripple.load("Ripple.png");

	string databasePath = ofToDataPath("allergiezonedb.db", true);
	db = new SQLite::Database(databasePath);
	
	ofSetBackgroundColor(ofColor(249, 249, 225));

	//Zorg ervoor dat de camera een mooi afstand heeft vanaf het begin.
	cam.setDistance(4000);

	query = new SQLite::Statement(*db, "select gk.name, s.stellingid, s.stelling, c.categorie, gk.zone from stellingen s left join GebruikerKeuze gk on s.stellingId = gk.stellingId left join categorie c on c.categorieId = s.categorieId where gk.name=?");

	//2e query voor de gebruiker waarmee je vergelijkt. Zelfde als de bovenste.
	queryCompare = new SQLite::Statement(*db, "select gk.name, s.stellingid, s.stelling, c.categorie, gk.zone from stellingen s left join GebruikerKeuze gk on s.stellingId = gk.stellingId left join categorie c on c.categorieId = s.categorieId where gk.name=?");
}

void ofApp::update() {
	for (unsigned int i = 0; i < textBlocks.size(); i++) {
		textBlocks[i].update();
	}
	for (unsigned int i = 0; i < textBlocksCompare.size(); i++) {
		textBlocksCompare[i].update();
	}

	//Query om alle gebruikers uit de database te halen.
	SQLite::Statement usersQuery(*db, "Select * FROM Gebruiker");
	
	//Kijk naar hoeveel gebruikers er zijn in totaal.
	maxUsers = db->execAndGet("SELECT COUNT(Name) FROM Gebruiker").getInt();
	while (usersQuery.executeStep())
	{	
		//Zet de gebruikers in een vector
		userNames.push_back(usersQuery.getColumn("Name"));

	}

}

void ofApp::draw() {
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

	//Teken de ribbel lijn.
	ofSetColor(allergieRood);
	ripple.draw(-205, 20, 410, 25);
	
	//Teken alle zone anduidingen.
	ofSetColor(tekstZwart);
	circleFont.drawString("Allergie zone", -200, 0);
	circleFont.drawString("Kut", zoneCircleRadius + 10, 0);
	circleFont.drawString("Irritant", zoneCircleRadius * 2 + 10, 0);
	circleFont.drawString("Neutraal", zoneCircleRadius * 3 + 10, 0);
	circleFont.drawString("Prima", zoneCircleRadius * 4 + 10, 0);
	circleFont.drawString("Geweldig", zoneCircleRadius * 5 + 10, 0);
	
	//Teken de huidige geselecteerde gebruiker.
	font.drawString(userNames[currentUser], -2000, -2000);
	ofSetColor(tekstBlauw);
	//Teken de huidige geselecteerde gebruiker waarmee je wilt vergelijken.
	font.drawString(userNames[currentUserCompare], 2000, -2000);
	ofSetColor(tekstZwart);

	//Bind de huidige gebruiker aan de query
	query->bind(1, userNames[currentUser]);
	while (query->executeStep())
	{
		
		for (unsigned int i = 0; i < textBlocks.size(); i++) {
			textBlocks[i].draw();
		}
		//Zorg dat hij zoveel blokken aan maakt als dat er stellingen zijn. 
		if (a < 25) {
			//Voer de functie uit om een tekst block te maken, vraag de zone, content en categorie op.
			dataDing(query->getColumn("stelling"), query->getColumn("zone"), query->getColumn("categorie"));
			
		}
	}
	//Reset de query weer zodat de volgende uitgevoerd kan worden.
	query->reset();

	ofSetColor(tekstBlauw);

	//Doe hetzelfde als hierboven maar dan voor de gebruiker waarmee je wilt vergelijken.
	queryCompare->bind(1, userNames[currentUserCompare]);
	while (queryCompare->executeStep())
	{

		for (unsigned int i = 0; i < textBlocksCompare.size(); i++) {
			textBlocksCompare[i].draw();
		}
		if (b < 25) {
			dataDingCompare(queryCompare->getColumn("stelling"), queryCompare->getColumn("zone"), queryCompare->getColumn("categorie"));

		}


	}
	//Reset ook deze query weer.
	queryCompare->reset();
	
	cam.end();
}

void ofApp::keyPressed(int key) {
	//Als je op rechter pijltje drukt en je niet op het max aantal gebruikers zit ga 1 plek omhoog in de vector van gebruikers
	if (key == OF_KEY_RIGHT && currentUser < (maxUsers - 1)) {
		//1 gebruiker omhoog.
		currentUser += 1;
		//Maak de vector van tekstblokken leeg zodat de oude van de vorige gebruiker weg gaan.
		textBlocks.clear();
		//Zet a weer op nul zodat het if statement weer uitgevoerd wordt.
		a = 0;

	}
	//Zelfde als hierboven maar dan voor achteruit gaan in de vector van gebruikers
	if (key == OF_KEY_LEFT && currentUser > 0) {
		currentUser -= 1;
		textBlocks.clear();
		a = 0;
	}
	//Zelfde maar dan voor de gebruikers waarmee je vergelijkt.
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
	
	
}
void ofApp::dataDing(string content, string zone, string category) {
	//Maak een nieuw tekstblock aan met de tekstBlock class.
	textBlock newTextBlock;
	newTextBlock.setup(content, zone, category, blockFont);
	textBlocks.push_back(newTextBlock);
	a++;
}
void ofApp::dataDingCompare(string content, string zone, string category) {

	textBlock newTextBlockCompare;
	newTextBlockCompare.setup(content, zone, category, blockFont);
	textBlocksCompare.push_back(newTextBlockCompare);
	b++;


}
void ofApp::zoomIn()
{
	//Oude troep.
	//cam.setPosition(worldMousePos.x, worldMousePos.y, 2000);

}