#ifndef GENETIC_GENETIC_CORE_H_
#define GENETIC_GENETIC_CORE_H_
#include <cmath>
#include <string>
#include <vector>
namespace genetic {
struct Chromosome {
  std::string bits;
  double value, fitness;
};
extern int populationsize, chromosomelength;
extern double goalvalue, crossoverrate, mutationrate;
extern std::vector<Chromosome> population;
double RunAlgorithm(int popsize = 100, int chrolength = 5, double gova = 729,
                    double crossrate = 0.7, double mutrate = 0.001);
double drand();
}
#endif
