#ifndef GENETIC_EVOLVE_H_
#define GENETIC_EVOLVE_H_
#include "genetic_core.h"
namespace genetic {
namespace evolve {
extern double totalfitness;
void GenorateBasePopulation();
void CalculateValues();
void CalculateFitness();
void Killoff();
void Reproduce();
void Mutate();
int SelectHigh();
int SelectLow();
void SumFitness();
void Sort();
bool SortCheck(const Chromosome a, const Chromosome b);
}
}
#endif
