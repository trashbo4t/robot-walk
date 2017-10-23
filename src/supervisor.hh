#ifndef SUPERVISOR_H
#define SUPERVISOR_H
#endif

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include <chrono>

#include "network_ring.hh"
#include "configs.hh"

class supervisor
{
    public:
	    supervisor();
    	robot *robots[ROBOT_COUNT];
	    network_ring *ring;
    	void execute();
    	int select_random_location();
    	void walk(robot *r);
    	int round_count;
        void log(std::string, robot *r);
};