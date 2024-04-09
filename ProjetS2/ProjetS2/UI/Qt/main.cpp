#include "UI/Qt/DisplayGameQt.h"
#include <QtWidgets\\QApplication>
#include <QFile>
#include <QtWidgets>

#include "UI/Console/DisplayGame.hpp"
#include "Input/InputConsole.hpp"
#include "Input/InputArduino.hpp"
#include "Output/OutputArduino.hpp"
#include "Output/OutputConsole.hpp"
#include "GameDomain/FishingRun.hpp"
#include "UI/Console/DisplayMenu.hpp"

#include "Communication/ComSerialJSON.hpp"
#include "GameView.h"


int main(int argc, char* argv[])
{
	DisplayGame displayGame;
	//DisplayMenu displayMenu;
	//ComSerialJSON com;
	//com.init();
	//IInput* input = new InputArduino(&com);
	IInput* input = new InputConsole();
	IOutput* output = new OutputConsole();
	//IOutput* output = new OutputArduino(&com);
	InputGame actions;
	InputMenu menuInput;
	FishingRun fishingRun;

	QApplication a(argc, argv);
	DisplayGameQt w(input, actions, fishingRun);
	QFile file(":/styles.css");

	file.open(QFile::ReadOnly | QFile::Text);
	QString styleSheet = QLatin1String(file.readAll());
	a.setStyleSheet(styleSheet);
	w.show();
	a.exec();

	
	//for (;;) //menu
	//{
	//  displayMenu.displayCurrentMenu();
	//  menuInput = input->getMenuInput();
	//  displayMenu.processInput(menuInput, fishingRun);
	//}

	//for (;;) // In game
	//{
	//	w.refreshMove(fishingRun);

	//	if (fishingRun.getIsFinished())
	//	{
	//		//displayGame.displayMessage("Run has been finished with " + std::to_string(fishingRun.getScore()) + " total score.");
	//		//exit(0);
	//	}

	//	output->DisplayGameData(fishingRun.getCurrentSession()->getScore());
	//	displayGame.displaySession(*fishingRun.getCurrentSession());
	//	actions = input->getGameInput();

	//	if (actions.quit)
	//	{
	//		//displayGame.displayMessage("Quit");
	//		//quick_exit(0);
	//	}
	//	// Check menu
	//	fishingRun.getCurrentSession()->processInput(actions);
	//}
	//delete input;
}
