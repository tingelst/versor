#include <iostream>
#include "vsr_cga3D.h"
#include "vsr_xf.h"

using namespace vsr;
using namespace vsr::cga3D;

int main(){

  Vec v(1,0,0);
  Biv b = Bivector::xy;
  double theta = PIOVERTWO;
  auto rotor = Gen::rot(-b * theta / 2);
  Vec v1 = v.rot(b * theta / 2.0);

  auto b4x4 = Xf::mat(rotor);
  std::cout << b4x4 << std::endl;

  return 0;

}
