#include <iostream>
#include "vsr_cga3D.h"
#include "vsr_xf.h"
#include "vsr_GLVimpl.h"

using namespace vsr;
using namespace vsr::cga3D;
using namespace glv;


struct MyApp : public App {

  void onDraw(){

  Vec v(1,0,0);


  Biv b = Bivector::xy;
  double theta = PIOVERTWO;

  Frame f;

  auto rotor = Gen::rot(b);

  Vec v1 = v.rot(b * theta / 2.0);


  Line lin = Vec(0,0,0).null() ^ Vec(0,1,0).null() ^ Inf(1);

  Draw(lin,0,1,0);

  Draw(v,1,0,0);
  Draw(v1,1,1,0);
  Draw(b,1,0,1);
  Draw(f);

    //Circle through 3 Points
    //static Circle circle = Ro::point(1,0,0) ^ Ro::point(0,1,0) ^ Ro::point(-1,0,0); ///< i.e. CXY(1)


    //Dual plane with Normal in Y direction
    //static DualPlane dualplane(0,1,0);// = Fl::plane(0,1,0);

    //Calculate their Intersection (which is the dual of the outer product of duals . . . )
    //auto pair = meet(circle,dualplane);  //<---- i.e. (circle.dual() ^ dualplane).dual();

    //Draw 'em with colors
    //Draw(circle,0,1,0);     //<-- Green
    //Draw(dualplane,0,0,1);  //<-- Blue
    //Draw(pair,1,0,0);  //<-- Red

    //Enable Mouse Control with 'G' 'R' and 'S' keys
    Touch( interface, v);

    //text("use G, R and S keys and drag with mouse to Grab, Rotate and Scale the Circle");
  }

};

MyApp * myApp;

int main(){

  Vec v(1,0,0);
  Biv b = Bivector::xy;
  double theta = PIOVERTWO;
  auto rotor = Gen::rot(-b * theta / 2);
  Vec v1 = v.rot(b * theta / 2.0);

  auto b4x4 = Xf::mat(rotor);
  std::cout << b4x4 << std::endl;




  //GLV glv(0,0);

  //Window * win = new Window(800,500,"Versor",&glv);

  //myApp = new MyApp;
  //myApp -> init(win);

  //glv << *myApp;

  //Application::run();

  return 0;

}
