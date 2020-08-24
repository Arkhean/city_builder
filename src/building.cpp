#include "building.hpp"

int building_size(int type){
    switch (type) {
        case WELL:
        case FOUNTAIN:
        case DOCTOR:
        case BARBER:
        case PREFET:
            return 1;
        case UNIVERSITY:
        case CASERN:
        case HOSPITAL:
        case WAREHOUSE:
            return 3;
        case COLISEUM:
        case SENATE:
            return 4;
        default:
            return 2;
    }
}

std::string names[] = {"Marché", "Ferme", "Mine de fer", "Puits d'argile",
                    "Cabane de bûcheron", "Ecole", "Université", "Atelier de vin",
                    "Atelier d'huile", "Atelier de meubles", "Théâtre", "Colisée",
                "Sénat", "Préfecture", "Fort", "Caserne", "Barbier", "Médecin",
                "Thermes", "Hôpital", "Temple", "Temple", "Temple", "Temple",
                "Temple", "Oracle", "Pêcherie", "Pêcherie", "Pêcherie", "Pêcherie",
                "Puits", "Fontaine", "Entrepôt"};
int maintenance_costs[] = { 100,100,100,100,100,100,100,100,100,100,100,100,100,
                100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
            100,100,100,100 };

Building::Building(int type, int i, int j)
        : type(type), i(i), j(j), name(names[type]), maintenance_cost(maintenance_costs[type]) {}

Service_building::Service_building(int type, int i, int j, int range)
        : Building(type, i, j), range(range) {}
