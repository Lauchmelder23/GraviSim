#pragma once

#include <map>

#include <QPointF>

#include "Planet.hpp"

class PlanetManager
{
public:
	PlanetManager() = delete;

	static Planet* AddPlanet(const QPointF& position, float radius, const QColor& color, 
		const QString& name = "Unnamed");
	static void RemovePlanet(uint32_t id);

	static Planet* GetPlanet(uint32_t id);
	static Planet* GetLastPlanet();
	static void RemoveLastPlanet();

	static Planet* IsInPlanet(const QPointF& position);

	static void Update();
	static void Render(QPainter& painter);

private:
	static std::map<uint32_t, Planet*> planets;
	static uint32_t planetCounter;
};