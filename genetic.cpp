
#include "genetic.h"
#include "induco.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using std::string;

namespace genetic {
std::vector<Chromosome> ChroPopulation;
std::vector<Chromosome> newpop;
double totalfitness;
double goal, cross, mutate;
int population, length, goodpointer;
bool solved;
}

void genetic::RunAlgorithm(double ingoal, int inpopulation, int inlength,
                           double incross, double inmutate) {
  if (ingoal == 0 && inpopulation == 0 && inlength == 0 && incross == 0 &&
      inmutate == 0) {
    ingoal = 1000;
    inpopulation = 100;
    inlength = 20;
    incross = 0.7;
    inmutate = 0.001;
  }
  goal = ingoal;
  population = inpopulation;
  length = inlength;
  cross = incross;
  mutate = inmutate;
  ChroPopulation.clear();
  newpop.clear();
  totalfitness = 0;
  goodpointer = -1;
  solved = false;
  int genorations = 0;
  for (int i = 0; i < population; i++) {
    Chromosome newchromosome;
    newchromosome.bits = GenRandomBits();
    newchromosome.value = 0;
    newchromosome.fitness = 0;
    ChroPopulation.push_back(newchromosome);
  }
  std::cout << goal << "\n";
  std::cout << "GENORATION|    BEST    |  AVERAGE   |    WORST   \n";
  while (solved == false) {
    totalfitness = 0;
    if (genorations > 2000) {
      break;
    }
    for (int i = 0; i < population; i++) {
      Solve(i);
      SetFitness(i);
    }
    genorations++;
    std::sort(ChroPopulation.begin(), ChroPopulation.end(), SortFit);
    DrawStats(genorations);
    if (solved == true) {
      break;
    }
    newpop.clear();
    while (newpop.size() < population) {
      Crossover(Roulette(), Roulette());
    }
    for (int i = 0; i < newpop.size(); i++) {
      Mutate(i);
    }
    ChroPopulation.clear();
    ChroPopulation = newpop;
    newpop.clear();
  }
  if (solved == true) {
    DrawEq(0);
  }
}
void genetic::PrintGeneSymbole(int value) {}
string genetic::GenRandomBits() {
  string bits = "";
  for (int i = 0; i < length; i++) {
    std::string gene = "";
    for (int j = 0; j < 4; j++) {
      if (rand() % 2 == 0) {
        gene = gene + "1";
      } else {
        gene = gene + "0";
      }
    }
    bits = bits + gene;
  }
  return (bits);
}
void genetic::Solve(int pointer) {
  bool op = false;
  int storedop = 0;
  double result = 0;
  for (int i = 0; i < ChroPopulation[pointer].bits.size(); i += 4) {
    int bit = 0;
    for (int j = i; j < i + 4; j++) {
      if (ChroPopulation[pointer].bits[j] == '1') {
        bit = bit + pow(2, (3 - (j - i)));
      }
    }
    if (bit < 10 && op == false) {
      if (storedop == 0) {
        result = (double)bit;
      }
      if (storedop == 10) {
        result += (double)bit;
      }
      if (storedop == 11) {
        result -= (double)bit;
      }
      if (storedop == 12) {
        result *= (double)bit;
      }
      if (storedop == 13) {
        if (bit == 0) {
          result = 0;
        } else {
          result /= (double)bit;
        }
      }
      op = true;
    }
    if (bit >= 10 && bit <= 13 && op == true) {
      storedop = bit;
      op = false;
    }
  }
  if (result == goal) {
    solved = true;
    goodpointer = pointer;
  }
  ChroPopulation[pointer].value = result;
}
void genetic::SetFitness(int pointer) {
  if (ChroPopulation[pointer].value == goal) {
    ChroPopulation[pointer].fitness = 1000;
  } else {
    ChroPopulation[pointer].fitness =
        1 / std::fabs((double)(goal - ChroPopulation[pointer].value));
  }
  totalfitness += ChroPopulation[pointer].fitness;
}
int genetic::Roulette() {
  double slice = drand() * totalfitness;
  double fitnesssofar = 0;
  for (int i = 0; i < population; i++) {
    fitnesssofar += ChroPopulation[i].fitness;
    if (fitnesssofar >= slice) {
      return (i);
    }
  }
  return (ChroPopulation.size() - 1);
}
void genetic::Mutate(int pointer) {
  for (int i = 0; i < newpop[pointer].bits.size(); i++) {
    if (drand() < mutate) {
      if (newpop[pointer].bits[i] == '1') {
        newpop[pointer].bits[i] = '0';
      } else {
        newpop[pointer].bits[i] = '1';
      }
    }
  }
  if (drand() < (mutate / (double)10)) {
    string gene = "";
    for (int i = 0; i < 4; i++) {
      if (rand() % 2 == 0) {
        gene += "1";
      } else {
        gene += "0";
      }
    }
    newpop[pointer].bits = newpop[pointer].bits + gene;
  }
}
void genetic::Crossover(int a, int b) {
  if (drand() < cross) {
    int crosspoint = rand() % ChroPopulation[a].bits.size();
    if (crosspoint > ChroPopulation[b].bits.size()) {
      crosspoint = ChroPopulation[b].bits.size() - 1;
    }
    Chromosome t1, t2;
    t1.bits = ChroPopulation[a].bits.substr(0, crosspoint) +
              ChroPopulation[b].bits.substr(crosspoint,
                                            ChroPopulation[a].bits.size());
    t2.bits = ChroPopulation[b].bits.substr(0, crosspoint) +
              ChroPopulation[a].bits.substr(crosspoint,
                                            ChroPopulation[a].bits.size());
    t1.value = 0;
    t1.fitness = 0;
    t2.value = 0;
    t2.fitness = 0;
    newpop.push_back(t1);
    newpop.push_back(t2);
  }
}

double genetic::drand() { return (fabs((float)rand() / (RAND_MAX + 1))); }

void genetic::DrawStats(int genoration) {
  string line = "", value = "";
  value = std::to_string(genoration);
  while (value.size() > 10) {
    value.pop_back();
  }
  for (int i = value.size(); i < 10; i++) {
    line = line + " ";
  }
  line = line + value + "|";
  value = std::to_string(ChroPopulation[0].value);
  while (value.size() > 12) {
    value.pop_back();
  }
  for (int i = value.size(); i < 12; i++) {
    line = line + " ";
  }
  line = line + value + "|";
  double averagesum = 0;
  for (int i = 0; i < ChroPopulation.size(); i++) {
    averagesum += ChroPopulation[i].value;
  }
  averagesum /= (double)population;
  value = std::to_string(averagesum);
  while (value.size() > 12) {
    value.pop_back();
  }
  for (int i = value.size(); i < 12; i++) {
    line = line + " ";
  }
  line = line + value + "|";
  value = std::to_string(ChroPopulation[ChroPopulation.size() - 1].value);
  while (value.size() > 12) {
    value.pop_back();
  }
  for (int i = value.size(); i < 12; i++) {
    line = line + " ";
  }
  line = line + value + "\n";
  std::cout << line;
}

bool genetic::SortFit(const Chromosome a, const Chromosome b) {
  return a.fitness > b.fitness;
}

void genetic::DrawEq(int pointer) {
  int result = 0, storedop = -1;
  bool op = false;
  for (int i = 0; i < ChroPopulation[pointer].bits.size(); i += 4) {
    int bit = 0;
    for (int j = i; j < i + 4; j++) {
    }
    for (int j = i; j < i + 4; j++) {
      if (ChroPopulation[pointer].bits[j] == '1') {
        bit = bit + pow(2, (3 - (j - i)));
        int temp = (3 - (j - i));
        temp = pow(2, temp);
      }
    }
    if (bit < 10 && op == false) {
      if (storedop == -1) {
        std::cout << bit;
      }
      if (storedop == 10) {
        std::cout << "+" << bit;
      }
      if (storedop == 11) {
        std::cout << "-" << bit;
      }
      if (storedop == 12) {
        std::cout << "*" << bit;
      }
      if (storedop == 13) {
        std::cout << "/" << bit;
      }
      op = true;
    } else if (bit >= 10 && bit <= 13 && op == true) {
      storedop = bit;
      op = false;
    } else {
      // std::cout << "[" << bit << "]";
    }
  }
  std::cout << "=" << ChroPopulation[pointer].value << "\n";
}
