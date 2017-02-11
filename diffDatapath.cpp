#include "diffdatapath3.h"

datapath::datapath(bus & rst_, bus & clk_, bus & read_, bus & write_, bus & gt_, bus & lt_, 
	bus & ldCntr_, bus & incCntr_, bus & addrout_, bus & result_, 
	bus & controllerFree_, bus & getdata_, bus & entemp_)
	:
	rst(&rst_),clk(&clk_),read(&read_),write(&write_),gt(&gt_),lt(&lt_),
	ldCntr(&ldCntr_),incCntr(&incCntr_),addrout(&addrout_),result(&result_),
	controllerFree(&controllerFree_),getdata(&getdata_), entemp(&entemp_)
{
	result->resize(8, 'X');

	//internal busses
	tempout.resize(8, 'X');
	rgtout.resize(8, '0');
	rltout.resize(8, '1');
	memout.resize(8, 'X');
	addrin.resize(4, '0');
	compout.resize(8, 'X');
	ci.resize(1, '0');
	co.resize(1, '0');
	one = "00000001";
	add1out.resize(8, 'X');

	temp = new dRegisterE(memout, *clk, *entemp, tempout);
	rgt = new dRegisterE(tempout, *clk, *gt, rgtout);
	rlt = new dRegisterE(tempout, *clk, *lt, rltout);
	a_gt_b = new Comparator(tempout, rgtout, *lt, eq, *gt);
	a_lt_b = new Comparator(tempout, rltout, *lt, eq, *gt);
	addrCntr = new upCounterRaE(addrin, *clk, *rst, *ldCntr, *incCntr, *addrout);
	comp = new Compliment(rltout, compout);
	add1 = new Adder(compout, one, ci, co, add1out);
	difference = new Adder(rgtout, add1out, ci, co, *result);
	memory = new Memory(*rst, *clk, *read, *write, memin, *addrout, memout);
}

void datapath::evl()
{
	memory->evl();
	temp->evl();
	rgt->evl();
	rlt->evl();
	a_lt_b->evl();
	addrCntr->evl();
	
	if (addrout->ival() == 8)
	{
		comp->evl();
		add1->evl();
		difference->evl();
		cout << "\nThe difference of "<<rgtout<<" & "<<rltout<<" is:" << *result;
	}
}
