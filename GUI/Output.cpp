#include "Output.h"

Output::Output()
{
	//Initialize user interface parameters

	UI.AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor = RED;
	UI.MsgColor = BLUE;
	UI.BkGrndColor = WHITE;
	
	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);	
	ChangeTitle("Programming Techniques Project");

	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar

}

Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}


//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, UI.height-UI.StatusBarHeight, UI.width, UI.height-UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	// Print the Message
    pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial"); 
	pWind->SetPen(UI.MsgColor); 
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(MsgX, UI.height - MsgY, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void Output::ClearDrawingArea() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	UI.AppMode = DESIGN;	//Design Mode

	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_AND2] = "images\\Menu\\Menu_AND2.jpg";
	MenuItemImages[ITM_OR2]  = "images\\Menu\\Menu_OR2.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Menu\\Menu_Exit.jpg";

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i],i*UI.ToolItemWidth,0,UI.ToolItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	UI.AppMode = SIMULATION;	//Simulation Mode

	//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)


}

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void Output::DrawAND(GraphicsInfo r_GfxInfo, bool selected,bool invert,bool connections) const
{
	r_GfxInfo.x2 = r_GfxInfo.x1 + 10;
	r_GfxInfo.y2 = r_GfxInfo.y1 + 20;
	r_GfxInfo.x1 -= 10;
	r_GfxInfo.y1 -= 20;
	int raduis = (r_GfxInfo.y2 - r_GfxInfo.y1) / 2;
	raduis += 9;
	pWind->SetPen(BLACK, 3);
	pWind->SetBrush(SKYBLUE);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x2 , r_GfxInfo.y1 );
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y2, r_GfxInfo.x2 , r_GfxInfo.y2 );
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x1, r_GfxInfo.y2);
	pWind->DrawArc(r_GfxInfo.x2-raduis+3, r_GfxInfo.y1-2, r_GfxInfo.x2+raduis-6, r_GfxInfo.y2+2,270,90);
	if (selected) {
		pWind->DrawArc(r_GfxInfo.x2 - raduis + 3, r_GfxInfo.y1 - 2, r_GfxInfo.x2 + raduis - 6, r_GfxInfo.y2 + 2, 270, 90, FILLED);
		pWind->SetPen(SKYBLUE);
		pWind->DrawRectangle(r_GfxInfo.x1 + 2, r_GfxInfo.y1 + 2, r_GfxInfo.x2, r_GfxInfo.y2 - 1, FILLED);
	}
	if (!invert) 
	{
		pWind->SetPen(BLACK, 3); 
		pWind->DrawLine(r_GfxInfo.x2 + raduis - 9, r_GfxInfo.y1 + raduis - 9, r_GfxInfo.x2 + raduis + 10, r_GfxInfo.y1 + raduis - 9);
	}
	if (invert)
	{
		pWind->SetPen(BLACK, 3);
		int y_Center = r_GfxInfo.y1 + raduis-9;
		int x_Center = r_GfxInfo.x2 + raduis-1;
		int Raduis = 6;
		if (selected)
			pWind->DrawCircle(x_Center - 1, y_Center, Raduis);
		else pWind->DrawCircle(x_Center - 1, y_Center, Raduis, FRAME);
		pWind->DrawLine(x_Center - 1 + Raduis, y_Center, x_Center + Raduis + 10, y_Center);
	}
	pWind->SetPen(BLACK, 3);
	if (connections)
	{
		int dist = (r_GfxInfo.y2 - r_GfxInfo.y1) / 4;
		for (size_t i = 1; i <= 3; i++)
		{
			pWind->DrawLine(r_GfxInfo.x1 - 10, (r_GfxInfo.y1 +i* dist), r_GfxInfo.x1,(r_GfxInfo.y1) +i* dist);
		}
	}
	else
	{
		int dist = (r_GfxInfo.y2 - r_GfxInfo.y1) / 3;
		for (size_t i = 1; i <= 2; i++)
		{
			pWind->DrawLine(r_GfxInfo.x1 - 10, (r_GfxInfo.y1 +i* dist), r_GfxInfo.x1, (r_GfxInfo.y1) + i*dist);
		}
	}
}

void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawAND(r_GfxInfo, selected);
}

void Output::DrawNAND2(GraphicsInfo r_GfxInfo,bool selected)
{
	DrawAND(r_GfxInfo, selected, true);
}

void Output::DrawAND3(GraphicsInfo r_GfxInfo,bool selected)
{
	DrawAND(r_GfxInfo, selected, false,true);
}

void Output::DrawNAND3(GraphicsInfo r_GfxInfo,bool selected)
{
	DrawAND(r_GfxInfo, selected, true,true);
}

void Output::DrawOr(GraphicsInfo r_GfxInfo, bool selected, bool invert, bool connections) const
{
	pWind->SetPen(BLACK, 3);
	r_GfxInfo.x2 = r_GfxInfo.x1+10;
	r_GfxInfo.y2 = r_GfxInfo.y1 + 20;
	r_GfxInfo.x1 -=10;
	r_GfxInfo.y1 -= 20;
	int ArcHeight = (r_GfxInfo.x2 - r_GfxInfo.x1)/2 ;
	int Midpoint = (r_GfxInfo.y2 - r_GfxInfo.y1)/2;
	int iHeight =(r_GfxInfo.x2 - r_GfxInfo.x1);
	if (!invert)pWind->DrawLine(r_GfxInfo.x2 + iHeight, r_GfxInfo.y1 + Midpoint, r_GfxInfo.x2 + iHeight + 10, r_GfxInfo.y1 + Midpoint);
	if (selected)
	{
		pWind->SetPen(SKYBLUE, 3);
		pWind->SetBrush(SKYBLUE);
		pWind->DrawRectangle(r_GfxInfo.x1 + ArcHeight, r_GfxInfo.y1 + 2, r_GfxInfo.x2+1, r_GfxInfo.y2 - 1, FILLED, 0, 0);
		pWind->SetPen(SKYBLUE, 3);
		pWind->SetBrush(SKYBLUE);
		pWind->DrawArc(r_GfxInfo.x1, r_GfxInfo.y1+1, r_GfxInfo.x2 + iHeight-2, r_GfxInfo.y2-1 , 270, 90,FILLED);
		pWind->SetPen(SKYBLUE, 1);
		for (int i = 0;i<=ArcHeight ; i++)
		{
			pWind->DrawArc(r_GfxInfo.x1 - ArcHeight+i, r_GfxInfo.y1, r_GfxInfo.x1 + ArcHeight+i, r_GfxInfo.y2, 270, 90);
		}
	}
	if (invert)
	{
		pWind->SetPen(BLACK, 3);
		int y_Center = r_GfxInfo.y2 - Midpoint;
		int x_Center = r_GfxInfo.x2 + iHeight + 3;
		int Raduis = 6;
		if (selected)
			pWind->DrawCircle(x_Center-1, y_Center, Raduis);
		else pWind->DrawCircle(x_Center-1, y_Center, Raduis, FRAME);
		pWind->DrawLine(x_Center-1 + Raduis, y_Center, x_Center + Raduis + 10, y_Center);
	}
	if (connections)
	{
		pWind->SetPen(BLACK, 3);
		int dist = (r_GfxInfo.y2 - r_GfxInfo.y1) / 4;
		for (size_t i = 1; i <= 3; i++)
		{
			pWind->DrawLine(r_GfxInfo.x1 - 10, r_GfxInfo.y1 + (i*dist), r_GfxInfo.x1 + ArcHeight - 1, r_GfxInfo.y1 + i*dist);

		}
	}
	else
	{
		pWind->SetPen(BLACK, 3);
		int dist = (r_GfxInfo.y2 - r_GfxInfo.y1) / 3;
		for (size_t i = 1; i < 3; i++)
		{
			pWind->DrawLine(r_GfxInfo.x1 - 10, r_GfxInfo.y1 + (i*dist), r_GfxInfo.x1 + ArcHeight - 1, r_GfxInfo.y1 + i*dist);
		}
	}
	pWind->SetPen(BLACK, 3);
	pWind->SetBrush(SKYBLUE);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x2, r_GfxInfo.y1);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y2, r_GfxInfo.x2, r_GfxInfo.y2);
	pWind->DrawArc(r_GfxInfo.x1 - ArcHeight, r_GfxInfo.y1, r_GfxInfo.x1 + ArcHeight, r_GfxInfo.y2, 270, 90);
	pWind->DrawArc(r_GfxInfo.x1, r_GfxInfo.y1 - 2, r_GfxInfo.x2 + iHeight, r_GfxInfo.y2 + 2, 270, 90);

}

void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawOr(r_GfxInfo, selected);
}

void Output::DrawOR3(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawOr(r_GfxInfo, selected, false, true);
}

void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawOr(r_GfxInfo, selected, true, false);
}

void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawOr(r_GfxInfo, selected, true, true);
}

void Output::DrawXOR(GraphicsInfo r_GfxInfo, bool selected, bool invert, bool connections) const
{
	r_GfxInfo.x2 = r_GfxInfo.x1 + 10;
	r_GfxInfo.y2 = r_GfxInfo.y1 + 20;
	r_GfxInfo.x1 -= 10;
	r_GfxInfo.y1 -= 20;
	int ArcHeight = (r_GfxInfo.x2 - r_GfxInfo.x1) / 2;
	int Midpoint = (r_GfxInfo.y2 - r_GfxInfo.y1) / 2;
	int iHeight = (r_GfxInfo.x2 - r_GfxInfo.x1);
	pWind->SetPen(BLACK, 3);
	if(!invert)pWind->DrawLine(r_GfxInfo.x2 + iHeight, r_GfxInfo.y1 + Midpoint, r_GfxInfo.x2 + iHeight + 10, r_GfxInfo.y1 + Midpoint);
	if (selected)
	{
		pWind->SetPen(SKYBLUE, 3);
		pWind->SetBrush(SKYBLUE);
		pWind->DrawRectangle(r_GfxInfo.x1 + ArcHeight, r_GfxInfo.y1 + 2, r_GfxInfo.x2 + 1, r_GfxInfo.y2 - 1, FILLED, 0, 0);
		pWind->SetPen(SKYBLUE, 3);
		pWind->SetBrush(SKYBLUE);
		pWind->DrawArc(r_GfxInfo.x1, r_GfxInfo.y1 + 1, r_GfxInfo.x2 + iHeight - 2, r_GfxInfo.y2 - 1, 270, 90, FILLED);
		pWind->SetPen(SKYBLUE, 1);
		for (int i = 0;i <= ArcHeight; i++)
		{
			pWind->DrawArc(r_GfxInfo.x1 - ArcHeight + i, r_GfxInfo.y1, r_GfxInfo.x1 + ArcHeight + i, r_GfxInfo.y2, 270, 90);
		}
	}
	if (invert)
	{
		pWind->SetPen(BLACK, 3);
		int y_Center = r_GfxInfo.y2 - Midpoint;
		int x_Center = r_GfxInfo.x2 + iHeight + 3;
		int Raduis = 6;
		if (selected)
			pWind->DrawCircle(x_Center-1, y_Center, Raduis);
		else pWind->DrawCircle(x_Center-1, y_Center, Raduis, FRAME);
		pWind->DrawLine(x_Center-1 + Raduis, y_Center, x_Center + Raduis + 10, y_Center);
	}
	if (connections)
	{
		pWind->SetPen(BLACK, 3);
		int dist = (r_GfxInfo.y2 - r_GfxInfo.y1) / 4;
		for (size_t i = 1; i <= 3; i++)
		{
			pWind->DrawLine(r_GfxInfo.x1 - 10, r_GfxInfo.y1 + (i*dist), r_GfxInfo.x1 + ArcHeight - 1, r_GfxInfo.y1 + i*dist);

		}
	}
	else
	{
		pWind->SetPen(BLACK, 3);
		int dist = (r_GfxInfo.y2 - r_GfxInfo.y1) / 3;
		for (size_t i = 1; i < 3; i++)
		{
			pWind->DrawLine(r_GfxInfo.x1 - 10, r_GfxInfo.y1 + (i*dist), r_GfxInfo.x1 + ArcHeight - 1, r_GfxInfo.y1 + i*dist);
		}
	}
	int Taildistance = (r_GfxInfo.x2 - r_GfxInfo.x1) / 3;
	pWind->SetPen(BLACK, 3);
	pWind->SetBrush(SKYBLUE);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x2, r_GfxInfo.y1);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y2, r_GfxInfo.x2, r_GfxInfo.y2);
	pWind->DrawArc(r_GfxInfo.x1 - ArcHeight, r_GfxInfo.y1, r_GfxInfo.x1 + ArcHeight, r_GfxInfo.y2, 270, 90);
	pWind->DrawArc(r_GfxInfo.x1, r_GfxInfo.y1 - 2, r_GfxInfo.x2 + iHeight, r_GfxInfo.y2 + 2, 270, 90);
	pWind->DrawArc(r_GfxInfo.x1 - 2 *Taildistance, r_GfxInfo.y1, r_GfxInfo.x1 , r_GfxInfo.y2,270,90);
	


}

void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawXOR(r_GfxInfo, selected);
}

void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawXOR(r_GfxInfo, selected,true,false);
}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawXOR(r_GfxInfo, selected,false,true);
}

void Output::DrawXNOR3(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawXOR(r_GfxInfo, selected,true,true);
}

void Output::DrawBuffer(GraphicsInfo r_GfxInfo, bool selected, bool invert) const
{
	r_GfxInfo.x2 = r_GfxInfo.x1 + 15;
	r_GfxInfo.x1 -= 15;
	r_GfxInfo.y2 = r_GfxInfo.y1;
	r_GfxInfo.y1 -= 15;
	int raduis = 6;
	pWind->SetPen(BLACK, 3);
	pWind->SetBrush(SKYBLUE);
	if(selected)
		pWind->DrawTriangle(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x1, r_GfxInfo.y2 + 15, r_GfxInfo.x2, r_GfxInfo.y2,FILLED);
	else pWind->DrawTriangle(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x1, r_GfxInfo.y2 + 15, r_GfxInfo.x2, r_GfxInfo.y2,FRAME);
	if (invert)
	{
		if (selected)
			pWind->DrawCircle(r_GfxInfo.x2 + raduis-2, r_GfxInfo.y2, raduis, FILLED);
		else 
			pWind->DrawCircle(r_GfxInfo.x2 + raduis-2, r_GfxInfo.y2, raduis, FRAME);
		pWind->DrawLine(r_GfxInfo.x2 + raduis+1, r_GfxInfo.y2, r_GfxInfo.x2 + raduis + 11, r_GfxInfo.y2);
	}
	else 
		pWind->DrawLine(r_GfxInfo.x2 + -1, r_GfxInfo.y2, r_GfxInfo.x2+9, r_GfxInfo.y2);
	pWind->DrawLine(r_GfxInfo.x1 - 10, r_GfxInfo.y2, r_GfxInfo.x1, r_GfxInfo.y2);
}

void Output::DrawBuffer(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawBuffer(r_GfxInfo, selected, false);
}

void Output::DrawInverter(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawBuffer(r_GfxInfo, selected, true);
}

void Output::DrawSwitch(GraphicsInfo r_GfxInfo,bool selected)
{
	r_GfxInfo.x2 = r_GfxInfo.x1 + 20;
	r_GfxInfo.x1 -= 20;
	r_GfxInfo.y2 = r_GfxInfo.y1 + 10;
	r_GfxInfo.y1 -= 10;
	pWind->SetPen(BLACK, 3);
	pWind->DrawRectangle(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x2, r_GfxInfo.y2,FRAME);
	pWind->DrawLine(r_GfxInfo.x1 + 10, r_GfxInfo.y1+1, r_GfxInfo.x1 + 10, r_GfxInfo.y2-2);
	pWind->SetBrush(GREY);
	pWind->DrawRectangle(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x1 + 13, r_GfxInfo.y2);
	if (selected)
	{
		pWind->SetBrush(SKYBLUE);
		pWind->DrawRectangle(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x2, r_GfxInfo.y2, FILLED);
		pWind->SetPen(STEELBLUE, 3);
		pWind->SetBrush(STEELBLUE);
		pWind->DrawRectangle(r_GfxInfo.x2 - 10, r_GfxInfo.y1+3, r_GfxInfo.x2-3, r_GfxInfo.y2-3,FILLED);
		pWind->SetPen(BLACK, 3);
		pWind->DrawLine(r_GfxInfo.x2-10, r_GfxInfo.y1 + 1, r_GfxInfo.x2-10, r_GfxInfo.y2 - 2);
	}
}

//TODO: Add similar functions to draw all components


void Output::DrawConnection(GraphicsInfo r_GfxInfo, bool selected) const
{
	//TODO: Add code to draw connection
}


Output::~Output()
{
	delete pWind;
}
