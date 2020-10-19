#include "AIController.h"

AIController::AIController()
{
}

AIController::~AIController()
{
}

void AIController::seekOrFlee(Enemy& t_seeker, sf::Vector2f t_target, std::string t_seekOrFlee)
{
	sf::Vector2f relevantLocation;
	if (t_seekOrFlee == "Seek")
	{
		//SEEK
		relevantLocation = t_target - t_seeker.getPos();
		t_seeker.setText("Seek");
	}
	else if (t_seekOrFlee == "flee")
	{
		//FLEE
		relevantLocation = t_seeker.getPos() - t_target;
		t_seeker.setText("Flee");
	}
	else if (t_seekOrFlee == "Wander")
	{
		//SEEK with wander
		t_seeker.setText("Wander");
		relevantLocation = t_target - t_seeker.getPos();
	}
	else if (t_seekOrFlee == "Pursue")
	{
		t_seeker.setText("Pursue");
		relevantLocation = t_target - t_seeker.getPos();
	}

	//Unit vector
	relevantLocation = m_vectorMaths.unitVec(relevantLocation);

	//Scale to Speed
	relevantLocation = relevantLocation * t_seeker.getSpeed();

	//Subtract velocity from desiered
	sf::Vector2f steering = relevantLocation + t_seeker.getVel();

	//Limit Max force
	float magnitudeSteering = m_vectorMaths.magnitude(steering);
	if (magnitudeSteering > t_seeker.getMaxForce())
	{
		sf::Vector2f unitSteering = steering / magnitudeSteering;
		steering = unitSteering * t_seeker.getMaxForce();
	}

	//Apply Rotation
	t_seeker.setRotiation(t_seeker.getNewOrientation(t_seeker.getRotation(), steering));

	//Apply Steering
	t_seeker.setVelocity(steering);
}

void AIController::arrive(Enemy& t_seeker, sf::Vector2f t_target)
{
	t_seeker.setText("Arrive");
	sf::Vector2f relevantLocation;

	relevantLocation = t_target - t_seeker.getPos();

	//Inverse max speed with distance to target
	if (m_vectorMaths.magnitude(relevantLocation) > 300)
	{
		t_seeker.setMaxForce(10);
	}
	else if (m_vectorMaths.magnitude(relevantLocation) < 300)
	{
		t_seeker.setMaxForce(10 * (m_vectorMaths.magnitude(relevantLocation) / 300));
	}

	//Unit vector
	relevantLocation = m_vectorMaths.unitVec(relevantLocation);

	//Scale to Speed
	relevantLocation = relevantLocation * t_seeker.getSpeed();

	//Subtract velocity from desiered
	sf::Vector2f steering = relevantLocation + t_seeker.getVel();

	//Limit Max force
	float magnitudeSteering = m_vectorMaths.magnitude(steering);

	if (magnitudeSteering > t_seeker.getMaxForce())
	{
		sf::Vector2f unitSteering = steering / magnitudeSteering;
		steering = unitSteering * t_seeker.getMaxForce();
	}

	//Apply Rotation
	t_seeker.setRotiation(t_seeker.getNewOrientation(t_seeker.getRotation(), steering));

	//Apply Steering
	t_seeker.setVelocity(steering);
}

void AIController::pursue(Enemy& t_seeker, Player t_target)
{
	
	//direction = target.position - my.position
	sf::Vector2f relevantLocation;
	relevantLocation = t_target.getPos() - t_seeker.getPos();

	//	distance = direction.length
	float distance = m_vectorMaths.magnitude(relevantLocation);

	//	speed = my.velocity.length
	float speed = m_vectorMaths.magnitude(t_seeker.getVel());
	float timePrediction;
	//	if speed <= distance / maxTimePrediction:
	if (speed <= distance / m_MAX_TIME_PREDICTION)
	{
		//timePrediction = maxTimeprediction
		timePrediction = m_MAX_TIME_PREDICTION;
	}
	else
	{
		//	else:
		//timePrediction = distance / speed
		timePrediction = distance / speed;
	}
	//	newtarget.position = target.position + target.velocity * timePrediction
	sf::Vector2f newTargetPos = t_target.getPos() + t_target.getVel() * timePrediction;

	arrive(t_seeker, newTargetPos);

}

void AIController::wander(Enemy& t_seeker)
{
	//Randomize the rotation
	float num = (rand() % 3) - 1;
	m_wanderOrientation += t_seeker.getMaxRotation() * ((num));

	//Target Orientation as a vector
	float targetOrientation = m_wanderOrientation + t_seeker.getRotation();

	if (targetOrientation >= 360.0)
	{
		targetOrientation = 0;
	}

	sf::Vector2f oriVec;
	oriVec.x =  (cos(targetOrientation) * RAD_TO_DEG ) ; 
	oriVec.y =  (sin(targetOrientation)  * RAD_TO_DEG )  ;


	//Predict future location
	sf::Vector2f futureLocation;
	futureLocation = t_seeker.getPos() + m_vectorMaths.unitVec(t_seeker.getVel()) * m_PREDICTED_LENGTH;

	futureLocation += m_WANDER_RADIUS * oriVec;
	
	seekOrFlee(t_seeker, futureLocation, "Wander");

}
