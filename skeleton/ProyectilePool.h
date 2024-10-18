#pragma once
#include "Proyectile.h"

class ProyectilePool {
public:
	Proyectile* getProyectile(Vector3 Pos, Vector3 Vel, float mass,
		float size = 1, Vector4 color = Vector4(1, 1, 1, 1)) {
		Proyectile* p = new Proyectile(Pos, Vel, PxGeometryType::Enum::eSPHERE, mass, size, color);
		pool.push_back(p);
		return p;
	}

	void freeProyectile(Proyectile* p) {
		auto it = std::remove_if(pool.begin(), pool.end(),
			[p](Proyectile* proj) { return proj == p; });
		pool.erase(it, pool.end());
	}

	void integrate(double t) {
		for (auto p : pool)
			p->integrate(t);
	}
private:
	std::vector<Proyectile*> pool;
};
