//#include "Input.h"
#include "Output.h"
#include<sstream>
#include<iostream>
#include<string>

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output* pOut)
{
	keytype ktInput;

	char cKeyData;
	string str="";

	pWind->FlushKeyQueue();
	do
	{
		pWind->FlushKeyQueue();
		ktInput = pWind->WaitKeyPress(cKeyData);
		
		// Figure out what key was pressed
		if (ktInput == ESCAPE) {
			pOut->ClearStatusBar();
			return "";
		}
		else if (ktInput == ASCII)
		{
			if (cKeyData == '\b'&&str.length() != 0)
			{
				str.erase(str.length() - 1, 1);
				pOut->PrintMsg(str);
				continue;
			}
			else
			{
				str += cKeyData;
				pOut->PrintMsg(str);
			}
		}
	} while ((int)cKeyData!=13);
	pWind->SetPen(BLACK, 3);
	pWind->DrawString(500, 500, str);
	return str;
	
}



//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction(InterfaceX UN) const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.AppMode == DESIGN)	//application is in design mode
	{
		if (y >= 0 && y <= UI.ToolBarHeight&&x >= 1.2*UI.width / 4 && x <= 1.2*UI.width / 4 + 7 * UI.ToolItemWidth && UN.ToolBar)
		{
			int ClickedItemOrder = ceil((x- 1.2*UI.width / 4.0) / UI.ToolItemWidth);
			switch (ClickedItemOrder)
			{
			case 1:
				return ADD_GATE_BAR;
				break;
			case 2:
				return ADD_CONNECTION;
				break;
			case 3:
				return UNDO;
				break;
			case 4:
				return REDO;
				break;
			case 5:
				return SAVE;
				break;
			case 6:
				return SELECT;
				break;
			case 7:
				return EXIT;
				break;
			default:
				break;
			}
		}
		else if (x >= UI.GateBarHeight&&x <= UI.width&&y >= UI.height / 4 && y <= UI.height / 4 + 7 * UI.ToolItemWidth&&UN.GateBar)
		{
			int ClickedItemOrder = ceil((y - UI.height / 4.0) / UI.ToolItemWidth);
			switch (ClickedItemOrder)
			{
			case 1:
				return ADD_AND;
				break;
			case 2:
				return ADD_OR;
				break;
			case 3:
				return ADD_XOR;
				break;
			case 4:
				return ADD_Switch;
				break;
			case 5:
				return ADD_Buff;
				break;
			case 6:
				return ADD_INV;
				break;
			case 7:
				return ADD_LED;
				break;
			default:
				break;
			}
		}
	}
	 if (x >= 0 && x <= UI.GateBarHeight&&y >= UI.height / 3 && y <= UI.height / 3 + UI.ToolItemWidth * 7)
	{
		int ClickedItemCount = ceil((y- UI.height / 3.0) / UI.ToolItemWidth);
		if (UN.AndBar)
		{
			switch (ClickedItemCount)
			{
			case 1:
				return ADD_AND_GATE_2;
				break;
			case 2:
				return ADD_AND_GATE_3;
				break;
			case 3:
				return ADD_NAND_GATE_2;
				break;
			case 4:
				return ADD_NAND_GATE_3;
				break;
			default:
				break;
			}
		}
		else if (UN.OrBar)
		{
			switch (ClickedItemCount)
			{
			case 1:
				return ADD_OR_GATE_2;
				break;
			case 2:
				return ADD_OR_GATE_3;
				break;
			case 3:
				return ADD_NOR_GATE_2;
				break;
			case 4:
				return ADD_NOR_GATE_3;
				break;
			default:
				break;
			}
		}
		else if (UN.XorBar)
		{
			switch (ClickedItemCount)
			{
			case 1:
				return ADD_XOR_GATE_2;
				break;
			case 2:
				return ADD_XOR_GATE_3;
				break;
			case 3:
				return ADD_XNOR_GATE_2;
				break;
			case 4:
				return ADD_XNOR_GATE_3;
				break;
			default:
				break;
			}
		}
	}
	 if (y >= UI.ToolBarHeight&&y <= UI.height - UI.StatusBarHeight&&x >= UI.GateBarHeight&&UI.width - UI.GateBarHeight)
	 {
		 return DRWNG_AREA;
	 }
	 if (y >= UI.height&&y <= UI.height - UI.StatusBarHeight)
		 return STATUS_BAR;
	 if (y >= UI.Margain&&y <= UI.Margain + UI.ToolBarHeight&&x >= UI.Margain&&x <= UI.Margain + UI.ToolBarHeight)
	 {
		 if (!UN.Simulation)
		 {
			 UN.Simulation = true;
			 return SIM_MODE;
		 }
		 else return DSN_MODE;
	 }
}


Input::~Input()
{
}
