#pragma once
#include "ParticleGenerator.h"
#include "../ParticleSystem.h"
#include <random>
#include <cmath>
#include <algorithm>

class GeneratorNormal : public ParticleGenerator
{
public:
	// meter los valores de media y desvSTD para del 0 al 1
	GeneratorNormal(ParticleSystem* sysRef, 
		physx::PxGeometryType::Enum geo, double spawnSpeed,
		double media, double desvStd, 
		Vector3 minDir, Vector3 maxDir,
		double minSpeed, double maxSpeed,
		double minSize, double maxSize,
		double minMass, double maxMass,
		Vector4 minColor, Vector4 maxColor);

	void spawnParticle() override;
private:
	double genRandomValue(double minValue, double maxValue);

	ParticleSystem* sysRef;
	physx::PxGeometryType::Enum geoType;

	double media, desvStd;
	double minSpeed, maxSpeed;
	Vector3 minDir, maxDir;
	double minSize, maxSize;
	double minMass, maxMass;
	Vector4 minColor, maxColor;

	std::random_device rd;
	std::mt19937 gen;
	std::normal_distribution<double> dist;
};

