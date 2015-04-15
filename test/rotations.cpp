#include <iostream>
#include "vsr_cga3D.h"

using namespace vsr;
using namespace vsr::cga3D;

int main(){

  Vec v(1,0,0);
  Biv b = Bivector::xy;
  double theta = PIOVERTWO;
  auto rotor = Gen::rot(-b * theta / 2);
  Vec v1 = v.rot(b * theta / 2.0);

  v1.print();

  return 0;

}
