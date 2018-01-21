#include <cmath>
#include "Steering.h"

namespace Flocking {
	void Seek::getSteering(SteeringResult* output)
	{
		// First work out the direction
		output->linear_acceleration = *target;
		output->linear_acceleration -= pboid->position;
		
		// If there is no direction, do nothing
		if (output->linear_acceleration.squareMagnitude() > 0)
		{
			output->linear_acceleration.Normalize();
			output->linear_acceleration *= maxAcceleration;
		}
	}
	
	void Flee::getSteering(SteeringResult* output)
	{
		// First work out the direction
		output->linear_acceleration = pboid->position;
		output->linear_acceleration -= *target;
		
		// If there is no direction, do nothing
		if (output->linear_acceleration.squareMagnitude() > 0)
		{
			output->linear_acceleration.Normalize();
			output->linear_acceleration *= maxAcceleration;
		}
	}
	
	
	
	void Separation::getSteering(SteeringResult* output)
	{
		// Get the neighbourhood of boids
		unsigned count = theFlock->prepareNeighourhood(pboid, neighbourhoodRay);
		if (count <= 0) return;
		
		// Work out their center of mass
		Location cofm = theFlock->getNeighbourhoodCenter(pboid);
		
		// Steer away from it.
		flee.maxAcceleration = maxAcceleration;
		flee.pboid = pboid;
		flee.target = &cofm;
		flee.getSteering(output);
		if (isnan(output->linear_acceleration.x) || isnan(output->linear_acceleration.y)) {
			cout <<*(flee.pboid)<<endl;
			cout<<*(flee.target)<<endl;
			error("lin_acc sep",vector<double>{1.0,2});
		}
	}
	
	void Cohesion::getSteering(SteeringResult* output)
	{
		// Get the neighbourhood of boids
		unsigned count = theFlock->prepareNeighourhood(pboid, neighbourhoodRay);
		if (count <= 0) return;
		
		// Work out their center of mass
		Location cofm = theFlock->getNeighbourhoodCenter(pboid);
		
		// Steer away from it.
		seek.maxAcceleration = maxAcceleration;
		seek.pboid = pboid;
		seek.target = &cofm;
		seek.getSteering(output);
		if (isnan(output->linear_acceleration.x) || isnan(output->linear_acceleration.y)) {
			error("lin_acc coh",vector<double>{1.0,2});
		}
	}
	
	void VelocityMatch::getSteering(SteeringResult* output)
	{
		// Get the neighbourhood of boids
		unsigned count = theFlock->prepareNeighourhood(pboid, neighbourhoodRay	);
		if (count <= 0) return;
		
		// Work out their center of mass
		Velocity vel = theFlock->getNeighbourhoodAverageVelocity(pboid);
		
		// Try to match it
		output->linear_acceleration = vel - pboid->velocity;
		if (output->linear_acceleration.squareMagnitude() > maxAcceleration*maxAcceleration)
		{
			output->linear_acceleration.Normalize();
			output->linear_acceleration *= maxAcceleration;
		}
			if (isnan(output->linear_acceleration.x) || isnan(output->linear_acceleration.y)) {
			error("lin_acc vel",vector<double>{1.0,2});
		}
	}
	
	
	
	void BlendedSteering::getSteering(SteeringResult *steer_res)
	{
		// Clear the output to start with
		steer_res->linear_acceleration.clear();
		
		// Go through all the behaviours in the list
		std::vector<BehaviourAndWeight>::iterator baw;
		double totalWeight = 0;
		SteeringResult temp;
		for (BehaviourAndWeight &baw : behaviours)
		{
			// Make sure the children's character is set
			baw.behaviour->pboid = pboid;
			
			// Get the behaviours steering and add it to the accumulator
			baw.behaviour->getSteering(&temp);
			steer_res->linear_acceleration += temp.linear_acceleration * baw.weight;
			//output->angular += temp.angular * baw->weight;
			
			totalWeight += baw.weight;
		}
		if (isnan(steer_res->linear_acceleration.x) || isnan(steer_res->linear_acceleration.y)) {
			error("lin_acc",vector<double>{1.0,2});
		}
		// Divide the accumulated output by the total weight
		if (totalWeight > 0.0)
		{
			totalWeight = (double)1.0 / totalWeight;
			steer_res->linear_acceleration *= totalWeight;
			//output->angular *= totalWeight;
		}
	}
	
}