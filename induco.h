#ifndef INDUCO_H_
#define INDUCO_H_
#include <string>
#include <termios.h>
#include <vector>
namespace induco {
extern struct termios t;
int Menu(std::string title, std::vector<std::string> options);
double GetValue(std::string value);
std::string SGetValue(std::string value);
std::string DisplayTime(double elapsed = 0, bool unit = false);
bool Pause();
void Line(int size);
void Break();
void Echo(bool setting);
}
#endif
