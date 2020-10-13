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
	if (t_seekOrFlee == "seek")
	{
		//SEEK
		relevantLocation = t_target - t_seeker.getPos();
	}
	else if (t_seekOrFlee == "flee")
	{
		//FLEE
		relevantLocation = t_seeker.getPos() - t_target;
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

void AIController::pursue(Enemy& t_seeker, sf::Vector2f t_target)
{
}

void AIController::wander(Enemy& t_seeker)
{
	sf::Vector2f futureLocation;
	//Predict future location
	futureLocation.x = t_seeker.getVel().x * m_PREDICTED_LENGTH;
	futureLocation.y = t_seeker.getVel().y * m_PREDICTED_LENGTH;
	futureLocation = futureLocation + t_seeker.getPos();

	//Required Vel to future location
	t_seeker.setVelocity(futureLocation - t_seeker.getPos());

	//Apply Rotation
	t_seeker.setRotiation(t_seeker.getNewOrientation(t_seeker.getRotation(), t_seeker.getVel()));
	//Apply Rotation
	t_seeker.setRotiation(t_seeker.getRotation() + (t_seeker.getMaxRotation() * ((rand() % 2) - 0.5)));

	//set new Velocity
	t_seeker.setVelocity(sf::Vector2f(-std::sin(t_seeker.getRotation() * DEG_TO_RAD), std::cos(t_seeker.getRotation() * DEG_TO_RAD)) * t_seeker.getMaxForce());


}
