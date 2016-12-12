#include "genetic/genetic_core.h"
#include "induco.h"
#include <iomanip>
#include <iostream>
#include <pessum.h>
#include <stdio.h>
#include <stdlib.h>
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
      induco::Echo(false);
      std::string goal = "", mutate = "", pop = "", length = "";
      bool entervalues = true;
      std::cout << "|      GOAL      |      POP       |     LENGTH     "
                   "|    MUTATE%     |\n";
      int selected = 0;
      char input = ' ';
      while (entervalues == true) {
        std::cout << "\r";
        std::string line = "|";
        std::string variable = goal;
        if (selected == 0) {
          variable = "[" + variable + "]";
        }
        while (variable.size() < 16) {
          variable = " " + variable;
        }
        line += variable + "|";
        variable = pop;
        if (selected == 1) {
          variable = "[" + variable + "]";
        }
        while (variable.size() < 16) {
          variable = " " + variable;
        }
        line += variable + "|";
        variable = length;
        if (selected == 2) {
          variable = "[" + variable + "]";
        }
        while (variable.size() < 16) {
          variable = " " + variable;
        }
        line += variable + "|";
        variable = mutate;
        // variable = std::to_string(int(input));
        if (selected == 3) {
          variable = "[" + variable + "]";
        }
        while (variable.size() < 16) {
          variable = " " + variable;
        }
        line += variable + "|";
        std::cout << line;
        std::cin >> input;
        if (int(input) == 68 && selected > 0) {
          selected--;
        } else if (int(input) == 67 && selected < 3) {
          selected++;
        } else if (int(input) <= 57 && int(input) >= 48) {
          if (selected == 0) {
            goal += input;
          }
          if (selected == 1) {
            pop += input;
          }
          if (selected == 2) {
            length += input;
          }
          if (selected == 3) {
            mutate += input;
          }
        } else if (int(input) == 127 || int(input) == 100) {
          std::string current = "";
          if (selected == 0 && goal.size() > 0) {
            goal.pop_back();
          }
          if (selected == 1 && pop.size() > 0) {
            pop.pop_back();
          }
          if (selected == 2 && length.size() > 0) {
            length.pop_back();
          }
          if (selected == 3 && mutate.size() > 0) {
            mutate.pop_back();
          }
        } else if (int(input) == 46) {
          if (selected == 0) {
            goal += '.';
          } else if (selected == 3) {
            mutate += '.';
          }
        } else if (int(input) == 113) {
          entervalues = false;
        }
      }
      induco::Break();
      double g, m;
      int p, l;
      if (goal == "") {
        goal = "-1";
      }
      if (mutate == "") {
        mutate = "-1";
      }
      if (pop == "") {
        pop = "-1";
      }
      if (length == "") {
        length = "-1";
      }
      g = std::stod(goal);
      m = std::stod(mutate);
      p = std::stoi(pop);
      l = std::stoi(length);
      genetic::RunAlgorithm(g, p, l, m);
      induco::Echo(true);
      induco::Break();
    }
  }
  pessum::TerminatePessumComponents();
  return (1);
}
