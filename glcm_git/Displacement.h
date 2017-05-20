#pragma once
#include <vector>

struct Displacement{
	
	int step;
	int angle;
	Displacement(){};
	Displacement(int s, int a):step(s),angle(a){};
	Displacement(const Displacement& d){ step = d.step;  angle = d.angle; }
	void toString(){ std::cout<<step<<","<<angle<<"\n";	}
};


struct Displacements{
	std::vector<Displacement> vector;
	void  push(Displacement& d){ vector.push_back(d);}
	int getNumDisplacements(){ return vector.size();}
};