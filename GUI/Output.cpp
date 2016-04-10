#include "Output.h"

void Output::Register(GraphicsInfo r_GfxInfo, Cell type) const
{
	int ix = r_GfxInfo.x1 / UI.PixelDenisty;
	int iy = r_GfxInfo.y1 / UI.PixelDenisty;
	int fx = ceil(r_GfxInfo.x2 / (double)UI.PixelDenisty);
	int fy = ceil(r_GfxInfo.y2 / (double)UI.PixelDenisty);
	for (int i = 0; i <= fx - ix; i++)
	{
		for (int j = 0;j <= fy - iy;j++)
			Components[ix + i][iy + j] = type;
	}
}

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
	Components = new Cell*[UI.GridWidth];
	for (int i = 0; i < UI.GridWidth; i++)
	{
		Components[i] = new Cell[UI.GridHeight];
	}
	for (int i = 0; i < UI.GridWidth; i++)
	{
		for (int j = 0; j < UI.GridHeight; j++)
		{
			Components[i][j] = Empty;
		}
	}
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
void Output::print()
{
	int counter=0;
	ofstream out("output.txt");
	for (int i = 0; i < UI.GridWidth; i++)
	{
		out << i<<" ";
	}
	out << endl;
	for (int i = 0; i < UI.GridHeight; i++)
	{
		out << ++counter<< ' ';
		for (int j = 0; j < UI.GridWidth; j++)
		{
			switch (Components[i][j])
			{
			case Empty:
				out << "E";
				break;
			case Gate:
				out << "G";
				break;
			case Connection:
				out << "C";
				break;
			case Line:
				out << "L";
				break;
			default:	
				break;
			}
			out << " ";
		}
		out << endl;
	}
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);
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
	MenuItemImages[ITM_OR2] = "images\\Menu\\Menu_OR2.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Menu\\Menu_Exit.jpg";

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i<ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
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

void Output::DrawAND(GraphicsInfo r_GfxInfo, bool selected, bool invert, bool connections) const
{
	r_GfxInfo.x2 = r_GfxInfo.x1 + UI.AllGateDimensions / 4;
	r_GfxInfo.y2 = r_GfxInfo.y1 + UI.AllGateDimensions/2;
	r_GfxInfo.x1 -= UI.AllGateDimensions / 4;
	r_GfxInfo.y1 -= UI.AllGateDimensions / 2;
	int raduis = (r_GfxInfo.y2 - r_GfxInfo.y1) / 2;
	raduis += 9;
	pWind->SetPen(BLACK, 3);
	pWind->SetBrush(SKYBLUE);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x2, r_GfxInfo.y1);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y2, r_GfxInfo.x2, r_GfxInfo.y2);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x1, r_GfxInfo.y2);
	pWind->DrawArc(r_GfxInfo.x2 - raduis + 3, r_GfxInfo.y1 - 2, r_GfxInfo.x2 + raduis - 6, r_GfxInfo.y2 + 2, 270, 90);
	if (selected) {
		pWind->DrawArc(r_GfxInfo.x2 - raduis + 3, r_GfxInfo.y1 - 2, r_GfxInfo.x2 + raduis - 6, r_GfxInfo.y2 + 2, 270, 90, FILLED);
		pWind->SetPen(SKYBLUE);
		pWind->DrawRectangle(r_GfxInfo.x1 + 2, r_GfxInfo.y1 + 2, r_GfxInfo.x2, r_GfxInfo.y2 - 1, FILLED);
	}
	if (!invert)
	{
		pWind->SetPen(BLACK, 3);
		pWind->DrawLine(r_GfxInfo.x2 + raduis - 9, r_GfxInfo.y1 + raduis - 9, r_GfxInfo.x2 + raduis + 10, r_GfxInfo.y1 + raduis - 9);
		Register(GraphicsInfo(r_GfxInfo.x2 + raduis - 9, r_GfxInfo.y1 + raduis - 9, r_GfxInfo.x2 + raduis + 10, r_GfxInfo.y1 + raduis - 9), Connection);
	}
	if (invert)
	{
		pWind->SetPen(BLACK, 3);
		int y_Center = r_GfxInfo.y1 + raduis - 9;
		int x_Center = r_GfxInfo.x2 + raduis - 1;
		int Raduis = UI.InverterDimensions;
		if (selected)
			pWind->DrawCircle(x_Center - 1, y_Center, Raduis);
		else pWind->DrawCircle(x_Center - 1, y_Center, Raduis, FRAME);
		pWind->DrawLine(x_Center - 1 + Raduis, y_Center, x_Center + Raduis + 10, y_Center);
		Register(GraphicsInfo(x_Center - 1 + Raduis, y_Center, x_Center + Raduis + 10, y_Center), Connection);
		Register(GraphicsInfo(r_GfxInfo.x2 + raduis - 6, y_Center, x_Center - 1 + Raduis, y_Center), Gate);
	}
	pWind->SetPen(BLACK, 3);
	if (connections)
	{
		int dist = (r_GfxInfo.y2 - r_GfxInfo.y1) / 4;
		for (size_t i = 1; i <= 3; i++)
		{
			pWind->DrawLine(r_GfxInfo.x1 - UI.ConnectionDimensions, (r_GfxInfo.y1 + i* dist), r_GfxInfo.x1, (r_GfxInfo.y1) + i* dist);
			Register(GraphicsInfo(r_GfxInfo.x1 - UI.ConnectionDimensions, (r_GfxInfo.y1 + i* dist), r_GfxInfo.x1, (r_GfxInfo.y1) + i* dist), Connection);

		}
	}
	else
	{
		int dist = (r_GfxInfo.y2 - r_GfxInfo.y1) / 3;
		for (size_t i = 1; i <= 2; i++)
		{
			pWind->DrawLine(r_GfxInfo.x1 - UI.ConnectionDimensions, (r_GfxInfo.y1 + i* dist), r_GfxInfo.x1, (r_GfxInfo.y1) + i*dist);
			Register(GraphicsInfo(r_GfxInfo.x1 - UI.ConnectionDimensions, (r_GfxInfo.y1 + i* dist), r_GfxInfo.x1, (r_GfxInfo.y1) + i*dist), Connection);
		}
	}
	Register(GraphicsInfo(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x2 + raduis-6, r_GfxInfo.y2), Gate);
}

void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawAND(r_GfxInfo, selected);
}

void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawAND(r_GfxInfo, selected, true);
}

void Output::DrawAND3(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawAND(r_GfxInfo, selected, false, true);
}

void Output::DrawNAND3(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawAND(r_GfxInfo, selected, true, true);
}

void Output::DrawOr(GraphicsInfo r_GfxInfo, bool selected, bool invert, bool connections) const
{
	pWind->SetPen(BLACK, 3);
	r_GfxInfo.x2 = r_GfxInfo.x1 + UI.AllGateDimensions/4;
	r_GfxInfo.y2 = r_GfxInfo.y1 + UI.AllGateDimensions/2;
	r_GfxInfo.x1 -= UI.AllGateDimensions / 4;
	r_GfxInfo.y1 -= UI.AllGateDimensions / 2;
	int ArcHeight = (r_GfxInfo.x2 - r_GfxInfo.x1) / 2;
	int Midpoint = (r_GfxInfo.y2 - r_GfxInfo.y1) / 2;
	int iHeight = (r_GfxInfo.x2 - r_GfxInfo.x1);
	if (!invert)pWind->DrawLine(r_GfxInfo.x2 + iHeight, r_GfxInfo.y1 + Midpoint, r_GfxInfo.x2 + iHeight + 10, r_GfxInfo.y1 + Midpoint);
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
		int Raduis = UI.InverterDimensions;
		if (selected)
			pWind->DrawCircle(x_Center - 1, y_Center, Raduis);
		else pWind->DrawCircle(x_Center - 1, y_Center, Raduis, FRAME);
		pWind->DrawLine(x_Center - 1 + Raduis, y_Center, x_Center + Raduis + 10, y_Center);
	}
	if (connections)
	{
		pWind->SetPen(BLACK, 3);
		int dist = (r_GfxInfo.y2 - r_GfxInfo.y1) / 4;
		for (size_t i = 1; i <= 3; i++)
		{
			pWind->DrawLine(r_GfxInfo.x1 - UI.ConnectionDimensions, r_GfxInfo.y1 + (i*dist), r_GfxInfo.x1 + ArcHeight - 1, r_GfxInfo.y1 + i*dist);

		}
	}
	else
	{
		pWind->SetPen(BLACK, 3);
		int dist = (r_GfxInfo.y2 - r_GfxInfo.y1) / 3;
		for (size_t i = 1; i < 3; i++)
		{
			pWind->DrawLine(r_GfxInfo.x1 - UI.ConnectionDimensions, r_GfxInfo.y1 + (i*dist), r_GfxInfo.x1 + ArcHeight - 1, r_GfxInfo.y1 + i*dist);
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
	r_GfxInfo.x2 = r_GfxInfo.x1 + UI.AllGateDimensions/4;
	r_GfxInfo.y2 = r_GfxInfo.y1 + UI.AllGateDimensions / 2;
	r_GfxInfo.x1 -= UI.AllGateDimensions / 4;
	r_GfxInfo.y1 -= UI.AllGateDimensions / 2;
	int ArcHeight = (r_GfxInfo.x2 - r_GfxInfo.x1) / 2;
	int Midpoint = (r_GfxInfo.y2 - r_GfxInfo.y1) / 2;
	int iHeight = (r_GfxInfo.x2 - r_GfxInfo.x1);
	pWind->SetPen(BLACK, 3);
	if (!invert)pWind->DrawLine(r_GfxInfo.x2 + iHeight, r_GfxInfo.y1 + Midpoint, r_GfxInfo.x2 + iHeight + 10, r_GfxInfo.y1 + Midpoint);
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
		int Raduis = UI.InverterDimensions;
		if (selected)
			pWind->DrawCircle(x_Center - 1, y_Center, Raduis);
		else pWind->DrawCircle(x_Center - 1, y_Center, Raduis, FRAME);
		pWind->DrawLine(x_Center - 1 + Raduis, y_Center, x_Center + Raduis + 10, y_Center);
	}
	if (connections)
	{
		pWind->SetPen(BLACK, 3);
		int dist = (r_GfxInfo.y2 - r_GfxInfo.y1) / 4;
		for (size_t i = 1; i <= 3; i++)
		{
			pWind->DrawLine(r_GfxInfo.x1 - UI.ConnectionDimensions, r_GfxInfo.y1 + (i*dist), r_GfxInfo.x1 + ArcHeight - 1, r_GfxInfo.y1 + i*dist);

		}
	}
	else
	{
		pWind->SetPen(BLACK, 3);
		int dist = (r_GfxInfo.y2 - r_GfxInfo.y1) / 3;
		for (size_t i = 1; i < 3; i++)
		{
			pWind->DrawLine(r_GfxInfo.x1 - UI.ConnectionDimensions, r_GfxInfo.y1 + (i*dist), r_GfxInfo.x1 + ArcHeight - 1, r_GfxInfo.y1 + i*dist);
		}
	}
	int Taildistance = (r_GfxInfo.x2 - r_GfxInfo.x1) / 3;
	pWind->SetPen(BLACK, 3);
	pWind->SetBrush(SKYBLUE);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x2, r_GfxInfo.y1);
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y2, r_GfxInfo.x2, r_GfxInfo.y2);
	pWind->DrawArc(r_GfxInfo.x1 - ArcHeight, r_GfxInfo.y1, r_GfxInfo.x1 + ArcHeight, r_GfxInfo.y2, 270, 90);
	pWind->DrawArc(r_GfxInfo.x1, r_GfxInfo.y1 - 2, r_GfxInfo.x2 + iHeight, r_GfxInfo.y2 + 2, 270, 90);
	pWind->DrawArc(r_GfxInfo.x1 - 2 * Taildistance, r_GfxInfo.y1, r_GfxInfo.x1, r_GfxInfo.y2, 270, 90);



}

void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawXOR(r_GfxInfo, selected);
}

void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawXOR(r_GfxInfo, selected, true, false);
}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawXOR(r_GfxInfo, selected, false, true);
}

void Output::DrawXNOR3(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawXOR(r_GfxInfo, selected, true, true);
}

void Output::DrawBuffer(GraphicsInfo r_GfxInfo, bool selected, bool invert) const
{
	r_GfxInfo.x2 = r_GfxInfo.x1 + UI.BufferDimensions / 2;
	r_GfxInfo.x1 -= UI.BufferDimensions/2;
	r_GfxInfo.y2 = r_GfxInfo.y1;
	r_GfxInfo.y1 -= UI.BufferDimensions / 2;
	int raduis = UI.InverterDimensions;
	pWind->SetPen(BLACK, 3);
	pWind->SetBrush(SKYBLUE);
	if (selected)
		pWind->DrawTriangle(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x1, r_GfxInfo.y2 + UI.BufferDimensions/2, r_GfxInfo.x2, r_GfxInfo.y2, FILLED);
	else pWind->DrawTriangle(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x1, r_GfxInfo.y2 + UI.BufferDimensions/2, r_GfxInfo.x2, r_GfxInfo.y2, FRAME);
	if (invert)
	{
		if (selected)
			pWind->DrawCircle(r_GfxInfo.x2 + raduis - 2, r_GfxInfo.y2, raduis, FILLED);
		else
			pWind->DrawCircle(r_GfxInfo.x2 + raduis - 2, r_GfxInfo.y2, raduis, FRAME);
		pWind->DrawLine(r_GfxInfo.x2 + raduis + 1, r_GfxInfo.y2, r_GfxInfo.x2 + raduis + UI.ConnectionDimensions+1, r_GfxInfo.y2);
	}
	else
		pWind->DrawLine(r_GfxInfo.x2 + -1, r_GfxInfo.y2, r_GfxInfo.x2 + UI.ConnectionDimensions-1, r_GfxInfo.y2);
	pWind->DrawLine(r_GfxInfo.x1 - UI.ConnectionDimensions, r_GfxInfo.y2, r_GfxInfo.x1, r_GfxInfo.y2);
}

void Output::DrawBuffer(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawBuffer(r_GfxInfo, selected, false);
}

void Output::DrawInverter(GraphicsInfo r_GfxInfo, bool selected)
{
	DrawBuffer(r_GfxInfo, selected, true);
}

void Output::DrawSwitch(GraphicsInfo r_GfxInfo, bool ON, bool selected)
{
	r_GfxInfo.x2 = r_GfxInfo.x1 + UI.SwitchWidth/2;
	r_GfxInfo.x1 -= UI.SwitchWidth/2;
	r_GfxInfo.y2 = r_GfxInfo.y1 + UI.SwitchHeight/2;
	r_GfxInfo.y1 -= UI.SwitchHeight / 2;
	pWind->SetPen(BLACK, 3);
	pWind->DrawRectangle(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x2, r_GfxInfo.y2, FRAME);
	pWind->DrawLine(r_GfxInfo.x1 + 10, r_GfxInfo.y1 + 1, r_GfxInfo.x1 + 10, r_GfxInfo.y2 - 2);
	pWind->SetBrush(GREY);
	pWind->DrawRectangle(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x1 + 3 + UI.SwitchWidth / 4, r_GfxInfo.y2);
	if (selected)
	{
		pWind->SetBrush(SKYBLUE);
		pWind->SetPen(SKYBLUE, 3);
		pWind->DrawRectangle(r_GfxInfo.x1 + 3 + UI.SwitchWidth / 4, r_GfxInfo.y1 + 3, r_GfxInfo.x2 - 3, r_GfxInfo.y2 - 3);
	}
	if (ON)
	{
		pWind->SetBrush(ROYALBLUE);
		pWind->SetPen(ROYALBLUE, 3);
		pWind->DrawRectangle(r_GfxInfo.x1 + 3, r_GfxInfo.y1 + 3, r_GfxInfo.x2 - 3, r_GfxInfo.y2 - 3, FILLED);
		pWind->SetPen(STEELBLUE, 3);
		pWind->SetBrush(STEELBLUE);
		pWind->DrawRectangle(r_GfxInfo.x2 - UI.SwitchWidth / 4, r_GfxInfo.y1 + 3, r_GfxInfo.x2 - 3, r_GfxInfo.y2 - 3, FILLED);
		pWind->SetPen(BLACK, 3);
		pWind->DrawLine(r_GfxInfo.x2 - UI.SwitchWidth / 4, r_GfxInfo.y1 + 1, r_GfxInfo.x2 - UI.SwitchWidth / 4, r_GfxInfo.y2 - 2);
	}
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(r_GfxInfo.x2, (r_GfxInfo.y2 + r_GfxInfo.y1) / 2, r_GfxInfo.x2 + UI.ConnectionDimensions, (r_GfxInfo.y2 + r_GfxInfo.y1) / 2);
}

void Output::DrawLED(GraphicsInfo r_GfxInfo, bool selected, bool ON) const
{
	pWind->SetPen(BLACK, 3);
	int raduis = UI.LedDimensions * 4 / 7;
	r_GfxInfo.x2 = r_GfxInfo.x1 - 1.75*raduis+3;
	r_GfxInfo.y2 = r_GfxInfo.y1 - 0.5*raduis;
	int dist = 10 * tan(22.5);
	if (ON)
	{
		pWind->SetBrush(LIGHTGOLDENRODYELLOW);
		pWind->DrawCircle(r_GfxInfo.x1 - dist + 2, r_GfxInfo.y1, raduis, FILLED);
	}
	else if (selected)
	{
		pWind->SetBrush(SKYBLUE);
		pWind->DrawCircle(r_GfxInfo.x1 - dist+2 , r_GfxInfo.y1, raduis, FILLED);
	}
	pWind->DrawCircle(r_GfxInfo.x1 - dist+2, r_GfxInfo.y1, raduis, FRAME);
	pWind->DrawLine(r_GfxInfo.x2, r_GfxInfo.y2, r_GfxInfo.x2, r_GfxInfo.y1 + 0.5*raduis);
	pWind->DrawLine(r_GfxInfo.x2, r_GfxInfo.y2, r_GfxInfo.x2 + 0.75*raduis, r_GfxInfo.y2);
	pWind->DrawLine(r_GfxInfo.x2, r_GfxInfo.y1 + 0.5*raduis, r_GfxInfo.x2 + 0.75*raduis, r_GfxInfo.y1 + 0.5*raduis);
	pWind->DrawLine(r_GfxInfo.x2 - UI.ConnectionDimensions, r_GfxInfo.y1, r_GfxInfo.x2, r_GfxInfo.y1);
	if (selected && !ON)
	{
		pWind->SetBrush(SKYBLUE);
		pWind->SetPen(SKYBLUE, 3);
	}
	else
	{
		pWind->SetBrush(BLACK);
		pWind->SetPen(BLACK, 3);
	}
	pWind->DrawRectangle(r_GfxInfo.x2 + 2, r_GfxInfo.y2 + 2, r_GfxInfo.x2 + 0.75*raduis, r_GfxInfo.y1 + 0.5*raduis-1);
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
