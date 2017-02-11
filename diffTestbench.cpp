#include<iostream>
#include<string>
#include"diffcontroller3.h"
#include"diffdatapath3.h"

using namespace std;

int main()
{
	int choice;
	string filename("data3.txt");
	
	bus rst, clk;
	bus read, write;
	bus gt, lt;
	bus ldCntr, incCntr;
	bus addrout(4, '0');
	bus result;
	bus controllerFree, getdata;
	bus entemp;

	datapath *dp = new datapath(rst, clk, read, write, gt, lt, ldCntr, incCntr, addrout, result,
		controllerFree, getdata, entemp);

	controller *con = new controller(rst, clk, read, write, gt, lt, ldCntr, incCntr, addrout, result,
		controllerFree, getdata, entemp);
	
	//memory and controller resetting
	rst = "1";
	dp->evlMemory();
	con->evl();
	rst = "0";

	//initialize memory and dump
	dp->initMemory(filename);
	cout << "Initial memory contents:" << endl;
	dp->dumpMemory("memcontents3.txt");

	do {
		controllerFree = "0";
		getdata = "1";
		do {
			clk = "P";

			dp->evl();
			con->evl();
		} while (controllerFree == "0");
		getdata = "0";

		cout << "\nDo you want to continue (0 or 1)?:" << endl;
		cin >> choice;
	} while (choice > 0);
}