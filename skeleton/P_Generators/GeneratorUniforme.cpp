#include "GeneratorUniforme.h"


GeneratorUniforme::GeneratorUniforme(ParticleSystem* sysRef, physx::PxGeometryType::Enum geoType, double spawnSpeed,
	Vector3 minDir, Vector3 maxDir, double minSpeed, double maxSpeed,
	double minSize, double maxSize, double minMass, double maxMass, 
	Vector4 minColor, Vector4 maxColor)
	: ParticleGenerator(spawnSpeed) {
	this->sysRef = sysRef;
	this->geoType = geoType;

	this->minSpeed = minSpeed;
	this->maxSpeed = maxSpeed;

	this->minDir = minDir;
	this->maxDir = maxDir;

	this->minSize = minSize;
	this->maxSize = maxSize;

	this->minMass = minMass;
	this->maxMass = maxMass;

	this->minColor = minColor;
	this->maxColor = maxColor;

	gen = std::mt19937(rd());
	dist = std::uniform_real_distribution<double>(0, 1);
}

void GeneratorUniforme::spawnParticle() {
	double rndSpeed = minSpeed != maxSpeed ? genRandomValue(minSpeed, maxSpeed) : minSpeed;

	double rndDirX = minDir.x != maxDir.x ? genRandomValue(minDir.x, maxDir.x) : minDir.x;
	double rndDirY = minDir.y != maxDir.y ? genRandomValue(minDir.y, maxDir.y) : minDir.y;
	double rndDirZ = minDir.z != maxDir.z ? genRandomValue(minDir.z, maxDir.z) : minDir.z;
	Vector3 rndDir = Vector3(rndDirX, rndDirY, rndDirZ);
	rndDir.normalize();

	double rndSize = minSize != maxSize ? genRandomValue(minSize, maxSize) : minSize;

	double rndMass = minMass != maxMass ? genRandomValue(minMass, maxMass) : minMass;

	double rndColorX = minColor.x != maxColor.x ? genRandomValue(minColor.x, maxColor.x) : minColor.x;
	double rndColorY = minColor.y != maxColor.y ? genRandomValue(minColor.y, maxColor.y) : minColor.y;
	double rndColorZ = minColor.z != maxColor.z ? genRandomValue(minColor.z, maxColor.z) : minColor.z;
	double rndColorW = minColor.w != maxColor.w ? genRandomValue(minColor.w, maxColor.w) : minColor.w;
	Vector4 rndColor = Vector4(rndColorX, rndColorY, rndColorZ, rndColorW);

	sysRef->AddParticle(new Particle(sysRef->getOrigin(), rndSpeed * rndDir,
		geoType, rndSize, rndMass, rndColor));
}

double GeneratorUniforme::genRandomValue(double minValue, double maxValue)
{
	double valor = dist(gen);

	// clamp
	if (valor < 0) { valor = 0; }
	else if (valor > 1) { valor = 1; }

	return (minValue + valor * (maxValue - minValue));
}