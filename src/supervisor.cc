#include "supervisor.hh"

// Ctor
supervisor::supervisor()
{
    ring = new network_ring();
	for (int i = 0; i < ROBOT_COUNT; i++) 
    {
		int location = select_random_location();
		robots[i] = new robot(location);
	}
	round_count = 0;
}

// Select a random location on the ring
int supervisor::select_random_location()
{
	return rand() % POINT_COUNT;
}

// Place the robot on the ring and command robot to walk
void supervisor::walk(robot *r)
{
    std::string s1("is now walking ");
    std::string s2((r->get_direction() == LEFT ? "LEFT" : "RIGHT"));
    log(s1 + s2, r);
    while (true)
	{
        if (r->get_steps_taken() == POINT_COUNT) 
        {
            log("is the final robot", r);
            return;
        }
        r->set_location(ring->move_ring_point(r));
        r->increase_steps_taken();
         
		if (r->get_location() == -1)
		{
            log("has collided", r);
            return; // were done here
		}
        log("has moved", r);
        std::this_thread::sleep_for(std::chrono::milliseconds(UI_SPEED));
	}
}

// Main thread of execution
// Places robots into individual threads
void supervisor::execute()
{
    std::thread threads[ROBOT_COUNT];
    int i = 0;
    for (robot *r : robots)
    {
        log("has been dropped", r);
		threads[i++] = std::thread(&supervisor::walk, this, r);
    }
    for (int i=0; i<ROBOT_COUNT; i++)
    {
        threads[i].join();
    }
}

int* supervisor::get_robot_positions() {
	return ring->get_robot_positions();
}

int supervisor::get_robot_count() {
	return ring->robot_count;
}
// Log the output for each robot
void supervisor::log(std::string s, robot *r)
{
    LOG_CHECK;
    std::cout << "[Robot:" << r->get_id() << " Size:" << r->get_size() << " Location:" << r->get_location() << " Steps Taken: " << r->get_steps_taken() <<  "] " << s << std::endl;
}
