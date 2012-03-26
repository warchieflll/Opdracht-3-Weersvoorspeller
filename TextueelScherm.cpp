/*
 * TextueelScherm.cpp
 *
 *  Created on: 11 mrt. 2012
 *      Author: acer
 */

#include "TextueelScherm.hpp"

TextueelScherm::TextueelScherm( WeerData* weerData )
{
	//sla schermgrootte op in globale variabelen
	MAExtent screenSize = maGetScrSize();
	int screenWidth = EXTENT_X( screenSize );
	int screenHeight = EXTENT_Y( screenSize );

	//sla de weerdata op in het attribuut
	this->weerData = weerData;

	//ken font en skin toe
	this->font = new MAUI::Font(RES_FONT);
	skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false );

	//maak een achtergrond label om alle andere widgets in op te slaan, en te tonen
	Label* achtergrond = new Label(0,0,0,0,NULL);
	achtergrond->setBackgroundColor(0x000000);

	//maak een listbox waar update en visueelknop aan toegevoegd worden
//	this->listBox = ...

	//knop om data te updaten
	this->updateKnop = new Label ( screenWidth/2-50, 250, 80, 30, achtergrond, "Update", 0, font );
	this->updateKnop->setSkin( this->skin );
	this->updateKnop->setPaddingLeft(5);
	this->updateKnop->setPaddingTop(5);

	//knop om naar visueel scherm te schakelen
	this->visueelKnop = new Label ( screenWidth/2-50, 285, 80, 30, achtergrond, "Visueel", 0, font );
	this->visueelKnop->setSkin( this->skin );
	this->visueelKnop->setPaddingLeft(5);
	this->visueelKnop->setPaddingTop(5);

	//label veld voor weer data, beslaat de rest van het scherm (zie onder)
	this->weerDataLabel = new Label (20, 20, screenWidth-40, screenHeight/2+60, achtergrond, "DataLabel", 0, font);
	weerDataLabel->setBackgroundColor(0xff0000);

	//info label
	this->weerInfo = new Label (screenWidth/2-50, 50, 80, 30, achtergrond, "Info", 0, font);

	//zonneschijn label
	this->weerInfoZon = new Label (screenWidth/2-50, 90, 80, 30, achtergrond, "Zon", 0, font);

	//neerslag label
	this->weerInfoNeerslag = new Label (screenWidth/2-50, 130, 80, 30, achtergrond, "Neerslag", 0, font);

	//minimum temperatuur label
	this->weerInfoMintemp = new Label (screenWidth/2-50, 170, 80, 30, achtergrond, "Temp", 0, font);

	//update labels met text, etc.
	this->update();

	//stel achtergrond label in als main widget, en maakt alles zichtbaar
	this->setMain(achtergrond);
}

TextueelScherm::~TextueelScherm()
{
}



void TextueelScherm::toonWeerData()
{
	//tijdelijke data buffer voor sprintf operaties
	char data[500];

	printf(data, weerData);
	//stel tekst in voor info label
//	this->weerInfo->???

	//stel tekst in voor zonneschijn label
//	sprintf( data, "Zonneschijn: %i%%	/ %i%% / %i%%", ???, ???, ??? );
//	this->weerInfoZon->setCaption( data );

	//stel tekst in voor neerslag label
//	sprintf( data, ??? );
//	...

	//stel tekst in voor minimum temperatuur label
//	sprintf( data, ??? );
//	...
}


void TextueelScherm::setToggleScherm( Screen* toggleScherm )
{
	//switch naar andere scherm (visueel scherm)
	this->toggleScherm = toggleScherm;
}



void TextueelScherm::update()
{
	//update weerdata en geef alles weer (update labels met nieuwe data)
	this->weerData->update();
	this->toonWeerData();
}



void TextueelScherm::pointerPressEvent( MAPoint2d maPoint )
{
	Point point;
	point.x = maPoint.x;
	point.y = maPoint.y;

	//update knop is ingedrukt
	if( this->updateKnop->contains( point ) )
	{
		this->updateKnop->setSelected( true );
	}
	else
	{
		this->updateKnop->setSelected( false );
	}


	//visueel knop is ingedrukt
	if( this->visueelKnop->contains( point ) )
	{
		this->visueelKnop->setSelected( true );
		this->hide();
		this->toggleScherm->show();
	}
	else
	{
		this->visueelKnop->setSelected( false );
	}
}
