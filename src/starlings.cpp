#include "boids.h"
#include <iostream>
#include <math.h>
#include "trip.h"
#include <vector>
#define MAX_BOIDS 1000
#define RA 0.4
#define RR 0.05
#define attfactor 1
#define repulsionfactor 1
#define allignmentfactor 8

using namespace std;

boid allboids[MAX_BOIDS];
boid allmod[MAX_BOIDS];
boid nextboids[MAX_BOIDS];
int size = 800;

inline trip add(trip a, trip b){
		trip c = {a.x + b.x, a.y + b.y, a.z + b.z};
		return c;
	}
inline trip div(trip a, int n){
	trip c = {a.x/n, a.y/n, a.z/n};
	return c;
}
float distance(int first, int second){
	boid firstboid = allboids[first];
	boid secondboid = allboids[second];
	return pow(pow(firstboid.px - secondboid.px, 2)+pow(firstboid.py - secondboid.py, 2)+pow(firstboid.pz - secondboid.pz, 2),0.5);
}

std::vector<int> find_neighbours(int n){
	std::vector<int> ret;
	for (int i = 0; i < size; ++i)
	{
		if (distance(i,n) < RA && i!= n){
			ret.push_back(i);
		}
	}
	return ret;
}	
std::vector<int> find_closer_neighbours(int n, std::vector<int> neighbours){
	std::vector<int> ret;
	int n_size = neighbours.size();
	for (int i = 0; i < n_size; ++i)
	{
		if (distance(neighbours[i],n) < RR){
			ret.push_back(neighbours[i]);
		}
	}
	return ret;
}
trip attraction(int n, std::vector<int> neighbours){
	trip ret = {0,0,0};
	int n_size = neighbours.size();
	for (int i = 0; i < n_size; ++i)
	{	
		int fin = neighbours[i];
		ret.x += allboids[fin].px;
		ret.y += allboids[fin].py;
		ret.z += allboids[fin].pz;
	}
	return div(ret, n_size * (attfactor/80));
}

trip repulsion(int n, std::vector<int> neighbours){
	trip ret = {0,0,0};
	boid fir = allboids[n];
	int n_size = neighbours.size();
	for (int i = 0; i < n_size; ++i)
	{
		boid sec = allboids[neighbours[i]];
		ret.x += fir.px - sec.px;
		ret.y += fir.py - sec.pz;
		ret.z += fir.pz - sec.pz;
	}
	return div(ret,repulsionfactor);
}

trip allignment(int n ,vector<int> neighbours)
{
    trip ret = {0,0,0};
	int n_size = neighbours.size();
    for(int i=0; i<n_size; i++)
    {	
    	boid sec = allboids[neighbours[i]];
        ret.x += sec.vx;
        ret.y += sec.vy;
        ret.z += sec.vz;
    }
      	boid fir = allboids[n];
      	ret = div(ret, n_size);
        ret.x -= fir.vx;
        ret.y -= fir.vy;
        ret.z -= fir.vz;
    return div(ret,allignmentfactor);
}

void move_all_boids_to_new_positions()
{
    trip rule1 = {0,0,0};
    trip rule2 = {0,0,0};
    trip rule3 = {0,0,0};
    vector<int> neighbour;
    for (int i = 0; i < size; ++i)
    {
        neighbour = find_neighbours(i);
        rule1 = attraction(i, neighbour);
        neighbour = find_closer_neighbours(i, neighbour);
        rule2 = repulsion(i, neighbour);
        rule3 = allignment(i, neighbour);
        allmod[i].vx=allboids[i].vx + rule1.x + rule2.x + rule3.x;
        allmod[i].vy=allboids[i].vy + rule1.y + rule2.y + rule3.y;
        allmod[i].vz=allboids[i].vz + rule1.z + rule2.z + rule3.z;
        allmod[i].px=allboids[i].px+allmod[i].vx;
        allmod[i].py=allboids[i].py+allmod[i].vy;
        allmod[i].pz=allboids[i].pz+allmod[i].vz;
    }
    for (int i = 0; i < size; ++i)
    {
	    allboids[i]=allmod[i];
	}
}

int main()
{
	allboids[0] = {0,0,0,1,2,3}; 
	allboids[1] =  {1,1,1,1,2,3};
	trip a = {1,2,3};
	trip b = {2,3,4};
	trip c = add(a,b);
	cout<<c.z<<endl;
	return 0;
}