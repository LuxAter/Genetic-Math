#ifndef GENETIC_DISPLAY_H_
#define GENETIC_DISPLAY_H_
#include "genetic_core.h"
namespace genetic {
namespace display {
void DrawStats(bool firstcall = false);
void DrawEquation(int pointer = 0, bool nulls = false, bool index = false);
void DrawEquation(Chromosome chromo, bool nulls = false);
void DrawChromosome(int pointer = 0, bool index = false);
void DisplayAll(bool chromosome = false, bool equation = false,
                bool fitness = false, bool compfitness = false,
                bool nulls = false);
}
}
#endif
