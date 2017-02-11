#pragma once
#include"classVectorPrimitives3.h"

class controller {
	bus *rst, *clk;
	bus *read, *write;
	bus *gt, *lt;
	bus *ldCntr, *incCntr, *addrout;
	bus *result;
	bus *controllerFree, *getdata;
	bus *entemp;
	int Pstate, Nstate;
public:
	controller(bus &rst_, bus &clk_, bus &read_, bus &write_, bus &gt_, bus &lt_,
		bus &ldCntr_, bus &incCntr_, bus &addrout_, bus &result_,
		bus &controllerFree_, bus &getdata_, bus &entemp_);
	~controller() {}
	void evl();
};