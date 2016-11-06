#ifndef GENETIC_H_
#define GENETIC_H_
#include <string>
#include <vector>
using std::string;
using std::vector;
namespace genetic {
struct Chromosome {
  string bits;
  double fitness;
  double value;
};
extern vector<Chromosome> ChroPopulation;
extern vector<Chromosome> newpop;
extern double totalfitness;
extern double goal, cross, mutate;
extern int population, length, goodpointer;
extern bool solved;
void RunAlgorithm(double ingoal, int inpopulation, int inlength, double incross,
                  double inmutate);
void PrintGeneSymbole(int value);
string GenRandomBits();
void Solve(int pointer);
void SetFitness(int pointer);
int Roulette();
void Mutate(int pointer);
void Crossover(int a, int b);
double drand();

void DrawStats(int genoration);
bool SortFit(const Chromosome a, const Chromosome b);
void DrawEq(int pointer);
}
#endif
