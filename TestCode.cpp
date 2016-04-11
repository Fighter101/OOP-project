#include "GUI\Input.h"
#include "GUI\Output.h"

//This is a test code to test the Input and Output classes

int main()
{
	int x,y;

	//Create Input and Output objects to test
	Output *pOut = new Output();;
	Input *pIn = pOut->CreateInput();

	//Starting the test
	pOut->PrintMsg("This demo is to test input and output classes, Click anywhere to start the test");
	pIn->GetPointClicked(x,y);	//Wait for any click


	///////////////////////////////////////////////////////////////////////////////////
	// TEST 1:	Create The FULL Tool bar, the drawing area and the status bar	
	//			This has already been done through the constrcutor of class Output
	///////////////////////////////////////////////////////////////////////////////////

	pOut->PrintMsg("TEST1: Drawing Tool bar and Status bar, Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click

	
	///////////////////////////////////////////////////////////////////////////////////
	// TEST 2:	Drawing all the Components with all possible states: Normal, highlighted
	//			
	///////////////////////////////////////////////////////////////////////////////////
	
	pOut->PrintMsg("TEST2: Now we will show that Output class can draw any Component in any state, Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click

	GraphicsInfo GfxInfo;  //to be used with draw function of the class Ouput

	/// 2.1- AND2 Gate test
	pOut->PrintMsg("Drawing 2-input AND gate, Normal and Highlighted,  Click to continue");
	
	//Drawing Normal AND2 gate
	GfxInfo.x1 = 100;	GfxInfo.y1 = 120; 
	pOut->DrawAND2(GfxInfo);
	//Drawing Highlighted AND2 gate
	GfxInfo.x1 = 180;	GfxInfo.y1 = 120;
	pOut->DrawAND2(GfxInfo, true);
	GfxInfo.x1 = 100;	GfxInfo.y1 = 180;
	pOut->DrawAND3(GfxInfo);
	GfxInfo.x1 = 180;	GfxInfo.y1 = 180;
	pOut->DrawAND3(GfxInfo, true);
	pIn->GetPointClicked(x,y);	//Wait for any click
	//pOut->ClearDrawingArea();

	/// 2.2- NAND2 Gate test
	GfxInfo.x1 = 100;	GfxInfo.y1 = 240;
	pOut->PrintMsg("Drawing 2-input NAND gate, Normal and Highlighted,  Click to continue");
	pOut->DrawNAND2(GfxInfo);
	GfxInfo.x1 = 180;	GfxInfo.y1 = 240;
	pOut->DrawNAND2(GfxInfo, true);
	GfxInfo.x1 = 100;	GfxInfo.y1 = 300;
	pOut->DrawNAND3(GfxInfo);
	GfxInfo.x1 = 180;	GfxInfo.y1 = 300;
	pOut->DrawNAND3(GfxInfo, true);
	///TODO: Add code to draw 2-input NAND gate, Normal and Highlighted
	pIn->GetPointClicked(x,y);	//Wait for any click
	//pOut->ClearDrawingArea();

	/// 2.3- OR2 and NOR2 Gates test
	pOut->PrintMsg("Drawing 2-input OR and NOR gates, Normal and Highlighted,  Click to continue");
	GfxInfo.x1 = 260;	GfxInfo.y1 = 120;
	pOut->DrawOR2(GfxInfo);
	GfxInfo.x1 = 340;	GfxInfo.y1 = 120;
	pOut->DrawOR2(GfxInfo,true);
	GfxInfo.x1 = 260;	GfxInfo.y1 = 180;
	pOut->DrawOR3(GfxInfo);
	GfxInfo.x1 = 340;	GfxInfo.y1 = 180;
	pOut->DrawOR3(GfxInfo,true);
	///TODO: Add code to draw 2-input OR and NOR gates, Normal and Highlighted for each
	GfxInfo.x1 = 260;	GfxInfo.y1 = 240;
	pOut->DrawNOR2(GfxInfo);
	GfxInfo.x1 = 260;	GfxInfo.y1 = 300;
	pOut->DrawNOR2(GfxInfo, true);
	GfxInfo.x1 = 340;	GfxInfo.y1 = 240;
	pOut->DrawNOR3(GfxInfo);
	GfxInfo.x1 = 340;	GfxInfo.y1 = 300;
	pOut->DrawNOR3(GfxInfo, true);
	pIn->GetPointClicked(x,y);	//Wait for any click
	//pOut->ClearDrawingArea();

	/// 2.4- XOR2 and XNOR2 Gates test
	pOut->PrintMsg("Drawing 2-input XOR and XNOR gates, Normal and Highlighted,  Click to continue");
	///TODO: Add code to draw 2-input XOR and XNOR gates, Normal and Highlighted for each
	GfxInfo.x1 = 420;	GfxInfo.y1 = 120;
	pOut->DrawXOR2(GfxInfo);
	GfxInfo.x1 = 500;	GfxInfo.y1 = 120;
	pOut->DrawXOR2(GfxInfo,true);
	GfxInfo.x1 = 420;	GfxInfo.y1 = 180;
	pOut->DrawXOR3(GfxInfo);
	GfxInfo.x1 = 500;	GfxInfo.y1 = 180;
	pOut->DrawXOR3(GfxInfo,true);
	///TODO: Add code to draw 2-input XOR and XNOR gates, XNORmal and Highlighted fXOR each
	GfxInfo.x1 = 420;	GfxInfo.y1 = 240;
	pOut->DrawXNOR2(GfxInfo);
	GfxInfo.x1 = 500;	GfxInfo.y1 = 240;
	pOut->DrawXNOR2(GfxInfo, true);
	GfxInfo.x1 = 420;	GfxInfo.y1 = 300;
	pOut->DrawXNOR3(GfxInfo);
	GfxInfo.x1 = 500;	GfxInfo.y1 = 300;
	pOut->DrawXNOR3(GfxInfo, true);
	pIn->GetPointClicked(x,y);	//Wait for any click
	//pOut->ClearDrawingArea();
	
	/// 2.5- Buffer and Inverter Gates test
	pOut->PrintMsg("Drawing Buffer and Inverter Gates, Normal and Highlighted,  Click to continue");
	GfxInfo.x1 = 580; GfxInfo.y1 = 120;
	pOut->DrawBuffer(GfxInfo);
	GfxInfo.x1 = 580; GfxInfo.y1 = 180;
	pOut->DrawBuffer(GfxInfo,true);
	GfxInfo.x1 = 640; GfxInfo.y1 = 120;
	pOut->DrawInverter(GfxInfo);
	GfxInfo.x1 = 640; GfxInfo.y1 = 180;
	pOut->DrawInverter(GfxInfo,true);
	///TODO: Add code to draw Buffer and Inverter Gates, Normal and Highlighted for each

	pIn->GetPointClicked(x,y);	//Wait for any click
	//pOut->ClearDrawingArea();
	GfxInfo.x1 = 580; GfxInfo.y1 = 240;
	pOut->DrawSwitch(GfxInfo);
	pIn->GetPointClicked(x, y);
	GfxInfo.x1 = 640; GfxInfo.y1 = 240;
	pOut->DrawSwitch(GfxInfo, true, false);
	GfxInfo.x1 = 580; GfxInfo.y1 = 300;
	pOut->DrawSwitch(GfxInfo, false, true);
	GfxInfo.x1 = 640; GfxInfo.y1 = 300;
	pOut->DrawSwitch(GfxInfo, true, true);
	/// 2.6- AND3, NOR3, and XOR3 Gates test
	pOut->PrintMsg("Drawing 3-input AND, NOR, XOR Gates, Normal and Highlighted,  Click to continue");
	GfxInfo.x1 = 750;	GfxInfo.y1 = 120;
	pOut->DrawLED(GfxInfo);
	GfxInfo.x1 = 750;	GfxInfo.y1 = 180;
	pOut->DrawLED(GfxInfo, true);
	GfxInfo.x1 = 830;	GfxInfo.y1 = 120;
	pOut->DrawLED(GfxInfo, false, true);
	GfxInfo.x1 = 830;	GfxInfo.y1 = 180;
	pOut->DrawLED(GfxInfo, true, true);
	pIn->GetPointClicked(x, y);	//Wait for any click
	///TODO: Add code to draw 3-input AND, NOR, and XOR Gates, Normal and Highlighted for each
	pOut->print();
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawingArea();
	pOut->connect(GraphicsInfo(100, 400, 250, 500));
	/// 2.7- Switch and LED test
	pOut->PrintMsg("Drawing Switch and LED, Normal and Highlighted,  Click to continue");
	
	///TODO: Add code to draw Switch and LED, Normal and Highlighted for each

	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawingArea();


	/// 2.8- Connections
	pOut->PrintMsg("Drawing connections, Normal, Highlighted, straight, and broken,  Click to continue");
	
	///TODO: Add code to draw connections, Normal, Highlighted, straight, and broken (all combinations) 

	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawingArea();



	


	///////////////////////////////////////////////////////////////////////////////////
	// TEST 3: Read strings from the user
	///////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMsg("TEST3: Now Time to test class Input, Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	
	pOut->PrintMsg("Testing Input ability to read strings");

	///TODO: Add code here to 
	// 1- Read a string from the user on the status bar and print it inside the drawing area


	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawingArea();

	///////////////////////////////////////////////////////////////////////////////////
	// TEST 4: Check for the user action
	///////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMsg("TEST4: Testing Input ability to detect User Action, click anywhere");

	ActionType ActType;
	
	///TODO:  You must add a case for each action
	//Add cases for the missing actions below
	do
	{
		ActType = pIn->GetUserAction();

		switch (ActType)
		{
		case ADD_Buff:
				pOut->PrintMsg("Action: add a buffer gate , Click anywhere");
				break;

		case ADD_INV:
				pOut->PrintMsg("Action: add an inverter gate , Click anywhere");
				break;

		case ADD_AND_GATE_2:
				pOut->PrintMsg("Action: add 2-input AND gate , Click anywhere");
				break;

		case ADD_NAND_GATE_2:
				pOut->PrintMsg("Action: add 2-input NAND gate , Click anywhere");
				break;

		case ADD_OR_GATE_2:
				pOut->PrintMsg("Action: add 2-input OR gate , Click anywhere");
				break;

		case ADD_NOR_GATE_2:
				pOut->PrintMsg("Action: add 2-input NOR gate , Click anywhere");
				break;

		case ADD_XOR_GATE_2:
				pOut->PrintMsg("Action: add 2-input XOR gate , Click anywhere");
				break;

		case ADD_XNOR_GATE_2:
				pOut->PrintMsg("Action: add 2-input XNOR gate , Click anywhere");
				break;

		case SELECT:
				pOut->PrintMsg("Action: a click on the Drawing area, Click anywhere");
				break;
			
		case STATUS_BAR:
				pOut->PrintMsg("Action: a click on the Status Bar, Click anywhere");
				break;
 
		case DSN_TOOL:
				pOut->PrintMsg("Action: a click on empty area in the Design Tool Bar, Click anywhere");
				break;

		case SIM_MODE:
				pOut->PrintMsg("Action: Switch to Simulation Mode, creating simualtion tool bar");
				pOut->CreateSimulationToolBar();
				break;

		case DSN_MODE:
				pOut->PrintMsg("Action: Switch to Design Mode, creating Design tool bar");
				pOut->CreateDesignToolBar();
				break;


		case EXIT:				
				break;
		}
	}while(ActType != EXIT);


	/// Exiting
	pOut->PrintMsg("Action: EXIT, test is finished, click anywhere to exit");
	pIn->GetPointClicked(x,y);

	
	delete pIn;
	delete pOut;	
	return 0;
}


