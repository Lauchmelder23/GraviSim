#include "PlanetManager.hpp"

std::map<uint32_t, Planet*> PlanetManager::planets;
uint32_t PlanetManager::planetCounter = 0;

Planet* PlanetManager::AddPlanet(const QPointF& position, float radius, const QColor& color, const QString& name)
{
	Planet* planet = new Planet(planetCounter, position, radius, color);
	planet->mass = rand() % 100;

	planets.insert(
		std::make_pair(
			planetCounter++,
			planet
		)
	);

	return planet;
}

void PlanetManager::RemovePlanet(uint32_t id)
{
	auto it = planets.find(id);
	if (it == planets.end())
		return;

	delete it->second;
	planets.erase(it);
}

Planet* PlanetManager::GetPlanet(uint32_t id)
{
	auto it = planets.find(id);
	if (it == planets.end())
		return nullptr;
	return it->second;
}

Planet* PlanetManager::GetLastPlanet()
{
	return planets.rbegin()->second;
}

void PlanetManager::RemoveLastPlanet()
{
	auto it = planets.cbegin();
	delete it->second;

	planets.erase(it);
}

Planet* PlanetManager::IsInPlanet(const QPointF& position)
{
	for (auto it : planets)
		if (it.second->IsInside(position))
			return it.second;
	
	return nullptr;
}

void PlanetManager::Update()
{
	for (auto planet : planets)
		planet.second->Update();

	// Collision detection && Gravitation
	for (auto planet : planets)
	{
		planet.second->acceleration = QPointF(0.f, 0.f);
		for (auto otherPlanet : planets)
		{
			if (planet == otherPlanet)
				continue;

			QPointF distance = planet.second->position - otherPlanet.second->position;
			float radiusSum = (planet.second->radius + otherPlanet.second->radius);
			float dist = distance.x() * distance.x() + distance.y() * distance.y();
			if (dist < radiusSum * radiusSum)
			{
				// Collision
				Planet* lighter = ((planet.second->mass > otherPlanet.second->mass) ? otherPlanet.second : planet.second);
				lighter->position += (radiusSum - sqrt(dist) + 1) * distance / sqrt(dist);
			}
			else
			{
				// Gravitation
				planet.second->acceleration -= 1000000 * (planet.second->mass * otherPlanet.second->mass) / pow(dist, 3.f / 2.f) * distance / sqrt(dist);
			}
		}

		planet.second->acceleration /= planet.second->mass;
	}
}

void PlanetManager::Render(QPainter& painter)
{
	for (auto it : planets)
		it.second->Draw(painter);
}
