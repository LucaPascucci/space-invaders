#include <windows.h> 
#include <stdlib.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glui.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdarg.h>
#include <tchar.h>

//con questo codice non viene visualizzat la console di windows
#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

using namespace std;

#define intervalloIdle 17
#define PI 3.14159265
#define timerAvvioStelle 55
#define timerAvvioTitolo 160
#define timerAvvioAstronaveMadre 530
#define timerAvvioIstruzioni 810
#define timerAlieno1 900
#define timerAlieno2 990
#define timerAvvioNavicella 1050
#define timerSparoMissile 1235
#define timerEsplosioniPresentazione 1700
#define larghezzaTitolo 1108
#define altezzaTitolo 100 
#define bordoSuperioreTitolo altezzaDisplay/8
#define	bordoSinistroAstronaveMadre larghezzaDisplay/13
#define interspazioAlieniPresentazione 25
#define bordoSinistroIstruzioni (larghezzaDisplay/6)*4.7
#define bordoSuperioreIstruzioni (altezzaDisplay/10)*6 
#define interlineaIstruzioni 30
#define spaziaturaIstruzioni 180
#define larghezzaInfo 507
#define bordoInferioreInfo altezzaDisplay/6
#define larghezzaCoins 160
#define altezzaCoins_Punteggio 15
#define lampeggioCoins 30
#define nomeNavicella 'N'
#define nomeAstronaveMadreAliena 'M'
#define nomeAlienoPiccolo 'P'
#define nomeAlienoGrosso 'G'
#define nomeAlienoChela 'C'
#define scalerNavicella 3
#define scalerAstronaveAliena 7
#define scalerAlienoGrosso 5
#define scalerAlienoPiccolo 6
#define scalerAlienoChela 5
#define scalerXEsplosioneNavicella 7
#define scalerYEsplosioneNavicella 10
#define scalerYEsplosioneAstronaveMadre 7
#define scalerXEsplosioneAstronaveMadre 9
#define scalerYEsplosioneAlienoGrosso 6
#define scalerXEsplosioneAlienoGrosso 4.5
#define scalerYEsplosioneAlienoPiccolo 6.5
#define scalerXEsplosioneAlienoPiccolo 3.5
#define scalerYEsplosioneAlienoChela 6
#define scalerXEsplosioneAlienoChela 4
#define altezzaMissileCentrale 4*scalerNavicella
#define altezzaMissiliDestraSinistra 3*scalerNavicella
#define altezzaMissileAlieno 5*scalerNavicella
#define larghezzaMissili 2*scalerNavicella
#define larghezzaMissileAlieno 3*scalerNavicella
#define altMissCentrBaseNavetta 29*scalerNavicella
#define altMissSinDesBaseNavicella 15*scalerNavicella
#define larghMissCentrLatoDestraNavicella 15*scalerNavicella
#define larghMissDestrLatoDestraNavicella 30*scalerNavicella
#define larghezzaNavicella 32*scalerNavicella
#define altezzaNavicella 33*scalerNavicella
#define larghezzaAstronaveMadre 16*scalerAstronaveAliena
#define altezzaAstronaveMadre 7*scalerAstronaveAliena
#define larghezzaAlienoGrosso 12*scalerAlienoGrosso
#define altezzaAlienoGrosso	8*scalerAlienoGrosso
#define larghezzaAlienoPiccolo 8*scalerAlienoPiccolo
#define altezzaAlienoPiccolo 8*scalerAlienoPiccolo
#define larghezzaAlienoChela 11*scalerAlienoChela
#define altezzaAlienoChela 8*scalerAlienoChela
#define larghezzaEsplosione 13
#define altezzaEsplosione 7
#define nomeArmaSinistra 'S'
#define nomeArmaCentrale 'C'
#define nomeArmaDestra 'D'
#define missileAlieno 'A'
#define numeroVerticiStella 5
#define scalerStella 10
#define altezzaLineaInvasione altezzaDisplay/3
#define bordoInfSupDisplay altezzaDisplay/15 
#define larghezzaPausa 60
#define larghezzaSounds 180
#define larghezzaPunteggio 110
#define scalerViteNavicella 1
#define spostamentoCostanteMissili 5
#define spostamentoInizialeMissile 0
#define tempoAttesaNuovoMissile 25
#define numeroAlieniPerRiga 10
#define numeroRigheAlieni 5
#define xInizialeGruppoAlieni larghezzaDisplay/15
#define yInizialeGruppoAlieni (altezzaDisplay/10)*8.5
#define spazioOrizzontaleAlieni altezzaDisplay/16
#define timerEsplosioneAlieniGioco 30
#define larghezzaGameOver 778
#define larghezzaInfoFineGioco 500
#define larghezzaYouWon 630

typedef struct {
	float red,green,blue;
} rgbColor;

typedef struct{
	float x, y;
} Point;

typedef struct {
	Point posizione;
	char nomeArma;
} DatiMissile;

typedef struct {
	Point posizione;
	char nomeAlieno;
	bool alienoSpecifico;
	bool colpito;
	int timerEsplosione;
	rgbColor colore;
} Alieno;

rgbColor nero = {0.0,0.0,0.0};
rgbColor bianco = {255.0,255.0,255.0};
rgbColor azzurroNavicella = {0.0,204.0,255.0};
rgbColor arancione = {255.0,78.0,0.0};
rgbColor gialloNavicella = {255.0,165.0,0.0};
rgbColor grigio = {123.0,123.0,117.0};
rgbColor rosso = {255.0,0.0,0.0};
rgbColor verde = {0.0,255.0,0.0};
rgbColor gialloStella = {255.0,255.0,54.0};
rgbColor viola = {255.0,0.0,255.0};
rgbColor blu = {0.0,0.0,255.0};
rgbColor giallo = {255.0,255.0,0.0};
rgbColor azzurro = {0.0,255.0,255.0};

int altezzaDisplay,larghezzaDisplay,windowsID,punteggio,viteNavicella;
bool startGame,finishGame,pauseGame,sound,vittoria;
Point posizioneVite;

int timerGlobalePresentazione,numeroMonete,tempoLampeggioCoins;
bool inizioIntro,esplosioniAlieniPresentazione;
int puntoPartenzaTitolo,puntoPartenzaIstruzioni;
Point posizioneAstronaveMadrePresentazione;
Point posizioneAlieno1Presentazione;
Point posizioneAlieno2Presentazione;
Point posizioneNavicellaPresentazione;
DatiMissile missilePresentazione;

Point poliStelle[numeroVerticiStella];
int numeroStelle;

Point posizioneNavicellaGioco;
int contatoreFrecciaDestra,contatoreFrecciaSinistra;

int tempoBaseAttesaMissile,timerPotenziamentoMissili;
vector<DatiMissile>	posizioniMissili;
Point posInizialeGruppoAlieni;
float interspazioVerticale;
Alieno alienoCorrente;
vector<Alieno> disposizioneAlieni;
Alieno navicellaAlienaMadre;
bool movimentoGruppo;
int incrementoMovimentoGruppo,timerIncrementoGruppo,moltiplicatoreVelocit‡Gruppo;
int timerDiscesaGruppo,valoreDiscesa,moltiplicatoreDiscesaGruppo;
vector<DatiMissile> posizioniMissiliAlieni;
int timerMissiliAlieni;
int timerInfoFineGioco;

float contatoreFrame,tempoFramePrecendente,fps,tempoCorrente,intervalloFrames,tempoIdlePrecedente,riposoIdle;

void inizializzazioneVariabili(){

	punteggio = 0;
	startGame = false;
	finishGame = false;
	pauseGame = false;
	vittoria = false;
	sound = true;
	viteNavicella = 3;
	posizioneVite.x = 70.0;
	posizioneVite.y = altezzaDisplay - (altezzaNavicella/scalerNavicella);
	posizioniMissiliAlieni.clear();
	posizioniMissili.clear();
	disposizioneAlieni.clear();

	timerGlobalePresentazione = 0;
	inizioIntro = true;
	puntoPartenzaTitolo = altezzaDisplay;
	puntoPartenzaIstruzioni = larghezzaDisplay;
	posizioneAstronaveMadrePresentazione.x = -larghezzaAstronaveMadre;
	posizioneAstronaveMadrePresentazione.y = altezzaDisplay/2;
	posizioneAlieno1Presentazione.x = bordoSinistroAstronaveMadre - interspazioAlieniPresentazione - larghezzaAlienoGrosso;
	posizioneAlieno1Presentazione.y = posizioneAstronaveMadrePresentazione.y;
	posizioneAlieno2Presentazione.x = bordoSinistroAstronaveMadre + larghezzaAstronaveMadre + interspazioAlieniPresentazione;
	posizioneAlieno2Presentazione.y = posizioneAstronaveMadrePresentazione.y;
	posizioneNavicellaPresentazione.x = bordoSinistroAstronaveMadre;
	posizioneNavicellaPresentazione.y = -altezzaNavicella;
	missilePresentazione.nomeArma = nomeArmaCentrale;
	Point posizioneMissilePresentazione = {posizioneNavicellaPresentazione.x + larghMissCentrLatoDestraNavicella, bordoInfSupDisplay + altMissCentrBaseNavetta};
	missilePresentazione.posizione = posizioneMissilePresentazione;

	esplosioniAlieniPresentazione = false;
	tempoLampeggioCoins = 0;
	numeroMonete = 0;

	numeroStelle = 100;
	for (int i = 0; i< numeroVerticiStella; i++)
	{
		poliStelle[i].x = cos(float((2*PI)*i/numeroVerticiStella));
		poliStelle[i].y = sin(float((2*PI)*i/numeroVerticiStella));
	}

	posizioneNavicellaGioco.x = larghezzaDisplay/2 - larghezzaNavicella/2;
	posizioneNavicellaGioco.y = bordoInfSupDisplay;
	contatoreFrecciaDestra = 0;
	contatoreFrecciaSinistra = 0;

	timerPotenziamentoMissili = 300;
	tempoBaseAttesaMissile = 0;

	movimentoGruppo = true; //true = destra, false = sinistra;
	timerIncrementoGruppo = 600;
	moltiplicatoreVelocit‡Gruppo = 1;
	timerDiscesaGruppo = 350;
	valoreDiscesa = 0;
	moltiplicatoreDiscesaGruppo = 0;
	timerMissiliAlieni = 120;

	posInizialeGruppoAlieni.x = xInizialeGruppoAlieni;
	posInizialeGruppoAlieni.y = yInizialeGruppoAlieni;
	alienoCorrente.colpito = false;
	alienoCorrente.timerEsplosione = timerEsplosioneAlieniGioco;
	for (int tipoAlieno = 0; tipoAlieno < numeroRigheAlieni; tipoAlieno++){
		for (int t = 0; t < numeroAlieniPerRiga; t++){
			alienoCorrente.posizione = posInizialeGruppoAlieni;
			switch (tipoAlieno)
			{
			case 0:
				alienoCorrente.nomeAlieno = nomeAlienoGrosso;
				alienoCorrente.alienoSpecifico = false;
				alienoCorrente.colore = verde;
				interspazioVerticale = (larghezzaDisplay - xInizialeGruppoAlieni*2 - larghezzaAlienoGrosso*10)/9;
				posInizialeGruppoAlieni.x += larghezzaAlienoGrosso;
				break;
			case 1:
				alienoCorrente.nomeAlieno = nomeAlienoPiccolo;
				alienoCorrente.alienoSpecifico = false;
				alienoCorrente.colore = viola;
				interspazioVerticale = (larghezzaDisplay - xInizialeGruppoAlieni*2 - larghezzaAlienoPiccolo*10)/9;
				posInizialeGruppoAlieni.x += larghezzaAlienoPiccolo;
				break;
			case 2:
				alienoCorrente.nomeAlieno = nomeAlienoChela;
				alienoCorrente.alienoSpecifico = NULL;
				alienoCorrente.colore = blu;
				interspazioVerticale = (larghezzaDisplay - xInizialeGruppoAlieni*2 - larghezzaAlienoChela*10)/9;
				posInizialeGruppoAlieni.x += larghezzaAlienoChela;
				break;
			case 3:
				alienoCorrente.nomeAlieno = nomeAlienoGrosso;
				alienoCorrente.alienoSpecifico = true;
				alienoCorrente.colore = giallo;
				interspazioVerticale = (larghezzaDisplay - xInizialeGruppoAlieni*2 - larghezzaAlienoGrosso*10)/9;
				posInizialeGruppoAlieni.x += larghezzaAlienoGrosso;
				break;
			case 4:
				alienoCorrente.nomeAlieno = nomeAlienoPiccolo;
				alienoCorrente.alienoSpecifico = true;
				alienoCorrente.colore = azzurro;
				interspazioVerticale = (larghezzaDisplay - xInizialeGruppoAlieni*2 - larghezzaAlienoPiccolo*10)/9;
				posInizialeGruppoAlieni.x += larghezzaAlienoPiccolo; 
				break;
			}
			disposizioneAlieni.push_back(alienoCorrente);
			posInizialeGruppoAlieni.x += interspazioVerticale;
		}
		posInizialeGruppoAlieni.x = xInizialeGruppoAlieni;
		posInizialeGruppoAlieni.y -= spazioOrizzontaleAlieni;
		navicellaAlienaMadre.colore = rosso;
		navicellaAlienaMadre.colpito = false;
		navicellaAlienaMadre.nomeAlieno = nomeAstronaveMadreAliena;
		navicellaAlienaMadre.timerEsplosione = timerEsplosioneAlieniGioco;
		navicellaAlienaMadre.posizione.x = -larghezzaDisplay;
		navicellaAlienaMadre.posizione.y = (altezzaDisplay/10)*9;

		timerInfoFineGioco = 30;

		contatoreFrame = 0.0;
		tempoFramePrecendente = 0.0;
		intervalloFrames = 0.0;
		fps = 0.0;
		tempoCorrente = 0.0;
		tempoIdlePrecedente = 0.0;
		riposoIdle = 0.0;
	}
}

float convertRGB(float value){
	return value/255.0;
}

int random(int m){ //ritorna un valore random tra 0 e m-1
	return rand()%m;
}

void calcolaFPS()
{
	//  incremento il contatore di frame
	contatoreFrame++;
	// Prendo il numero di millisecondi dalla prima chiamata del glutInit utilizzando glutGet(GLUT ELAPSED TIME))
	tempoCorrente = glutGet(GLUT_ELAPSED_TIME);

	//controllo se il tempo(millisecondi) che intercorre tra due cicli  idle Ë maggiore del tempo impostato di default
	if (tempoCorrente - tempoIdlePrecedente < intervalloIdle){
		//idle troppo veloce = imposto un valore per lo Sleep
		riposoIdle = intervalloIdle - (tempoCorrente - tempoIdlePrecedente);
	}else{
		//idle veloce il giusto oppure troppo lento
		riposoIdle = 0;
	}
	tempoIdlePrecedente = tempoCorrente;

	//  Calcolo il tempo passato
	intervalloFrames = tempoCorrente - tempoFramePrecendente;

	//finchË non Ë passato un secondo non posso calcolare il numero di frame
	if(intervalloFrames >= 1000)
	{
		//  Calcolo il numero di frame per secondocalculate the number of frames per second
		fps = contatoreFrame / (intervalloFrames / 1000.0f);

		//  imposto il tempo precedente
		tempoFramePrecendente = tempoCorrente;

		//  Resetto il contatore dei frame
		contatoreFrame = 0;
	}
}

//convertire intero a stringa
string int2str(int valore){

	stringstream ss;
	ss << valore;
	return ss.str();
}

void disegnaTestoStroke(float x, float y, string text, rgbColor color){

	glPushMatrix();
	glColor3f(convertRGB(color.red),convertRGB(color.green),convertRGB(color.blue));
	glTranslatef(x,y,0.0);
	for (int i = 0; i < text.length(); i++){
		glutStrokeCharacter(GLUT_STROKE_ROMAN,text[i]);
	}
	glPopMatrix();
}

void disegnaTestoBitmap(float x, float y, string text, rgbColor color){

	glPushMatrix();
	glColor3f(convertRGB(color.red),convertRGB(color.green),convertRGB(color.blue));
	glRasterPos2f(x,y);
	for (int i = 0; i < text.length();i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	}
	glPopMatrix();
}

void istruzioni(){

	disegnaTestoBitmap(puntoPartenzaIstruzioni, bordoSuperioreIstruzioni,"INSTRUCTIONS",bianco);
	disegnaTestoBitmap(puntoPartenzaIstruzioni, bordoSuperioreIstruzioni - interlineaIstruzioni,"RIGHT :",bianco);
	disegnaTestoBitmap(puntoPartenzaIstruzioni + spaziaturaIstruzioni, bordoSuperioreIstruzioni - interlineaIstruzioni,"RIGHT ARROW",bianco);
	disegnaTestoBitmap(puntoPartenzaIstruzioni, bordoSuperioreIstruzioni - interlineaIstruzioni*2,"LEFT :",bianco);
	disegnaTestoBitmap(puntoPartenzaIstruzioni + spaziaturaIstruzioni, bordoSuperioreIstruzioni - interlineaIstruzioni*2,"LEFT ARROW",bianco);
	disegnaTestoBitmap(puntoPartenzaIstruzioni, bordoSuperioreIstruzioni - interlineaIstruzioni*3,"SHOOT :",bianco);
	disegnaTestoBitmap(puntoPartenzaIstruzioni + spaziaturaIstruzioni, bordoSuperioreIstruzioni - interlineaIstruzioni*3,"SPACEBAR",bianco);
	disegnaTestoBitmap(puntoPartenzaIstruzioni, bordoSuperioreIstruzioni - interlineaIstruzioni*4,"PAUSE :",bianco);
	disegnaTestoBitmap(puntoPartenzaIstruzioni + spaziaturaIstruzioni, bordoSuperioreIstruzioni - interlineaIstruzioni*4,"p",bianco);
	disegnaTestoBitmap(puntoPartenzaIstruzioni, bordoSuperioreIstruzioni - interlineaIstruzioni*5,"PLAY :",bianco);
	disegnaTestoBitmap(puntoPartenzaIstruzioni + spaziaturaIstruzioni, bordoSuperioreIstruzioni - interlineaIstruzioni*5,"ENTER",bianco);
	disegnaTestoBitmap(puntoPartenzaIstruzioni, bordoSuperioreIstruzioni - interlineaIstruzioni*6,"COIN :",bianco);
	disegnaTestoBitmap(puntoPartenzaIstruzioni + spaziaturaIstruzioni, bordoSuperioreIstruzioni - interlineaIstruzioni*6,"c",bianco);
	disegnaTestoBitmap(puntoPartenzaIstruzioni, bordoSuperioreIstruzioni - interlineaIstruzioni*7,"DISABLE SOUND :",bianco);
	disegnaTestoBitmap(puntoPartenzaIstruzioni + spaziaturaIstruzioni, bordoSuperioreIstruzioni - interlineaIstruzioni*7,"s",bianco);
	disegnaTestoBitmap(puntoPartenzaIstruzioni, bordoSuperioreIstruzioni - interlineaIstruzioni*8,"EXIT :",bianco);
	disegnaTestoBitmap(puntoPartenzaIstruzioni + spaziaturaIstruzioni, bordoSuperioreIstruzioni - interlineaIstruzioni*8,"esc",bianco);
}

void stella(){

	glPushMatrix();
	glTranslatef(random(larghezzaDisplay),random(altezzaDisplay),0.0);
	glScalef(scalerStella,scalerStella,1.0);
	glColor3f(convertRGB(gialloStella.red),convertRGB(gialloStella.green),convertRGB(gialloStella.blue));
	glBegin(GL_LINE_LOOP);
	glVertex2d(poliStelle[1].x, poliStelle[1].y);
	glVertex2d(poliStelle[4].x, poliStelle[4].y);
	glVertex2d(poliStelle[2].x, poliStelle[2].y);
	glVertex2d(poliStelle[0].x, poliStelle[0].y);
	glVertex2d(poliStelle[3].x, poliStelle[3].y);
	glEnd();
	glPopMatrix();
}

void navicella (Point posizione,int scaler){

	glPushMatrix();
	glTranslatef(posizione.x, posizione.y, 0.0);
	glScalef(scaler,scaler,0.0);
	glBegin(GL_QUAD_STRIP);	
	glColor3f(convertRGB(bianco.red),convertRGB(bianco.green),convertRGB(bianco.blue));

	//Lancia Sinistra
	glVertex2d(0.0, 0.0);
	glVertex2d(0.0, 15.0);
	glVertex2d(2.0, 0.0);
	glVertex2d(2.0, 15.0);
	glVertex2d(2.0, 0.0);
	glVertex2d(2.0, 8.0);

	//Ala Sinistra
	glVertex2d(3.0, 0.0);
	glVertex2d(3.0, 8.0);
	glVertex2d(3.0, 2.0);
	glVertex2d(3.0, 9.0);
	glVertex2d(4.0, 2.0);
	glVertex2d(4.0, 9.0);
	glVertex2d(4.0, 3.0);
	glVertex2d(4.0, 10.0);
	glVertex2d(5.0, 3.0);
	glVertex2d(5.0, 10.0);
	glVertex2d(5.0, 3.0);
	glVertex2d(5.0, 11.0);
	glVertex2d(6.0, 3.0);
	glVertex2d(6.0, 11.0);
	glVertex2d(6.0, 3.0);
	glVertex2d(6.0, 12.0);
	glVertex2d(7.0, 3.0);
	glVertex2d(7.0, 12.0);
	glVertex2d(7.0, 3.0);
	glVertex2d(7.0, 13.0);
	glVertex2d(8.0, 3.0);
	glVertex2d(8.0, 13.0);
	glVertex2d(8.0, 3.0);
	glVertex2d(8.0, 14.0);
	glVertex2d(9.0, 3.0);
	glVertex2d(9.0, 14.0);
	glVertex2d(9.0, 3.0);
	glVertex2d(9.0, 15.0);
	glVertex2d(10.0, 3.0);
	glVertex2d(10.0, 15.0);
	glVertex2d(10.0, 4.0);
	glVertex2d(10.0, 16.0);
	glVertex2d(11.0, 4.0);
	glVertex2d(11.0, 16.0);
	glVertex2d(11.0, 4.0);
	glVertex2d(11.0, 17.0);
	glVertex2d(12.0, 4.0);
	glVertex2d(12.0, 17.0);
	glVertex2d(12.0, 4.0);
	glVertex2d(12.0, 18.0);
	glVertex2d(13.0, 4.0);
	glVertex2d(13.0, 18.0);

	//Corpo Centrale
	glVertex2d(13.0, 3.0);
	glVertex2d(13.0, 24.0);
	glVertex2d(14.0, 3.0);
	glVertex2d(14.0, 24.0);
	glVertex2d(14.0, 3.0);
	glVertex2d(14.0, 29.0);
	glVertex2d(18.0, 3.0);
	glVertex2d(18.0, 29.0);
	glVertex2d(18.0, 3.0);
	glVertex2d(18.0, 24.0);
	glVertex2d(19.0, 3.0);
	glVertex2d(19.0, 24.0);
	glVertex2d(19.0, 4.0);
	glVertex2d(19.0, 18.0);

	//Ala Destra
	glVertex2d(20.0, 4.0);
	glVertex2d(20.0, 18.0);
	glVertex2d(20.0, 4.0);
	glVertex2d(20.0, 17.0);
	glVertex2d(21.0, 4.0);
	glVertex2d(21.0, 17.0);
	glVertex2d(21.0, 4.0);
	glVertex2d(21.0, 16.0);
	glVertex2d(22.0, 4.0);
	glVertex2d(22.0, 16.0);
	glVertex2d(22.0, 3.0);
	glVertex2d(22.0, 15.0);
	glVertex2d(23.0, 3.0);
	glVertex2d(23.0, 15.0);
	glVertex2d(23.0, 3.0);
	glVertex2d(23.0, 14.0);
	glVertex2d(24.0, 3.0);
	glVertex2d(24.0, 14.0);
	glVertex2d(24.0, 3.0);
	glVertex2d(24.0, 13.0);
	glVertex2d(25.0, 3.0);
	glVertex2d(25.0, 13.0);
	glVertex2d(25.0, 3.0);
	glVertex2d(25.0, 12.0);
	glVertex2d(26.0, 3.0);
	glVertex2d(26.0, 12.0);
	glVertex2d(26.0, 3.0);
	glVertex2d(26.0, 11.0);
	glVertex2d(27.0, 3.0);
	glVertex2d(27.0, 11.0);
	glVertex2d(27.0, 3.0);
	glVertex2d(27.0, 10.0);
	glVertex2d(28.0, 3.0);
	glVertex2d(28.0, 10.0);
	glVertex2d(28.0, 2.0);
	glVertex2d(28.0, 9.0);
	glVertex2d(29.0, 2.0);
	glVertex2d(29.0, 9.0);
	glVertex2d(29.0, 0.0);
	glVertex2d(29.0, 8.0);
	glVertex2d(30.0, 0.0);
	glVertex2d(30.0, 8.0);

	//Lancia destra
	glVertex2d(30.0, 0.0);
	glVertex2d(30.0, 15.0);
	glVertex2d(32.0, 0.0);
	glVertex2d(32.0, 15.0);
	glEnd();

	//Motore centrale
	glBegin(GL_QUAD_STRIP);
	glColor3f(convertRGB(rosso.red),convertRGB(rosso.green),convertRGB(rosso.blue));
	glVertex2d(14.0, 3.0);
	glVertex2d(18.0, 3.0);
	glVertex2d(14.0, 2.0);
	glVertex2d(18.0, 2.0);
	glColor3f(convertRGB(arancione.red),convertRGB(arancione.green),convertRGB(arancione.blue));
	glVertex2d(14.0, 1.0);
	glVertex2d(18.0, 1.0);
	glColor3f(convertRGB(gialloNavicella.red),convertRGB(gialloNavicella.green),convertRGB(gialloNavicella.blue));
	glVertex2d(14.0, 0.0);
	glVertex2d(18.0, 0.0);
	glEnd();

	//Motore Sinistro/Basso
	glBegin(GL_QUAD_STRIP);
	glVertex2d(0.0, 0.0);
	glVertex2d(0.0, 1.0);
	glVertex2d(2.0, 0.0);
	glVertex2d(2.0, 1.0);
	glVertex2d(2.0, 0.0);
	glVertex2d(2.0, 3.0);
	glVertex2d(3.0, 0.0);
	glVertex2d(3.0, 3.0);
	glVertex2d(3.0, 2.0);
	glVertex2d(3.0, 4.0);
	glVertex2d(4.0, 2.0);
	glVertex2d(4.0, 4.0);
	glVertex2d(4.0, 3.0);
	glVertex2d(4.0, 4.0);
	glVertex2d(9.0, 3.0);
	glVertex2d(9.0, 4.0);
	glVertex2d(9.0, 3.0);
	glVertex2d(9.0, 5.0);
	glVertex2d(9.0, 3.0);
	glVertex2d(9.0, 5.0);
	glVertex2d(10.0, 3.0);
	glVertex2d(10.0, 5.0);
	glVertex2d(10.0, 4.0);
	glVertex2d(10.0, 5.0);
	glVertex2d(13.0, 4.0);
	glVertex2d(13.0, 5.0);
	glEnd();

	//Motore Destro/Basso
	glBegin(GL_QUAD_STRIP);
	glVertex2d(19.0, 4.0);
	glVertex2d(19.0, 5.0);
	glVertex2d(22.0, 4.0);
	glVertex2d(22.0, 5.0);
	glVertex2d(22.0, 3.0);
	glVertex2d(22.0, 5.0);
	glVertex2d(23.0, 3.0);
	glVertex2d(23.0, 5.0);
	glVertex2d(23.0, 3.0);
	glVertex2d(23.0, 4.0);
	glVertex2d(28.0, 3.0);
	glVertex2d(28.0, 4.0);
	glVertex2d(28.0, 2.0);
	glVertex2d(28.0, 4.0);
	glVertex2d(29.0, 2.0);
	glVertex2d(29.0, 4.0);
	glVertex2d(29.0, 0.0);
	glVertex2d(29.0, 3.0);
	glVertex2d(30.0, 0.0);
	glVertex2d(30.0, 3.0);
	glVertex2d(30.0, 0.0);
	glVertex2d(30.0, 1.0);
	glVertex2d(32.0, 0.0);
	glVertex2d(32.0, 1.0);
	glEnd();

	//Motore Sinistro/Alto
	glBegin(GL_QUAD_STRIP);
	glColor3f(convertRGB(arancione.red),convertRGB(arancione.green),convertRGB(arancione.blue));
	glVertex2d(5.0, 4.0);
	glVertex2d(5.0, 5.0);
	glVertex2d(8.0, 4.0);
	glVertex2d(8.0, 5.0);
	glVertex2d(8.0, 4.0);
	glVertex2d(8.0, 6.0);
	glVertex2d(9.0, 4.0);
	glVertex2d(9.0, 6.0);
	glVertex2d(9.0, 5.0);
	glVertex2d(9.0, 6.0);
	glVertex2d(13.0, 5.0);
	glVertex2d(13.0, 6.0);
	glEnd();

	//Motore Sinistro/Alto
	glBegin(GL_QUAD_STRIP);
	glVertex2d(19.0, 5.0);
	glVertex2d(19.0, 6.0);
	glVertex2d(23.0, 5.0);
	glVertex2d(23.0, 6.0);
	glVertex2d(23.0, 4.0);
	glVertex2d(23.0, 6.0);
	glVertex2d(24.0, 4.0);
	glVertex2d(24.0, 6.0);
	glVertex2d(24.0, 4.0);
	glVertex2d(24.0, 5.0);
	glVertex2d(27.0, 4.0);
	glVertex2d(27.0, 5.0);
	glEnd();

	//Divisorio Sinistro
	glBegin(GL_QUAD_STRIP);
	glColor3f(convertRGB(grigio.red),convertRGB(grigio.green),convertRGB(grigio.blue));
	glVertex2d(11.0, 6.0);
	glVertex2d(11.0, 12.0);
	glVertex2d(12.0, 6.0);
	glVertex2d(12.0, 12.0);
	glVertex2d(12.0, 6.0);
	glVertex2d(12.0, 7.0);
	glVertex2d(13.0, 6.0);
	glVertex2d(13.0, 7.0);
	glEnd();

	//Divisorio Destro
	glBegin(GL_QUAD_STRIP);
	glVertex2d(19.0, 6.0);
	glVertex2d(19.0, 7.0);
	glVertex2d(20.0, 6.0);
	glVertex2d(20.0, 7.0);
	glVertex2d(20.0, 6.0);
	glVertex2d(20.0, 12.0);
	glVertex2d(21.0, 6.0);
	glVertex2d(21.0, 12.0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(convertRGB(azzurroNavicella.red),convertRGB(azzurroNavicella.green),convertRGB(azzurroNavicella.blue));
	//Vetro centrale
	glVertex2d(14.0, 8.0);
	glVertex2d(14.0, 17.0);
	glVertex2d(18.0, 17.0);
	glVertex2d(18.0, 8.0);
	glVertex2d(14.0, 8.0);
	glEnd();

	//Aggiunta Sinistra/Basso
	glBegin(GL_POLYGON);
	glVertex2d(13.0, 9.0);
	glVertex2d(13.0, 12.0);
	glVertex2d(14.0, 12.0);
	glVertex2d(14.0, 9.0);
	glVertex2d(13.0, 9.0);
	glEnd();

	//Aggiunta Sinistra/Alto
	glBegin(GL_POLYGON);
	glVertex2d(13.0, 13.0);
	glVertex2d(13.0, 16.0);
	glVertex2d(14.0, 16.0);
	glVertex2d(14.0, 13.0);
	glVertex2d(13.0, 13.0);
	glEnd();

	//Aggiunta Destra/Alto
	glBegin(GL_POLYGON);
	glVertex2d(18.0, 13.0);
	glVertex2d(18.0, 16.0);
	glVertex2d(19.0, 16.0);
	glVertex2d(19.0, 13.0);
	glVertex2d(18.0, 13.0);
	glEnd();

	//Aggiunta Destra/Basso
	glBegin(GL_POLYGON);
	glVertex2d(18.0, 9.0);
	glVertex2d(18.0, 12.0);
	glVertex2d(19.0, 12.0);
	glVertex2d(19.0, 9.0);
	glVertex2d(18.0, 9.0);
	glEnd();

	glBegin(GL_POLYGON);
	//Arma Sinistra
	glVertex2d(0.0, 15.0);
	glVertex2d(0.0, 18.0);
	glVertex2d(2.0, 18.0);
	glVertex2d(2.0, 15.0);
	glVertex2d(0.0, 15.0);
	glEnd();

	//Arma centrale
	glBegin(GL_POLYGON);
	glVertex2d(15.0, 29.0);
	glVertex2d(15.0, 33.0);
	glVertex2d(17.0, 33.0);
	glVertex2d(17.0, 29.0);
	glVertex2d(15.0, 29.0);
	glEnd();

	//Arma Destra
	glBegin(GL_POLYGON);
	glVertex2d(30.0, 15.0);
	glVertex2d(30.0, 18.0);
	glVertex2d(32.0, 18.0);
	glVertex2d(32.0, 15.0);
	glVertex2d(30.0, 15.0);
	glEnd();

	//Riflesso Alto
	glBegin(GL_QUAD_STRIP);
	glColor3f(convertRGB(bianco.red),convertRGB(bianco.green),convertRGB(bianco.blue));
	glVertex2d(15.0, 13.0);
	glVertex2d(15.0, 16.0);
	glVertex2d(16.0, 13.0);
	glVertex2d(16.0, 16.0);
	glVertex2d(16.0, 15.0);
	glVertex2d(16.0, 16.0);
	glVertex2d(17.0, 15.0);
	glVertex2d(17.0, 16.0);
	glEnd();

	//Riflesso Basso
	glBegin(GL_QUAD_STRIP);
	glVertex2d(15.0, 9.0);
	glVertex2d(15.0, 10.0);
	glVertex2d(16.0, 9.0);
	glVertex2d(16.0, 10.0);
	glVertex2d(16.0, 9.0);
	glVertex2d(16.0, 12.0);
	glVertex2d(17.0, 9.0);
	glVertex2d(17.0, 12.0);
	glEnd();
	glPopMatrix();
}

void missile(DatiMissile informazioni){

	glPushMatrix();
	glTranslatef(informazioni.posizione.x, informazioni.posizione.y, 0.0);
	glScalef(scalerNavicella,scalerNavicella,0.0);
	glColor3f(convertRGB(bianco.red),convertRGB(bianco.green),convertRGB(bianco.blue));

	switch (informazioni.nomeArma)
	{
	case nomeArmaCentrale: 
		glBegin(GL_QUAD_STRIP);
		glVertex2d(0.0, 0.0);
		glVertex2d(0.0, 4.0);
		glVertex2d(2.0, 0.0);
		glVertex2d(2.0, 4.0);
		glEnd();;
		break;

	case nomeArmaDestra:
		glBegin(GL_QUAD_STRIP);
		glVertex2d(0.0, 0.0);
		glVertex2d(0.0, 3.0);
		glVertex2d(2.0, 0.0);
		glVertex2d(2.0, 3.0);
		glEnd();
		break;

	case nomeArmaSinistra:
		glBegin(GL_QUAD_STRIP);
		glVertex2d(0.0, 0.0);
		glVertex2d(0.0, 3.0);
		glVertex2d(2.0, 0.0);
		glVertex2d(2.0, 3.0);
		glEnd();
		break;

	case missileAlieno:
		glBegin(GL_QUAD_STRIP);
		glVertex2d(1.0, 4.0);
		glVertex2d(1.0, 5.0);
		glVertex2d(2.0, 4.0);
		glVertex2d(2.0, 5.0);

		glVertex2d(2.0, 3.0);
		glVertex2d(2.0, 4.0);
		glVertex2d(3.0, 3.0);
		glVertex2d(3.0, 4.0);
		glVertex2d(2.0, 3.0);
		glVertex2d(2.0, 4.0);
		glVertex2d(2.0, 2.0);
		glVertex2d(2.0, 3.0);

		glVertex2d(1.0, 2.0);
		glVertex2d(1.0, 3.0);
		glVertex2d(1.0, 1.0);
		glVertex2d(1.0, 2.0);

		glVertex2d(0.0, 1.0);
		glVertex2d(0.0, 2.0);
		glVertex2d(1.0, 1.0);
		glVertex2d(1.0, 2.0);

		glVertex2d(1.0, 0.0);
		glVertex2d(1.0, 1.0);
		glVertex2d(2.0, 0.0);
		glVertex2d(2.0, 1.0);
		glEnd();
		break;
	}
	glPopMatrix();
}

void esplosione(Point posizione,char grandezzaEsplosione){
	glPushMatrix();
	glTranslatef(posizione.x,posizione.y,0.0);
	switch (grandezzaEsplosione)
	{
	case nomeNavicella:
		glScalef(scalerXEsplosioneNavicella,scalerYEsplosioneNavicella,0.0);
		break;
	case nomeAstronaveMadreAliena:
		glScalef(scalerXEsplosioneAstronaveMadre,scalerYEsplosioneAstronaveMadre,0.0);
		break;
	case nomeAlienoGrosso:
		glScalef(scalerXEsplosioneAlienoGrosso,scalerYEsplosioneAlienoGrosso,0.0);
		break;
	case nomeAlienoPiccolo:
		glScalef(scalerXEsplosioneAlienoPiccolo,scalerYEsplosioneAlienoPiccolo,0.0);
		break;
	case nomeAlienoChela:
		glScalef(scalerXEsplosioneAlienoChela,scalerYEsplosioneAlienoChela,0.0);
		break;
	}

	glColor3f(convertRGB(grigio.red),convertRGB(grigio.green),convertRGB(grigio.blue));
	glBegin(GL_QUAD_STRIP);
	glVertex2d(1.0, 0.0);
	glVertex2d(1.0, 1.0);
	glVertex2d(2.0, 0.0);
	glVertex2d(2.0, 1.0);
	glVertex2d(2.0, 1.0);
	glVertex2d(2.0, 2.0);
	glVertex2d(3.0, 1.0);
	glVertex2d(3.0, 2.0);
	glVertex2d(3.0, 2.0);
	glVertex2d(3.0, 3.0);
	glVertex2d(4.0, 2.0);
	glVertex2d(4.0, 3.0);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glVertex2d(4.0, 0.0);
	glVertex2d(4.0, 1.0);
	glVertex2d(5.0, 0.0);
	glVertex2d(5.0, 1.0);
	glVertex2d(5.0, 1.0);
	glVertex2d(5.0, 2.0);
	glVertex2d(6.0, 1.0);
	glVertex2d(6.0, 2.0);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glVertex2d(7.0, 1.0);
	glVertex2d(7.0, 2.0);
	glVertex2d(8.0, 1.0);
	glVertex2d(8.0, 2.0);
	glVertex2d(8.0, 0.0);
	glVertex2d(8.0, 1.0);
	glVertex2d(9.0, 0.0);
	glVertex2d(9.0, 1.0);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glVertex2d(9.0, 2.0);
	glVertex2d(9.0, 3.0);
	glVertex2d(10.0, 2.0);
	glVertex2d(10.0, 3.0);
	glVertex2d(10.0, 1.0);
	glVertex2d(10.0, 2.0);
	glVertex2d(11.0, 1.0);
	glVertex2d(11.0, 2.0);
	glVertex2d(11.0, 0.0);
	glVertex2d(11.0, 1.0);
	glVertex2d(12.0, 0.0);
	glVertex2d(12.0, 1.0);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glVertex2d(1.0, 6.0);
	glVertex2d(1.0, 7.0);
	glVertex2d(2.0, 6.0);
	glVertex2d(2.0, 7.0);
	glVertex2d(2.0, 5.0);
	glVertex2d(2.0, 6.0);
	glVertex2d(3.0, 5.0);
	glVertex2d(3.0, 6.0);
	glVertex2d(3.0, 4.0);
	glVertex2d(3.0, 5.0);
	glVertex2d(4.0, 4.0);
	glVertex2d(4.0, 5.0);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glVertex2d(4.0, 6.0);
	glVertex2d(4.0, 7.0);
	glVertex2d(5.0, 6.0);
	glVertex2d(5.0, 7.0);
	glVertex2d(5.0, 5.0);
	glVertex2d(5.0, 6.0);
	glVertex2d(6.0, 5.0);
	glVertex2d(6.0, 6.0);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glVertex2d(7.0, 5.0);
	glVertex2d(7.0, 6.0);
	glVertex2d(8.0, 5.0);
	glVertex2d(8.0, 6.0);
	glVertex2d(8.0, 6.0);
	glVertex2d(8.0, 7.0);
	glVertex2d(9.0, 6.0);
	glVertex2d(9.0, 7.0);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glVertex2d(9.0, 4.0);
	glVertex2d(9.0, 5.0);
	glVertex2d(10.0, 4.0);
	glVertex2d(10.0, 5.0);
	glVertex2d(10.0, 5.0);
	glVertex2d(10.0, 6.0);
	glVertex2d(11.0, 5.0);
	glVertex2d(11.0, 6.0);
	glVertex2d(11.0, 6.0);
	glVertex2d(11.0, 7.0);
	glVertex2d(12.0, 6.0);
	glVertex2d(12.0, 7.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(0.0, 3.0);
	glVertex2d(0.0, 4.0);
	glVertex2d(2.0, 4.0);
	glVertex2d(2.0, 3.0);
	glVertex2d(0.0, 3.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(11.0, 3.0);
	glVertex2d(11.0, 4.0);
	glVertex2d(13.0, 4.0);
	glVertex2d(13.0, 3.0);
	glVertex2d(11.0, 3.0);
	glEnd();

	glPopMatrix();
}

void gambeGrosseChiuse(rgbColor colore){

	glPushMatrix();
	glBegin(GL_QUAD_STRIP);
	glColor3f(convertRGB(colore.red),convertRGB(colore.green),convertRGB(colore.blue));

	glVertex2d(1.0, 1.0);
	glVertex2d(1.0, 2.0);
	glVertex2d(2.0, 1.0);
	glVertex2d(2.0, 2.0);
	glVertex2d(2.0, 0.0);
	glVertex2d(2.0, 3.0);
	glVertex2d(3.0, 0.0);
	glVertex2d(3.0, 3.0);
	glVertex2d(3.0, 2.0);
	glVertex2d(3.0, 3.0);
	glVertex2d(5.0, 2.0);
	glVertex2d(5.0, 3.0);
	glVertex2d(5.0, 1.0);
	glVertex2d(5.0, 2.0);
	glVertex2d(7.0, 1.0);
	glVertex2d(7.0, 2.0);
	glVertex2d(7.0, 2.0);
	glVertex2d(7.0, 3.0);
	glVertex2d(9.0, 2.0);
	glVertex2d(9.0, 3.0);
	glVertex2d(9.0, 0.0);
	glVertex2d(9.0, 3.0);
	glVertex2d(10.0, 0.0);
	glVertex2d(10.0, 3.0);
	glVertex2d(10.0, 1.0);
	glVertex2d(10.0, 2.0);
	glVertex2d(11.0, 1.0);
	glVertex2d(11.0, 2.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(3.0, 0.0);
	glVertex2d(3.0, 1.0);
	glVertex2d(4.0, 1.0);
	glVertex2d(4.0, 0.0);
	glVertex2d(3.0, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(8.0, 0.0);
	glVertex2d(8.0, 1.0);
	glVertex2d(9.0, 1.0);
	glVertex2d(9.0, 0.0);
	glVertex2d(8.0, 0.0);
	glEnd();

	glPopMatrix();
}

void gambeGrosseAperte(rgbColor colore){

	glPushMatrix();
	glBegin(GL_QUAD_STRIP);
	glColor3f(convertRGB(colore.red),convertRGB(colore.green),convertRGB(colore.blue));

	glVertex2d(0.0, 0.0);
	glVertex2d(0.0, 1.0);
	glVertex2d(2.0, 0.0);
	glVertex2d(2.0, 1.0);
	glVertex2d(2.0, 1.0);
	glVertex2d(2.0, 2.0);
	glVertex2d(3.0, 1.0);
	glVertex2d(3.0, 2.0);
	glVertex2d(3.0, 1.0);
	glVertex2d(3.0, 3.0);
	glVertex2d(4.0, 1.0);
	glVertex2d(4.0, 3.0);
	glVertex2d(4.0, 2.0);
	glVertex2d(4.0, 3.0);
	glVertex2d(5.0, 2.0);
	glVertex2d(5.0, 3.0);
	glVertex2d(5.0, 1.0);
	glVertex2d(5.0, 2.0);
	glVertex2d(7.0, 1.0);
	glVertex2d(7.0, 2.0);
	glVertex2d(7.0, 2.0);
	glVertex2d(7.0, 3.0);
	glVertex2d(8.0, 2.0);
	glVertex2d(8.0, 3.0);
	glVertex2d(8.0, 1.0);
	glVertex2d(8.0, 3.0);
	glVertex2d(9.0, 1.0);
	glVertex2d(9.0, 3.0);
	glVertex2d(9.0, 1.0);
	glVertex2d(9.0, 2.0);
	glVertex2d(10.0, 1.0);
	glVertex2d(10.0, 2.0);
	glVertex2d(10.0, 0.0);
	glVertex2d(10.0, 1.0);
	glVertex2d(12.0, 0.0);
	glVertex2d(12.0, 1.0);
	glEnd();

	glPopMatrix();

}

void gambePiccoleChiuse(rgbColor colore){

	glPushMatrix();
	glBegin(GL_QUAD_STRIP);
	glColor3f(convertRGB(colore.red),convertRGB(colore.green),convertRGB(colore.blue));

	glVertex2d(0.0, 1.0);
	glVertex2d(0.0, 2.0);
	glVertex2d(1.0, 1.0);
	glVertex2d(1.0, 2.0);
	glVertex2d(1.0, 2.0);
	glVertex2d(1.0, 3.0);
	glVertex2d(2.0, 2.0);
	glVertex2d(2.0, 3.0);
	glVertex2d(2.0, 3.0);
	glVertex2d(2.0, 3.0);
	glVertex2d(3.0, 3.0);
	glVertex2d(3.0, 3.0);
	glVertex2d(3.0, 2.0);
	glVertex2d(3.0, 3.0);
	glVertex2d(5.0, 2.0);
	glVertex2d(5.0, 3.0);
	glVertex2d(5.0, 3.0);
	glVertex2d(5.0, 3.0);
	glVertex2d(6.0, 3.0);
	glVertex2d(6.0, 3.0);
	glVertex2d(6.0, 2.0);
	glVertex2d(6.0, 3.0);
	glVertex2d(7.0, 2.0);
	glVertex2d(7.0, 3.0);
	glVertex2d(7.0, 1.0);
	glVertex2d(7.0, 2.0);
	glVertex2d(8.0, 1.0);
	glVertex2d(8.0, 2.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(1.0, 0.0, 0.0);
	glVertex3d(1.0, 1.0, 0.0);
	glVertex3d(2.0, 1.0, 0.0);
	glVertex3d(2.0, 0.0, 0.0);
	glVertex3d(1.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(6.0, 0.0, 0.0);
	glVertex3d(6.0, 1.0, 0.0);
	glVertex3d(7.0, 1.0, 0.0);
	glVertex3d(7.0, 0.0, 0.0);
	glVertex3d(6.0, 0.0, 0.0);
	glEnd();

	glPopMatrix();
}

void gambePiccoleAperte(rgbColor colore){

	glPushMatrix();
	glBegin(GL_QUAD_STRIP);
	glColor3f(convertRGB(colore.red),convertRGB(colore.green),convertRGB(colore.blue));

	glVertex2d(0.0, 0.0);
	glVertex2d(0.0, 1.0);
	glVertex2d(1.0, 0.0);
	glVertex2d(1.0, 1.0);
	glVertex2d(1.0, 1.0);
	glVertex2d(1.0, 2.0);
	glVertex2d(2.0, 1.0);
	glVertex2d(2.0, 2.0);
	glVertex2d(2.0, 2.0);
	glVertex2d(2.0, 3.0);
	glVertex2d(3.0, 2.0);
	glVertex2d(3.0, 3.0);
	glVertex2d(3.0, 1.0);
	glVertex2d(3.0, 2.0);
	glVertex2d(5.0, 1.0);
	glVertex2d(5.0, 2.0);
	glVertex2d(5.0, 2.0);
	glVertex2d(5.0, 3.0);
	glVertex2d(6.0, 2.0);
	glVertex2d(6.0, 3.0);
	glVertex2d(6.0, 1.0);
	glVertex2d(6.0, 2.0);
	glVertex2d(7.0, 1.0);
	glVertex2d(7.0, 2.0);
	glVertex2d(7.0, 0.0);
	glVertex2d(7.0, 1.0);
	glVertex2d(8.0, 0.0);
	glVertex2d(8.0, 1.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(2.0, 0.0);
	glVertex2d(2.0, 1.0);
	glVertex2d(3.0, 1.0);
	glVertex2d(3.0, 0.0);
	glVertex2d(2.0, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(5.0, 0.0);
	glVertex2d(5.0, 1.0);
	glVertex2d(6.0, 1.0);
	glVertex2d(6.0, 0.0);
	glVertex2d(5.0, 0.0);
	glEnd();

	glPopMatrix();

}

void astronaveMadreAliena(Point posizione,rgbColor colore){

	glPushMatrix();
	glTranslatef(posizione.x,posizione.y,0.0);
	glScalef(scalerAstronaveAliena,scalerAstronaveAliena,0.0);

	glBegin(GL_QUAD_STRIP);
	glColor3f(convertRGB(colore.red),convertRGB(colore.green),convertRGB(colore.blue));
	glVertex2d(0.0, 2.0);
	glVertex2d(0.0, 3.0);
	glVertex2d(1.0, 2.0);
	glVertex2d(1.0, 3.0);
	glVertex2d(1.0, 2.0);
	glVertex2d(1.0, 4.0);
	glVertex2d(2.0, 2.0);
	glVertex2d(2.0, 4.0);
	glVertex2d(2.0, 1.0);
	glVertex2d(2.0, 5.0);
	glVertex2d(3.0, 1.0);
	glVertex2d(3.0, 5.0);
	glVertex2d(3.0, 0.0);
	glVertex2d(3.0, 6.0);
	glVertex2d(4.0, 0.0);
	glVertex2d(4.0, 6.0);
	glVertex2d(4.0, 1.0);
	glVertex2d(4.0, 6.0);
	glVertex2d(5.0, 1.0);
	glVertex2d(5.0, 6.0);
	glVertex2d(5.0, 2.0);
	glVertex2d(5.0, 7.0);
	glVertex2d(7.0, 2.0);
	glVertex2d(7.0, 7.0);
	glVertex2d(7.0, 1.0);
	glVertex2d(7.0, 7.0);
	glVertex2d(9.0, 1.0);
	glVertex2d(9.0, 7.0);
	glVertex2d(9.0, 2.0);
	glVertex2d(9.0, 7.0);
	glVertex2d(11.0, 2.0);
	glVertex2d(11.0, 7.0);
	glVertex2d(11.0, 1.0);
	glVertex2d(11.0, 6.0);
	glVertex2d(12.0, 1.0);
	glVertex2d(12.0, 6.0);
	glVertex2d(12.0, 0.0);
	glVertex2d(12.0, 6.0);
	glVertex2d(13.0, 0.0);
	glVertex2d(13.0, 6.0);
	glVertex2d(13.0, 1.0);
	glVertex2d(13.0, 5.0);
	glVertex2d(14.0, 1.0);
	glVertex2d(14.0, 5.0);
	glVertex2d(14.0, 2.0);
	glVertex2d(14.0, 4.0);
	glVertex2d(15.0, 2.0);
	glVertex2d(15.0, 4.0);
	glVertex2d(15.0, 2.0);
	glVertex2d(15.0, 3.0);
	glVertex2d(16.0, 2.0);
	glVertex2d(16.0, 3.0);
	glEnd();

	//Finestrini
	glBegin(GL_POLYGON);
	glColor3f(convertRGB(nero.red),convertRGB(nero.green),convertRGB(nero.blue));
	glVertex2d(3.0, 3.0);
	glVertex2d(3.0, 4.0);
	glVertex2d(4.0, 4.0);
	glVertex2d(4.0, 3.0);
	glVertex2d(3.0, 3.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(6.0, 3.0);
	glVertex2d(6.0, 4.0);
	glVertex2d(7.0, 4.0);
	glVertex2d(7.0, 3.0);
	glVertex2d(6.0, 3.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(9.0, 3.0);
	glVertex2d(9.0, 4.0);
	glVertex2d(10.0, 4.0);
	glVertex2d(10.0, 3.0);
	glVertex2d(9.0, 3.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(12.0, 3.0);
	glVertex2d(12.0, 4.0);
	glVertex2d(13.0, 4.0);
	glVertex2d(13.0, 3.0);
	glVertex2d(12.0, 3.0);
	glEnd();
	glPopMatrix();
}

//true = chiuse, false = aperte
void alienoGrosso(bool dimensioneGambe, Point posizione,rgbColor colore){

	glPushMatrix();
	glTranslatef(posizione.x,posizione.y,0.0);
	glScalef(scalerAlienoGrosso,scalerAlienoGrosso,0.0);

	glBegin(GL_QUAD_STRIP);
	glColor3f(convertRGB(colore.red),convertRGB(colore.green),convertRGB(colore.blue));
	glVertex2d(0.0, 3.0);
	glVertex2d(0.0, 6.0);
	glVertex2d(1.0, 3.0);
	glVertex2d(1.0, 6.0);
	glVertex2d(1.0, 3.0);
	glVertex2d(1.0, 7.0);
	glVertex2d(4.0, 3.0);
	glVertex2d(4.0, 7.0);
	glVertex2d(4.0, 3.0);
	glVertex2d(4.0, 8.0);
	glVertex2d(8.0, 3.0);
	glVertex2d(8.0, 8.0);
	glVertex2d(8.0, 3.0);
	glVertex2d(8.0, 7.0);
	glVertex2d(11.0, 3.0);
	glVertex2d(11.0, 7.0);
	glVertex2d(11.0, 3.0);
	glVertex2d(11.0, 6.0);
	glVertex2d(12.0, 3.0);
	glVertex2d(12.0, 6.0);
	glEnd();

	//Occhi Alieno
	glBegin(GL_POLYGON);
	glColor3f(convertRGB(nero.red),convertRGB(nero.green),convertRGB(nero.blue));
	glVertex2d(3.0, 4.0);
	glVertex2d(3.0, 5.0);
	glVertex2d(5.0, 5.0);
	glVertex2d(5.0, 4.0);
	glVertex2d(3.0, 4.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(7.0, 4.0);
	glVertex2d(7.0, 5.0);
	glVertex2d(9.0, 5.0);
	glVertex2d(9.0, 4.0);
	glVertex2d(7.0, 4.0);
	glEnd();

	if (dimensioneGambe){
		gambeGrosseChiuse(colore);
	}else{
		gambeGrosseAperte(colore);
	}
	glPopMatrix();
}

//true = chiuse, false = aperte
void alienoPiccolo(bool dimensioneGambe, Point posizione,rgbColor colore){

	glPushMatrix();
	glTranslatef(posizione.x,posizione.y,0.0);
	glScalef(scalerAlienoPiccolo,scalerAlienoPiccolo,0.0);

	glBegin(GL_QUAD_STRIP);
	glColor3f(convertRGB(colore.red),convertRGB(colore.green),convertRGB(colore.blue));
	glVertex2d(0.0, 3.0);
	glVertex2d(0.0, 5.0);
	glVertex2d(1.0, 3.0);
	glVertex2d(1.0, 5.0);
	glVertex2d(1.0, 3.0);
	glVertex2d(1.0, 6.0);
	glVertex2d(2.0, 3.0);
	glVertex2d(2.0, 6.0);
	glVertex2d(2.0, 3.0);
	glVertex2d(2.0, 7.0);
	glVertex2d(3.0, 3.0);
	glVertex2d(3.0, 7.0);
	glVertex2d(3.0, 3.0);
	glVertex2d(3.0, 8.0);
	glVertex2d(5.0, 3.0);
	glVertex2d(5.0, 8.0);
	glVertex2d(5.0, 3.0);
	glVertex2d(5.0, 7.0);
	glVertex2d(6.0, 3.0);
	glVertex2d(6.0, 7.0);
	glVertex2d(6.0, 3.0);
	glVertex2d(6.0, 6.0);
	glVertex2d(7.0, 3.0);
	glVertex2d(7.0, 6.0);
	glVertex2d(7.0, 3.0);
	glVertex2d(7.0, 5.0);
	glVertex2d(8.0, 3.0);
	glVertex2d(8.0, 5.0);
	glEnd();

	//Occhi Alieno
	glBegin(GL_POLYGON);
	glColor3f(convertRGB(nero.red),convertRGB(nero.green),convertRGB(nero.blue));
	glVertex2d(2.0, 4.0);
	glVertex2d(2.0, 5.0);
	glVertex2d(3.0, 5.0);
	glVertex2d(3.0, 4.0);
	glVertex2d(2.0, 4.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(5.0, 4.0);
	glVertex2d(5.0, 5.0);
	glVertex2d(6.0, 5.0);
	glVertex2d(6.0, 4.0);
	glVertex2d(5.0, 4.0);
	glEnd();

	if (dimensioneGambe){
		gambePiccoleChiuse(colore);
	}else{
		gambePiccoleAperte(colore);
	}
	glPopMatrix();

}

void alienoChela(Point posizione,rgbColor colore){

	glPushMatrix();
	glTranslatef(posizione.x,posizione.y,0.0);
	glScalef(scalerAlienoChela,scalerAlienoChela,0.0);

	glBegin(GL_QUAD_STRIP);
	glColor3f(convertRGB(colore.red),convertRGB(colore.green),convertRGB(colore.blue));

	glVertex2d(0.0, 1.0);
	glVertex2d(0.0, 4.0);
	glVertex2d(1.0, 1.0);
	glVertex2d(1.0, 4.0);
	glVertex2d(1.0, 3.0);
	glVertex2d(1.0, 4.0);
	glVertex2d(1.0, 3.0);
	glVertex2d(1.0, 5.0);
	glVertex2d(2.0, 3.0);
	glVertex2d(2.0, 5.0);
	glVertex2d(2.0, 1.0);
	glVertex2d(2.0, 6.0);
	glVertex2d(3.0, 1.0);
	glVertex2d(3.0, 6.0);
	glVertex2d(3.0, 2.0);
	glVertex2d(3.0, 7.0);
	glVertex2d(4.0, 2.0);
	glVertex2d(4.0, 7.0);
	glVertex2d(4.0, 2.0);
	glVertex2d(4.0, 6.0);
	glVertex2d(7.0, 2.0);
	glVertex2d(7.0, 6.0);
	glVertex2d(7.0, 2.0);
	glVertex2d(7.0, 7.0);
	glVertex2d(8.0, 2.0);
	glVertex2d(8.0, 7.0);
	glVertex2d(8.0, 1.0);
	glVertex2d(8.0, 6.0);
	glVertex2d(9.0, 1.0);
	glVertex2d(9.0, 6.0);
	glVertex2d(9.0, 3.0);
	glVertex2d(9.0, 5.0);
	glVertex2d(10.0, 3.0);
	glVertex2d(10.0, 5.0);
	glVertex2d(10.0, 1.0);
	glVertex2d(10.0, 3.0);
	glVertex2d(11.0, 1.0);
	glVertex2d(11.0, 3.0);
	glEnd();

	//Antenna Sinistra
	glBegin(GL_POLYGON);
	glVertex2d(2.0, 7.0);
	glVertex2d(2.0, 8.0);
	glVertex2d(3.0, 8.0);
	glVertex2d(3.0, 7.0);
	glVertex2d(2.0, 7.0);
	glEnd();

	//Antenna Destra
	glBegin(GL_POLYGON);
	glVertex2d(8.0, 7.0);
	glVertex2d(8.0, 8.0);
	glVertex2d(9.0, 8.0);
	glVertex2d(9.0, 7.0);
	glVertex2d(8.0, 7.0);
	glEnd();

	//Chela Sinistra
	glBegin(GL_POLYGON);
	glVertex2d(3.0, 0.0);
	glVertex2d(3.0, 1.0);
	glVertex2d(5.0, 1.0);
	glVertex2d(5.0, 0.0);
	glVertex2d(3.0, 0.0);
	glEnd();

	//Chela Destra
	glBegin(GL_POLYGON);
	glVertex2d(6.0, 0.0);
	glVertex2d(6.0, 1.0);
	glVertex2d(8.0, 1.0);
	glVertex2d(8.0, 0.0);
	glVertex2d(6.0, 0.0);
	glEnd();

	//Occhi Alieno
	glBegin(GL_POLYGON);
	glColor3f(convertRGB(nero.red),convertRGB(nero.green),convertRGB(nero.blue));
	glVertex2d(3.0, 4.0);
	glVertex2d(3.0, 5.0);
	glVertex2d(4.0, 5.0);
	glVertex2d(4.0, 4.0);
	glVertex2d(3.0, 4.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(7.0, 4.0);
	glVertex2d(7.0, 5.0);
	glVertex2d(8.0, 5.0);
	glVertex2d(8.0, 4.0);
	glVertex2d(7.0, 4.0);
	glEnd();
	glPopMatrix();

}

void gruppoAlieni(){
	if (!disposizioneAlieni.empty()){
		for (int i = 0; i < disposizioneAlieni.size(); i++){
			switch (disposizioneAlieni[i].nomeAlieno)
			{
			case nomeAlienoPiccolo:
				if (disposizioneAlieni[i].colpito){
					if (disposizioneAlieni[i].timerEsplosione >= 0){
						esplosione(disposizioneAlieni[i].posizione,disposizioneAlieni[i].nomeAlieno);
					}else{
						disposizioneAlieni.erase(disposizioneAlieni.begin() + i);
					}
				}else{
					alienoPiccolo(disposizioneAlieni[i].alienoSpecifico,disposizioneAlieni[i].posizione,disposizioneAlieni[i].colore);
				}
				break;

			case nomeAlienoGrosso:
				if (disposizioneAlieni[i].colpito){
					if (disposizioneAlieni[i].timerEsplosione >= 0){
						esplosione(disposizioneAlieni[i].posizione,disposizioneAlieni[i].nomeAlieno);
					}else{
						disposizioneAlieni.erase(disposizioneAlieni.begin() + i);
					}
				}else{
					alienoGrosso(disposizioneAlieni[i].alienoSpecifico,disposizioneAlieni[i].posizione,disposizioneAlieni[i].colore);
				}
				break;

			case nomeAlienoChela:
				if (disposizioneAlieni[i].colpito){
					if (disposizioneAlieni[i].timerEsplosione >= 0){
						esplosione(disposizioneAlieni[i].posizione,disposizioneAlieni[i].nomeAlieno);
					}else{
						disposizioneAlieni.erase(disposizioneAlieni.begin() + i);
					}
				}else{
					alienoChela(disposizioneAlieni[i].posizione,disposizioneAlieni[i].colore);
				}
				break;
			}
		}
	}else{
		finishGame = true;
		vittoria = true;
	}
	if (navicellaAlienaMadre.timerEsplosione >= 0){
		if (navicellaAlienaMadre.colpito){
			esplosione(navicellaAlienaMadre.posizione,navicellaAlienaMadre.nomeAlieno);
		}else{
			astronaveMadreAliena(navicellaAlienaMadre.posizione,navicellaAlienaMadre.colore);
		}
	}
}

void creaNuovoMissile(){

	Point posizionePartenza = {posizioneNavicellaGioco.x + larghMissCentrLatoDestraNavicella, posizioneNavicellaGioco.y + altMissCentrBaseNavetta};
	DatiMissile nuovoMissileCentrale = {posizionePartenza,nomeArmaCentrale};
	posizioniMissili.push_back(nuovoMissileCentrale);

	if (punteggio > 400 && timerPotenziamentoMissili >= 0){
		posizionePartenza.x = posizioneNavicellaGioco.x + larghMissDestrLatoDestraNavicella;
		posizionePartenza.y = posizioneNavicellaGioco.y + altMissSinDesBaseNavicella;
		DatiMissile nuovoMissileDestro = {posizionePartenza,nomeArmaDestra};
		posizionePartenza.x = posizioneNavicellaGioco.x + 0;
		DatiMissile nuovoMissileSinistro = {posizionePartenza,nomeArmaSinistra};
		posizioniMissili.push_back(nuovoMissileDestro);
		posizioniMissili.push_back(nuovoMissileSinistro);
	}
	if (sound){
		PlaySound(TEXT("SpaceShipShoot.wav"), NULL, SND_ASYNC|SND_FILENAME|NULL);
	}

}

void nuovoMissileAlieno(){
	int alieno = 0;
	bool presente = true;
	while (presente)
	{
		alieno = random(disposizioneAlieni.size());
		presente = disposizioneAlieni[alieno].colpito;
	}
	Point posizioneAlieno = disposizioneAlieni[alieno].posizione;
	char tipologiaAlieno = disposizioneAlieni[alieno].nomeAlieno;
	DatiMissile nuovoMissileAlieno = {posizioneAlieno,missileAlieno};
	posizioniMissiliAlieni.push_back(nuovoMissileAlieno);
	if (sound){
		PlaySound(TEXT("InvaderShot.wav"), NULL, SND_ASYNC|SND_FILENAME|NULL);
	}
}

bool controlloContatti(DatiMissile missile, Point posizioneBersaglio, char tipologiaBersaglio){

	bool risultato = false;
	int altezzaMissile = 0;

	switch (missile.nomeArma)
	{ 
	case nomeArmaCentrale:
		altezzaMissile = altezzaMissileCentrale;
		break;
	case nomeArmaDestra:
		altezzaMissile = altezzaMissiliDestraSinistra;
		break;
	case nomeArmaSinistra:
		altezzaMissile = altezzaMissiliDestraSinistra;
		break;
	case missileAlieno:
		altezzaMissile = altezzaMissileAlieno;
		break;
	}

	switch (tipologiaBersaglio){
	case nomeNavicella:
		if (missile.posizione.x + larghezzaMissileAlieno -1 >= posizioneBersaglio.x && missile.posizione.x + 1 <= posizioneBersaglio.x + larghezzaNavicella){
			if (missile.posizione.y + altezzaMissile -1 >= posizioneBersaglio.y && missile.posizione.y +1 <= posizioneBersaglio.y + altezzaNavicella){
				risultato = true;
			}
		}
		break;

	case nomeAstronaveMadreAliena:
		if (missile.posizione.x + larghezzaMissili -1 >= posizioneBersaglio.x && missile.posizione.x + 1 <= posizioneBersaglio.x + larghezzaAstronaveMadre){
			if (missile.posizione.y + altezzaMissile -1 >= posizioneBersaglio.y && missile.posizione.y +1 <= posizioneBersaglio.y + altezzaAstronaveMadre){
				risultato = true;
			}
		}
		break;

	case nomeAlienoPiccolo:
		if (missile.posizione.x  + larghezzaMissili -1 >= posizioneBersaglio.x && missile.posizione.x + 1 <= posizioneBersaglio.x + larghezzaAlienoPiccolo){
			if (missile.posizione.y + altezzaMissile -1 >= posizioneBersaglio.y && missile.posizione.y +1 <= posizioneBersaglio.y + altezzaAlienoPiccolo){
				risultato = true;
			}
		}
		break;

	case nomeAlienoGrosso:
		if (missile.posizione.x + larghezzaMissili -1 >= posizioneBersaglio.x && missile.posizione.x  + 1 <= posizioneBersaglio.x + larghezzaAlienoGrosso){
			if (missile.posizione.y + altezzaMissile -1 >= posizioneBersaglio.y && missile.posizione.y +1 <= posizioneBersaglio.y + altezzaAlienoGrosso){
				risultato = true;
			}
		}
		break;

	case nomeAlienoChela:
		if (missile.posizione.x + larghezzaMissili -1 >= posizioneBersaglio.x && missile.posizione.x  + 1 <= posizioneBersaglio.x + larghezzaAlienoChela){
			if (missile.posizione.y + altezzaMissile -1 >= posizioneBersaglio.y && missile.posizione.y +1 <= posizioneBersaglio.y + altezzaAlienoChela){
				risultato = true;
			}
		}
		break;
	}
	return risultato;
}

void gruppoMissili(){

	if (!posizioniMissiliAlieni.empty()){
		for (int i = 0; i < posizioniMissiliAlieni.size(); i++){
			missile(posizioniMissiliAlieni[i]);
			if (controlloContatti(posizioniMissiliAlieni[i],posizioneNavicellaGioco, nomeNavicella)){
				viteNavicella--;
				posizioniMissiliAlieni.erase(posizioniMissiliAlieni.begin() + i);
				if (sound){
					PlaySound(TEXT("SpaceShipExplosion.wav"), NULL, SND_ASYNC|SND_FILENAME|NULL);
				}
			}
		}

	}
	if (!posizioniMissili.empty()){
		for (int i = 0; i < posizioniMissili.size(); i++ ) {
			missile(posizioniMissili[i]);
			if (!disposizioneAlieni.empty()){
				for (int t = 0, lenAlieni = disposizioneAlieni.size(); t < lenAlieni; t++){
					if (!disposizioneAlieni[t].colpito){
						if (controlloContatti(posizioniMissili[i],disposizioneAlieni[t].posizione, disposizioneAlieni[t].nomeAlieno)){
							switch (disposizioneAlieni[t].nomeAlieno)
							{
							case nomeAlienoPiccolo:
								punteggio += 10;
								break;

							case nomeAlienoGrosso:
								punteggio += 20;
								break;

							case nomeAlienoChela:

								punteggio += 15;
								break;
							}
							disposizioneAlieni[t].colpito = true;
							posizioniMissili.erase(posizioniMissili.begin() + i);
							if (sound){
								PlaySound(TEXT("InvaderKilled.wav"), NULL, SND_ASYNC|SND_FILENAME|NULL);
							}
							break;
						}
					}
				}
			}
		}
		if (!posizioniMissili.empty()){
		for (int i = 0; i < posizioniMissili.size(); i++ ) {
			if (!navicellaAlienaMadre.colpito){
				if (controlloContatti(posizioniMissili[i],navicellaAlienaMadre.posizione, navicellaAlienaMadre.nomeAlieno)){
					punteggio += 100;
					navicellaAlienaMadre.colpito = true;
					posizioniMissili.erase(posizioniMissili.begin() + i);
					if (sound){
						PlaySound(TEXT("InvaderKilled.wav"), NULL, SND_ASYNC|SND_FILENAME|NULL);
					}
				}
			}
		}
	}
	}
	
}

void infoGioco(){

	disegnaTestoBitmap(larghezzaDisplay - larghezzaPunteggio, altezzaDisplay - altezzaCoins_Punteggio,"SCORE",verde);
	disegnaTestoBitmap(larghezzaDisplay - larghezzaPunteggio + 75, altezzaDisplay - altezzaCoins_Punteggio,int2str(punteggio),bianco);
	disegnaTestoBitmap(0.0, altezzaDisplay - (altezzaNavicella/scalerNavicella),"LIVES",verde);
	if (viteNavicella > 0){
		for (int i = 0; i < viteNavicella; i++){
			navicella(posizioneVite,scalerViteNavicella);
			posizioneVite.x += larghezzaNavicella/scalerNavicella + 10;
		}
	}else{
		finishGame = true;
		vittoria = false;
	}
	posizioneVite.x = 70.0;
	navicella(posizioneNavicellaGioco,scalerNavicella);
	if (pauseGame){
		disegnaTestoBitmap(larghezzaDisplay/2 - larghezzaPausa/2, altezzaDisplay/2,"PAUSE",verde);
	}
	if (sound){
		disegnaTestoBitmap(larghezzaDisplay - larghezzaSounds, 0 ,"SOUNDS ENABLED",verde);
	}else{
		disegnaTestoBitmap(larghezzaDisplay - larghezzaSounds, 0,"SOUNDS DISABLED",rosso);
	}
}

void presentazione(){

	if (inizioIntro && sound){
		PlaySound(TEXT("Intro.wav"), NULL, SND_ASYNC|SND_FILENAME|NULL);
		inizioIntro = !inizioIntro;
	}

	if (timerGlobalePresentazione >= timerAvvioStelle){
		srand(time(NULL)); // questa funzione rallenta l'uscita delle stelle e rende efficace la random
		for (int i = 0; i < numeroStelle; i++){
			stella();
		}
	}
	if (timerGlobalePresentazione >= timerAvvioTitolo){
		disegnaTestoStroke(larghezzaDisplay/2 - larghezzaTitolo/2,puntoPartenzaTitolo,"SPACE INVADERS",bianco);
	}

	if (timerGlobalePresentazione >= timerAvvioIstruzioni){
		istruzioni();
	}

	if (timerGlobalePresentazione >= timerAvvioNavicella){
		navicella(posizioneNavicellaPresentazione,scalerNavicella);
	}

	if (!esplosioniAlieniPresentazione){
		if (timerGlobalePresentazione >= timerAvvioAstronaveMadre){
			astronaveMadreAliena(posizioneAstronaveMadrePresentazione,rosso);
		}

		if (timerGlobalePresentazione >= timerAlieno1){
			alienoGrosso(false,posizioneAlieno1Presentazione,verde);
		}

		if (timerGlobalePresentazione >= timerAlieno2){
			alienoChela(posizioneAlieno2Presentazione,blu);
		}

		if (timerGlobalePresentazione >= timerSparoMissile){
			missile(missilePresentazione);
			esplosioniAlieniPresentazione = controlloContatti(missilePresentazione,posizioneAstronaveMadrePresentazione,nomeAstronaveMadreAliena);
		}
	}else{
		if (timerGlobalePresentazione <= timerEsplosioniPresentazione){
			esplosione(posizioneAstronaveMadrePresentazione,nomeAstronaveMadreAliena);
			esplosione(posizioneAlieno1Presentazione,nomeAlienoGrosso);
			esplosione(posizioneAlieno2Presentazione,nomeAlienoChela);
		}
		if (tempoLampeggioCoins < lampeggioCoins){
			disegnaTestoBitmap(larghezzaDisplay - larghezzaCoins, altezzaDisplay - altezzaCoins_Punteggio,"INSERT COINS : " + int2str(numeroMonete),bianco);
		}else{
			disegnaTestoBitmap(larghezzaDisplay/2 - larghezzaInfo/2, bordoInferioreInfo ,"INSERT A COIN AND PRESS ENTER TO START THE GAME",bianco);
		}
	}
}

void gioco(){

	if (!inizioIntro){
		PlaySound(NULL, 0, 0);
		inizioIntro = !inizioIntro;
	}
	gruppoAlieni();
	gruppoMissili();
	infoGioco();
}

void giocoFinito(){

	disegnaTestoBitmap(larghezzaDisplay - larghezzaPunteggio, altezzaDisplay - altezzaCoins_Punteggio,"SCORE",verde);
	disegnaTestoBitmap(larghezzaDisplay - larghezzaPunteggio + 75, altezzaDisplay - altezzaCoins_Punteggio,int2str(punteggio),bianco);
	disegnaTestoBitmap(0.0, altezzaDisplay - (altezzaNavicella/scalerNavicella),"LIVES",verde);
	if (viteNavicella > 0){
		for (int i = 0; i < viteNavicella; i++){
			navicella(posizioneVite,scalerViteNavicella);
			posizioneVite.x += larghezzaNavicella/scalerNavicella + 10;
		}
	}
	posizioneVite.x = 70.0;
	if (timerInfoFineGioco < 0){
		disegnaTestoBitmap(larghezzaDisplay/2 - larghezzaInfoFineGioco/2, altezzaDisplay/5,"PRESS ESC TO EXIT OR ENTER TO RESTART THE GAME", bianco);
	}
	if (vittoria){
		disegnaTestoStroke(larghezzaDisplay/2 - larghezzaYouWon/2,altezzaDisplay/2,"YOU WON",verde);
	}else{
		disegnaTestoStroke(larghezzaDisplay/2 - larghezzaGameOver/2,altezzaDisplay/2,"GAME OVER",rosso);
	}

}

void idle(){
	calcolaFPS(); //calcola i Frames per secondo ed in caso di un idle pi˘ veloce rallenta l'esecuzione del gioco
	if (riposoIdle != 0){
		Sleep(riposoIdle);
	}
	if (!pauseGame){
		if (startGame && !finishGame){
			if (punteggio > 400){
				timerPotenziamentoMissili--;
			}
			//aggiornamento posizione missili alieni
			if (!posizioniMissiliAlieni.empty()){
				for (int i = 0; i < posizioniMissiliAlieni.size(); i++ ) {
					if (posizioniMissiliAlieni[i].posizione.y + altezzaMissileAlieno < 0){
						posizioniMissiliAlieni.erase(posizioniMissiliAlieni.begin() + i);
					}else{
						posizioniMissiliAlieni[i].posizione.y -= spostamentoCostanteMissili;
					}
				}
			}
			tempoBaseAttesaMissile--;
			//aggiornamento posizione missili navicella
			if (!posizioniMissili.empty()){
				for (int i = 0; i < posizioniMissili.size(); i++ ) {
					if (posizioniMissili[i].posizione.y > altezzaDisplay){
						posizioniMissili.erase(posizioniMissili.begin() + i);
					}else{
						posizioniMissili[i].posizione.y += spostamentoCostanteMissili;
					}
				}
			}
			if (contatoreFrecciaDestra != 0){
				if (posizioneNavicellaGioco.x - contatoreFrecciaSinistra > larghezzaDisplay - larghezzaNavicella){
					posizioneNavicellaGioco.x = larghezzaDisplay - larghezzaNavicella;
					contatoreFrecciaDestra = 0;
				}else{
					posizioneNavicellaGioco.x += contatoreFrecciaDestra;
				}
			}
			if (contatoreFrecciaSinistra != 0){
				if (posizioneNavicellaGioco.x - contatoreFrecciaSinistra < 0){
					posizioneNavicellaGioco.x = 0;
					contatoreFrecciaSinistra = 0;
				}else{
					posizioneNavicellaGioco.x -= contatoreFrecciaSinistra;
				}
			}
			if (!disposizioneAlieni.empty()){
				timerMissiliAlieni--;
				timerIncrementoGruppo--;
				timerDiscesaGruppo--;
				if (timerIncrementoGruppo < 0){
					moltiplicatoreVelocit‡Gruppo++;
					timerIncrementoGruppo = 600;
				}
				if (timerDiscesaGruppo < 0){
					moltiplicatoreDiscesaGruppo++;
					valoreDiscesa = 5;
					timerDiscesaGruppo = 350;
				}
				if (movimentoGruppo){
					incrementoMovimentoGruppo = 2* moltiplicatoreVelocit‡Gruppo;
				}else{
					incrementoMovimentoGruppo = -2 * moltiplicatoreVelocit‡Gruppo;
				}
				//aggiornamento posizione gruppo alieni
					for (int i = 0; i < disposizioneAlieni.size(); i++){
						if (!disposizioneAlieni[i].colpito){
							if (disposizioneAlieni[i].posizione.x + incrementoMovimentoGruppo + larghezzaAlienoGrosso > larghezzaDisplay){
								movimentoGruppo = false;
							}else if (disposizioneAlieni[i].posizione.x + incrementoMovimentoGruppo < 0){
								movimentoGruppo = true;
							}
							disposizioneAlieni[i].posizione.x += incrementoMovimentoGruppo;
							disposizioneAlieni[i].posizione.y -= valoreDiscesa*moltiplicatoreDiscesaGruppo;
							if (disposizioneAlieni[i].posizione.y <= altezzaLineaInvasione){
								finishGame = true;
								vittoria = false;
							}
						}else{
							disposizioneAlieni[i].timerEsplosione--;
						}
					}
				valoreDiscesa = 0;
				if (timerMissiliAlieni < 0 && !disposizioneAlieni.empty()){
					nuovoMissileAlieno();
					timerMissiliAlieni = 120;
				}
				if (!navicellaAlienaMadre.colpito){
					if (navicellaAlienaMadre.posizione.x == -larghezzaAstronaveMadre){
						PlaySound(TEXT("InvaderCommandShip.wav"), NULL, SND_ASYNC|SND_FILENAME|NULL);
					}
					navicellaAlienaMadre.posizione.x += 3;
				}else{
					navicellaAlienaMadre.timerEsplosione--;
				}
			}
		}else if (finishGame){
			timerInfoFineGioco--;
			if (timerInfoFineGioco == -30){
				timerInfoFineGioco = 30;
			}
		}else{
			timerGlobalePresentazione++;
			if (timerGlobalePresentazione >= timerAvvioTitolo){
				if (puntoPartenzaTitolo + altezzaTitolo + bordoSuperioreTitolo != altezzaDisplay){
					puntoPartenzaTitolo--;
				}
			}
			if (timerGlobalePresentazione >= timerAvvioIstruzioni){
				if (puntoPartenzaIstruzioni >= bordoSinistroIstruzioni){
					puntoPartenzaIstruzioni -= 2;
				}
			}
			if (timerGlobalePresentazione >= timerAvvioAstronaveMadre){
				if (posizioneAstronaveMadrePresentazione.x <= bordoSinistroAstronaveMadre){
					posizioneAstronaveMadrePresentazione.x++;
				}
			}
			if (timerGlobalePresentazione >= timerAvvioNavicella){
				if (posizioneNavicellaPresentazione.y <= bordoInfSupDisplay){
					posizioneNavicellaPresentazione.y++;
				}
			}
			if (timerGlobalePresentazione >= timerSparoMissile && !esplosioniAlieniPresentazione){
				missilePresentazione.posizione.y += 1.5;	
			}
			if (tempoLampeggioCoins > lampeggioCoins*2){ //lampeggioCoins*2 - lampeggioCoins = periodo di visualizzazione della scritta INSERT COINS: 
				tempoLampeggioCoins = 0;
			}else {
				tempoLampeggioCoins++;
			}
		}
	}
	glutPostRedisplay();
	glutSetWindow(windowsID);
}

void tasti_speciali(int key, int x, int y){
	if (!pauseGame){
		switch (key)
		{
		case GLUT_KEY_LEFT : //freccia sinistra
			if (startGame){
				if (contatoreFrecciaDestra != 0){
					contatoreFrecciaDestra = 0;
				}else{
					contatoreFrecciaSinistra++;
				}
			}
			break;
		case GLUT_KEY_RIGHT : //freccia destra
			if (startGame){
				if (contatoreFrecciaSinistra != 0){
					contatoreFrecciaSinistra = 0;
				}else{
					contatoreFrecciaDestra++;
				}
			}
			break;
		default:
			break;
		}
	}
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
	case 27: // Esc
		glutDestroyWindow ( windowsID );
		exit (0);
		break;
	case 13 : //enter
		if (!pauseGame){
			if (finishGame){
				inizializzazioneVariabili();
				startGame = true;
			}
			else if (!startGame && numeroMonete == 1){
				startGame = !startGame;
			}
		}
		break;
	case 'p': //pausa
		if (startGame && !finishGame){
			pauseGame = !pauseGame;
		}
		break;
	case 's': //disabilita/abilita i suoni
		if (!pauseGame){
			PlaySound(NULL, 0, 0);
			sound = !sound;
		}
		break;
	case 'c': //inserimento moneta
		if (!startGame){
			if (numeroMonete == 0){
				numeroMonete++;
			}
		}
		break;
	case 32 : //barra spaziatrice
		if (!pauseGame){
			if (startGame){
				if (tempoBaseAttesaMissile <= 0){
					creaNuovoMissile();
					//tempo di attesa prima che sia possibile sparare un nuovo missile
					tempoBaseAttesaMissile = tempoAttesaNuovoMissile;
				}
			}
		}
		break;
	}
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	disegnaTestoBitmap(0.0, 0.0, "FPS: " + to_string(fps),bianco);
	if (!startGame){
		presentazione();
	}else if (finishGame){
		giocoFinito();
	}else{
		gioco();
	}
	glutSwapBuffers();
}

void init(void){
	glClearColor(convertRGB(nero.red),convertRGB(nero.green),convertRGB(nero.blue),0.0);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluOrtho2D(0.0,float(larghezzaDisplay),0.0,float(altezzaDisplay));
}

void main(int argc, char** argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
	altezzaDisplay = glutGet(GLUT_SCREEN_HEIGHT);
	larghezzaDisplay = glutGet(GLUT_SCREEN_WIDTH);
	glutInitWindowSize(larghezzaDisplay,altezzaDisplay);

	inizializzazioneVariabili();

	glutInitWindowPosition(0,0);
	windowsID = glutCreateWindow("Space Invaders");
	glutFullScreen();

	//per impostare l'icona nella finestra principale
	HWND hwnd = FindWindow(NULL, _T("Space Invaders") );
	HANDLE icon = LoadImage(GetModuleHandle(NULL), _T("icon.ico"), IMAGE_ICON, 64, 64, LR_LOADFROMFILE | LR_COLOR);
	SendMessage(hwnd, (UINT)WM_SETICON, ICON_BIG, (LPARAM)icon);

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(tasti_speciali);
	init();
	glutMainLoop();
}