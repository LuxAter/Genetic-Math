#ifndef GENETIC_GENETIC_CORE_H_
#define GENETIC_GENETIC_CORE_H_
#include <cmath>
#include <string>
#include <vector>
namespace genetic {
struct Chromosome {
  std::string bits;
  double value, fitness, cumulativefitness, bottemup;
};
extern int populationsize, chromosomelength, genoration;
extern double goalvalue, mutationrate;
extern std::vector<Chromosome> population;
double RunAlgorithm(double gova = -1, int popsize = -1, int chrolength = -1,
                    double mutate = -1);
double drand();
void Clean();
}
#endif
