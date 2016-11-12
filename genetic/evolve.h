#ifndef GENETIC_EVOLVE_H_
#define GENETIC_EVOLVE_H_
namespace genetic {
namespace evolve {
void GenorateBasePopulation();
void CalculateValues();
void CalculateFitness();
void Killoff();
void Reproduce();
void Mutate();
}
}
#endif
