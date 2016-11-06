#include "genetic.h"
#include "induco.h"
#include <iomanip>
#include <iostream>
#include <pessum.h>
#include <string>
#include <vector>
int main(int argc, char *argv[]) {
  srand(time(NULL));
  std::cout << std::setprecision(10);
  bool running = true;
  pessum::InitializePessumComponents();
  int input = 0;
  std::vector<std::string> options = {"Quit Program", "Genetic Solve"};
  while (running == true) {
    input = induco::Menu("Maze Systems", options);
    if (input == 1) {
      running = false;
    }
    if (input == 2) {
      induco::Break();
      double value = induco::GetValue("Value To Solve For(...)");
      int population = induco::GetValue("Population Size(10-100)");
      int length = induco::GetValue("Chromosome Length(5-10)");
      double crossover = induco::GetValue("Cross Over Rate  (0.70)");
      double mutate = induco::GetValue("Mutation Rate   (0.001)");
      genetic::RunAlgorithm(value, population, length, crossover, mutate);
      induco::Break();
    }
  }
  pessum::TerminatePessumComponents();
  return (1);
}
