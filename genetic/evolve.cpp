#include "../induco.h"
#include "display.h"
#include "evolve.h"
#include "genetic_core.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

void genetic::evolve::GenorateBasePopulation() {
  for (int i = 0; i < populationsize; i++) {
    Chromosome newchromosome;
    for (int j = 0; j < chromosomelength * 4; j++) {
      newchromosome.bits += std::to_string(rand() % 2);
    }
    population.push_back(newchromosome);
  }
}

void genetic::evolve::CalculateValues() {
  for (int i = 0; i < populationsize; i++) {
    std::string localbits = population[i].bits;
    bool loadoperator = false;
    int storedoperator = 0;
    double value = 0;
    for (int j = 0; j < localbits.size(); j += 4) {
      double bit = 0;
      for (int k = j; k < j + 4; k++) {
        bit = bit + pow(2, (3 - (k - j)));
      }
      if (bit < 10 && loadoperator == false) {
        if (storedoperator == 10) {
          value += bit;
        } else if (storedoperator == 11) {
          value -= bit;
        } else if (storedoperator == 12) {
          value *= bit;
        } else if (storedoperator == 13) {
          value /= bit;
        } else {
          value = bit;
        }
        loadoperator = true;
      } else if (bit > 9 && bit < 14 && loadoperator == true) {
        storedoperator = bit;
        loadoperator = false;
      }
    }
    population[i].value = value;
  }
}

void genetic::evolve::CalculateFitness() {
  for (int i = 0; i < populationsize; i++) {
    if (population[i].value == goalvalue) {
      population[i].fitness = 1000;
    } else {
      population[i].fitness =
          1 / std::fabs((double)(goalvalue - population[i].value));
    }
  }
}

void genetic::evolve::Killoff() {}

void genetic::evolve::Reproduce() {}

void genetic::evolve::Mutate() {
  for (int i = 0; i < populationsize; i++) {
    for (int j = 0; j < chromosomelength * 4; j++) {
      if (drand() < mutationrate) {
        if (population[i].bits[j] == '1') {
          population[i].bits[j] = '0';
        } else if (population[i].bits[j] == '0') {
          population[i].bits[j] = '1';
        }
      }
    }
  }
}
