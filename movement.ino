#include <BasicLinearAlgebra.h>
using namespace BLA;


float rl = 0;
float fh = 1;
float kh = 0;
float kr = 0.1;


void setup() {
Serial.begin(115200);


BLA::Matrix<4,4> A;
A = {1, -1, -1, 1, 1, 1, 1, 1, 1, 1, -1, -1, 1, -1, 1, -1};
Matrix<4> b = {rl,fh, kh, kr};
auto A_inv = A;
Invert(A_inv);
Matrix<4> Motors = A_inv * b;
Serial << "x (via inverse A): " << Motors;


}


void loop() {
 


}


