#pragma once
//#include "..\Defs.h"
#include "Input.h"
#include<cmath>
#include<fstream>
#include<iostream>
#include<queue>	
#include"UI_Info.h";
class Output	//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window
	Cell **Components;
	void Register(GraphicsInfo r_GfxInfo, Cell type)	const;//this is a utility function given the start and the end of a shape and its type and it registers it
	ofstream out;
	pair<int, int>**parent;
	vector<pair<int, int> > points;
	bool valid(int x, int y);
	void BFS(GraphicsInfo r_GfxInfo);
	void Getpoints(int x,int y);
	void Drawconnection();
	//Auxillary functions to create the status bar
	void DrawToolBar();
	void CreateSimulation();

public:
	Output(); // Performs the Window Initialization
	Input* CreateInput() const; //creates a pointer to the Input object
	void ChangeTitle(string Title) const;
	bool connect(GraphicsInfo r_GfxInfo);
	void CreateDesignToolBar();	//Tool bar of the design mode
	void CreateSimulationToolBar();//Tool bar of the simulation mode
	void CreateStatusBar() const;	//Create Status bar

	void ClearStatusBar() const;		//Clears the status bar
	void ClearDrawingArea() const;	//Clears the drawing area

	window* CreateWind(int wd, int h, int x, int y) const; //Creates user interface window
	void print();
	void DrawGatesToolBar();
	void DrawGatesBar();
	void DrawAndBar();
	void DrawOrBar();
	void DrawXorBar();
	void EraseToolBar();
	void CreateSimulationBar();
	void SimulationIcon(bool SIMU);
	// Draws 2-input AND gate
	void DrawAND(GraphicsInfo r_GfxInfo, bool selected = false, bool invert = false, bool connections = false) const;
	void DrawAND2(GraphicsInfo r_GfxInfo, bool selected = false);
	void DrawNAND2(GraphicsInfo r_GfxInfo,bool=false);
	void DrawAND3(GraphicsInfo r_GfxInfo,bool=false);
	void DrawNAND3(GraphicsInfo r_GfxInfo,bool=false);
	void DrawOr(GraphicsInfo r_GfxInfo, bool selected = false, bool invert = false, bool connections = false) const;
	void DrawOR2(GraphicsInfo r_GfxInfo, bool selected=false);
	void DrawOR3(GraphicsInfo r_GfxInfo, bool selected=false);
	void DrawNOR2(GraphicsInfo r_GfxInfo, bool selected=false);
	void DrawNOR3(GraphicsInfo r_GfxInfo, bool selected=false);
	void DrawXOR(GraphicsInfo r_GfxInfo, bool selected = false, bool invert = false, bool connections = false) const;
	void DrawXOR2(GraphicsInfo r_GfxInfo, bool selected = false);
	void DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected = false);
	void DrawXOR3(GraphicsInfo r_GfxInfo, bool selected = false);
	void DrawXNOR3(GraphicsInfo r_GfxInfo, bool selected = false);
	void DrawBuffer(GraphicsInfo r_GfxInfo, bool selected , bool invert ) const;
	void DrawBuffer(GraphicsInfo r_GfxInfo, bool selected = false);
	void DrawInverter(GraphicsInfo r_GfxInfo, bool selected = false);
	void DrawSwitch(GraphicsInfo r_GfxInfo, bool = false, bool = false);
	void DrawLED(GraphicsInfo r_GfxInfo, bool selected = false, bool ON = false) const;
	
	///TODO: Make similar functions for drawing all other gates, switch, and LED, .. etc

	// Draws Connection
	void DrawConnection(GraphicsInfo r_GfxInfo, bool selected = false) const;
	
	void PrintMsg(string msg) const;	//Print a message on Status bar


	~Output();
};
