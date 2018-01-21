#ifndef STEERING_H
#define STEERING_H

#include <vector>
#include "Vector2D.h"
#include "Flock.h"

using namespace  std;
using namespace Flocking;

namespace Flocking {

	
	class SteeringBehaviour
	{
	public:
		/**
		* The character who is moving.
		*/
		Boid *pboid;
		
		/**
		* Works out the desired steering and writes it into the given
		* steering output structure.
		*/
		virtual void getSteering(SteeringResult* output) = 0;
	};
	
	
	/**
	* The seek steering behaviour takes a target and aims right for
	* it with maximum acceleration.
	*/
	class Seek : public SteeringBehaviour
	{
	public:
		/**
		* The target may be any vector (i.e. it might be something
			* that has no orientation, such as a point in space).
			*/
			const Location *target;
			
			/**
			* The maximum acceleration that can be used to reach the
			* target.
			*/
			double maxAcceleration;
			
			/**
			* Works out the desired steering and writes it into the given
			* steering output structure.
			*/
			virtual void getSteering(SteeringResult* output);
		};
		
		/**
		* The seek steering behaviour takes a target and aims in the
		* opposite direction with maximum acceleration.
		*/
		class Flee : public Seek
		{
		public:
			/**
			* Works out the desired steering and writes it into the given
			* steering output structure.
			*/
			virtual void getSteering(SteeringResult* output);
		};
		
		
		class BoidSteeringBehaviour : public SteeringBehaviour
		{
		public:
			Flock *theFlock;
			
			double neighbourhoodRay;
			double maxAcceleration;
		};
		
		class Separation : public BoidSteeringBehaviour
		{
			Flee flee;
			
		public:
			virtual void getSteering(SteeringResult* output);
		};
		
		class Cohesion : public BoidSteeringBehaviour
		{
			Seek seek;
			
		public:
			virtual void getSteering(SteeringResult* output);
		};
		
		class VelocityMatch : public BoidSteeringBehaviour
		{
		public:
			virtual void getSteering(SteeringResult* output);
		};
		
		class BlendedSteering : public SteeringBehaviour
		{
		public:
			/**
			* Holds a steering behaviour with its associated weight.
			*/
			struct BehaviourAndWeight
			{
				SteeringBehaviour *behaviour;
				double weight;
				
				BehaviourAndWeight(SteeringBehaviour *behaviour, double weight=(double)1.0)
				:
				behaviour(behaviour), weight(weight)
				{}
				};
				
				/**
				* Holds the list of behaviour and their corresponding blending
				* weights.
				*/
				vector<BehaviourAndWeight> behaviours;
				
				/**
				* Works out the desired steering and writes it into the given
				* steering output structure.
				*/
				virtual void getSteering(SteeringResult* output);
			};
			
		}

#endif