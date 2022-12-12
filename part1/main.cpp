#include <iostream>
#include "langmodel.h"
#include <sndfile.hh>

using namespace std;

constexpr size_t FRAMES_BUFFER_SIZE = 65536; // Buffer for reading/writing frames

int main(void)
{
langmodel x (5, 1,"File.txt");
}