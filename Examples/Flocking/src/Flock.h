#ifndef FLOCK_H
#define FLOCK_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

#include "Vector2D.h"
//#include "Steering.h"

using namespace std;

using namespace Flocking;

namespace Flocking {

	struct Location : public Vector2D {
		Location() {};
		Location(double xx, double yy) : Vector2D(xx, yy) {};
		double Distance(Location &b) {return sqrt(pow(x-b.x,2)+pow(y-b.y,2));};
	};

	struct Velocity : public Vector2D {

		friend Velocity operator-(Velocity lhs,	const Velocity& rhs) // otherwise, both parameters may be const references
			{
				Velocity res;
				res=lhs;
				res-=rhs;
				return res; // return the result by value (uses move constructor)
			}
	};

	struct LinearAcceleration : public Vector2D {
		LinearAcceleration& operator=(const LinearAcceleration& rhs) {
			Vector2D::operator=(rhs);
			return *this;
			}
		LinearAcceleration& operator=(const Location& rhs) {
			Vector2D::operator=(rhs);
			return *this;
			}
			LinearAcceleration& operator=(const Velocity& rhs) {
			Vector2D::operator=(rhs);
			return *this;
			}
	};


	struct SteeringResult {
		LinearAcceleration linear_acceleration;
	};

	struct Boid {
		string label;
		int index;
		Location position;
		Velocity velocity;
		int world_size;
		double maxSpeed;

		void integrate(double duration);
		void integrate(double duration, SteeringResult &steer);

		void WrapWorld() {
			WrapWorld(position.x);
			WrapWorld(position.y);
		}
		void WrapWorld(double &var) {
			if (var < 0) var = world_size;
			if (var > world_size) var = 0;
		}

		void trimMaxSpeed() {
			if (velocity.squareMagnitude() > maxSpeed*maxSpeed) {
				velocity.Normalize();
				velocity *= maxSpeed;
			}
		}
	};

	ostream& operator<<(ostream& os, const Boid& v);

	struct Edge {
		int index;
		Boid *from; // alternatively, put here the index of the node
		Boid *to; // alternatively, put here the index of the node
		string label;
		Edge() {};
		Edge(const Edge& e) : from{e.from}, to{e.to}, label{e.label} {cout<<"copied";};
	};


	ostream& operator<<(ostream& os, const Edge& e);

	class Flock {
		vector<Boid*> boids;
		vector<vector<Boid*>> neighbor_list;
		int n_boids;
		Boid* getBoids(string lab);

	public:
		int getNBoids() const {return n_boids;}

		const Boid& getBoid(int i) const { return *boids[i];}
		const Boid& getBoid(string lab) const;

		const vector<Boid*>& getBoids() const { return boids;}
		const vector<Boid*>& getNeighbors(int i) const { return neighbor_list[i];}

		Flock()=delete;
		Flock(int n, int world_size, double max_speed);
		~Flock();

		/**
		* Sets up the boolean flags of boids in the neighbourhood of the given boid.
		*/
		unsigned prepareNeighourhood(const Boid *pb, double ray);

		/**
		* Returns the geometric center of the flock.
		*/
		Location getNeighbourhoodCenter(const Boid *of);

		/**
		* Returns the average velocity of the flock.
		*/
		Velocity getNeighbourhoodAverageVelocity(const Boid *of);

	};


	ostream& operator<<(ostream& os, const Flock& g);

}
#endif
