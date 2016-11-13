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
extern double goalvalue, crossoverrate, mutationrate;
extern std::vector<Chromosome> population;
double RunAlgorithm(double gova = 0, int popsize = 100, int chrolength = 15,
                    double crossrate = 0.7, double mutrate = 0.001);
double drand();
void Clean();
}
#endif
