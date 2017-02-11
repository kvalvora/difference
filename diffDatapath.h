#pragma once
#include"classVectorPrimitives3.h"

class datapath {
	bus *rst, *clk;
	bus *read, *write;
	bus *gt, *lt;
	bus *ldCntr, *incCntr, *addrout;
	bus *result;
	bus *controllerFree, *getdata;
	bus *entemp;

	dRegisterE* temp;
	dRegisterE* rgt;
	dRegisterE* rlt;
	Comparator* a_gt_b;
	Comparator* a_lt_b;
	upCounterRaE* addrCntr;
	Compliment* comp;
	Adder* add1;
	Adder* difference;
	Memory* memory;

	//Internal buses
	bus tempout;
	bus rgtout;
	bus rltout;
	bus memout;
	bus addrin;
	bus compout;
	bus ci, co, one;
	bus add1out;
	bus eq, memin;

public:
	datapath(bus &rst_, bus &clk_, bus &read_, bus &write_, bus &gt_, bus &lt_,
		bus &ldCntr_, bus &incCntr_, bus &addrout_, bus &result_,
		bus &controllerFree_, bus &getdata_, bus &entemp_);
	~datapath(){}
	void evl();
	void evlMemory() { memory->evl(); }
	void initMemory(string filename) { memory->init(filename); }
	void dumpMemory(string filename) { memory->dump(filename); }
};