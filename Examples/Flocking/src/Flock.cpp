#include "Flock.h"
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <cmath>
#include <functional>

namespace Flocking {


	void Boid::integrate(double duration) {
		position.x += (velocity).x*duration;
		position.y += (velocity).y*duration;
		if (isnan(position.x)){
			cerr<<"v: " <<(velocity).x<<" "<<duration<<endl;
			exit(0);
		}
		if (isnan(position.y)) {
			cerr<<"v: "<<(velocity).y<<" "<<duration<<endl;
			exit(0);
		}
	}

	void Boid::integrate(double duration, SteeringResult &steer) {
		integrate(duration);
		velocity.x += (steer.linear_acceleration).x*duration;
		velocity.y += (steer.linear_acceleration).y*duration;
		if (isnan(velocity.x)) {
			cerr<<"a: "<<(steer.linear_acceleration).x<<" "<<duration<<endl;
			exit(0);
		}
		if (isnan(velocity.y)) {
			cerr<<"a: "<<(steer.linear_acceleration).y<<" "<<duration<<endl;
			exit(0);
		}
	}

	ostream& operator<<(ostream& os, const Boid& v) {
		return os<<v.label<<" ["<<v.position<<","<<v.velocity<<"]";
	}


	ostream& operator<<(ostream& os, const Edge& e) {
		return os<<e.from->label<<" "<<e.to->label;
	}


	Flock::Flock(int n, int size, double speed) : n_boids{n} {
		boids.resize(n_boids);
		neighbor_list.resize(n_boids);

		default_random_engine ran{}; // generates integers
		uniform_real_distribution<> ureal{0,static_cast<double>(size)}; // maps ints into doubles // in [0:max)
		auto gen = bind(uniform_real_distribution<double>{-speed,speed},default_random_engine{});

		for (unsigned i = 0; i < static_cast<unsigned>(n_boids); i++)
		{
			boids[i] = new Boid();
			boids[i]->index=i;
			boids[i]->maxSpeed=speed;
			boids[i]->world_size=size;
			boids[i]->position.x = ureal(ran);
			boids[i]->position.y = ureal(ran);
			//boids[i].orientation = aicore::randomReal(aicore::M_PI);
			boids[i]->velocity.x = gen();
			boids[i]->velocity.y = gen();
			//boids[i].rotation = (aicore::real)0;
		}

	}




	Flock::~Flock()
	{/*
		delete separation;
		delete cohesion;
		delete vMA;
		*/
	}



	unsigned Flock::prepareNeighourhood(const Boid *pb, double ray)
	//double minDotProduct /* = -1.0 */)
	{
		unsigned i = pb->index;
		neighbor_list[i].clear();
		for (unsigned j=0; j<static_cast<unsigned>(n_boids); ++j) {
			// Ignore ourself
			if (i == j) continue;

			// Check for maximum distance
			if (boids[i]->position.Distance(boids[j]->position) > ray) continue;

			// Check for angle
			/*		if (minDotProduct > -1.0)
			{
				aicore::Vector3 offset = k->position - of->position;
				if (look * offset.unit() < minDotProduct)
				{
					continue;
				}
			}*/

			// If we get here we've passed all tests
			neighbor_list[i].push_back(boids[j]);
		}
		return neighbor_list[i].size();
	}


	Location Flock::getNeighbourhoodCenter(const Boid *of)
	{
		Location center;
		int index = of->index;
		unsigned count = 0;
		for (Boid *pb : neighbor_list[index])
		{
			center += pb->position;
			count ++;
		}
		center *= 1.0 / (double) count;
		return center;
	}

	Velocity Flock::getNeighbourhoodAverageVelocity(const Boid *of)
	{
		Velocity center;
		unsigned count = 0;
		int index = of->index;
		for (Boid* pb : neighbor_list[index])
		{
			center += pb->velocity;
			count ++;
		}
		center *= 1.0 / (double)count;

		return center;
	}


	ostream& operator<<(ostream& os, const Flock& g) {
		os<<g.getNBoids() <<" boids; \n";
		for (const Boid* pv : g.getBoids()) {
			os<<*pv<<" ";
		}
		os<<"\n";

		return os;
	}





}
