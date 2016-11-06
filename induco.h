#ifndef INDUCO_H_
#define INDUCO_H_
#include <string>
#include <vector>
namespace induco {
int Menu(std::string title, std::vector<std::string> options);
double GetValue(std::string value);
std::string DisplayTime(double elapsed = 0, bool unit = false);
bool Pause();
void Line(int size);
void Break();
}
#endif
