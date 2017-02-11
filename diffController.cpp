#include "diffcontroller3.h"

controller::controller(bus & rst_, bus & clk_, bus & read_, bus & write_, bus & gt_, bus & lt_, 
	bus & ldCntr_, bus & incCntr_, bus & addrout_, bus & result_, 
	bus & controllerFree_, bus & getdata_, bus & entemp_)
	:
	rst(&rst_), clk(&clk_), read(&read_), write(&write_), gt(&gt_), lt(&lt_),
	ldCntr(&ldCntr_), incCntr(&incCntr_), addrout(&addrout_), result(&result_),
	controllerFree(&controllerFree_), getdata(&getdata_), entemp(&entemp_)
{
	gt->fill('0');
	lt->fill('0');
	result->fill('X');
	Pstate = 0;
	Nstate = 0;
}


void controller::evl()
{
	*read = "0";
	*write = "0";
	*ldCntr = "0";
	*incCntr = "0";
	*entemp = "0";
	*controllerFree = "1";

	switch (Pstate)
	{
	case 0:
		if (*getdata == "1") Nstate = 1;
		else Nstate = 0;
		*controllerFree = "0";
		break;
	case 1:
		Nstate = 2;
		*ldCntr = "1";
		*incCntr = "1";
		*entemp = "1";
		*controllerFree = "0";
		break;
	case 2:
		Nstate = 3;
		*read = "1";
		*entemp = "1";
		*controllerFree = "0";
		break;
	case 3:
		Nstate = 4;
		*ldCntr = "0";
		*incCntr = "1";
		*controllerFree = "0";
		break;
	case 4:
		if (addrout->ival() < 8)
		{
			Nstate = 2;
			*controllerFree = "0";
		}
		else
		{
			Nstate = 0;
			*controllerFree = "1";
		}
		break;
	}

	if (*rst == "1") Pstate = 0;
	else if (*clk == "P") Pstate = Nstate;
}
