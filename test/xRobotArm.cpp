#include "vsr_cga3D.h"
#include "vsr_GLVimpl.h"
#include "vsr_chain.h"


using namespace vsr;
using namespace glv;
using namespace vsr::cga3D;

struct MyApp : App {

	float amt,linewidth;
	Chain k;
   // Frame baseFrame, targetFrame, secondFrame, finalFrame;
	Pnt targetPos;
	float distA;


	MyApp(Window * win) : App(win),
	k(5)
	{
   // colors().back.set(1,1,1);
  }

	virtual void initGui(){
      gui(distA, "LinkLength", 1,10);
      gui(linewidth,"linewidth",0,10);
     	distA = 5.0;
      linewidth=3;

	}

	void onDraw(){

    glLineWidth(linewidth);

		Frame baseFrame;

  		//Target: Mouse Position

    auto line =  Fl::line( interface.mouse.projectNear, interface.vd().ray );
		targetPos = Ro::point( line, Ori(1) );

		Frame targetFrame ( targetPos );

		Draw(targetPos, 1,0,0);


    Frame secondFrame( 0, distA, 0 );

   // Make a sphere from a point and a radius, calls Ro::dls( Pnt, float )
	 auto firstSphere = Ro::sphere( secondFrame.pos(), distA );
   auto targetSphere = Ro::sphere( targetPos, distA );

		 //Plane of Rotation formed by yaxis of base and target point
		 auto rotationPlane = baseFrame.ly() ^ targetPos;

		 Draw(rotationPlane,0,1,0);

 		//XZ plane of Target
		 Dlp targetXZ = targetFrame.dxz();
		 Draw(targetXZ,0,.5,1);

		 //Line of Target
		 Dll tline = targetXZ ^ rotationPlane.dual();
		 Draw(tline,1,1,0);

		 //Point Pairs of Final joint
		 Pair fjoint = ( tline ^ targetSphere ).dual();
		 Draw(fjoint);

 	   	 //Pick the one closest to the base frame
		 Frame finalFrame ( Ro::split(fjoint,false), Rot(1,0,0,0) );

		 //Sphere around fframe
		 auto ffsphere = Ro::sphere( finalFrame.pos(), distA);

		 //Circle of Possibilities
		 Circle cir = ( ffsphere ^ firstSphere).dual();
		 Draw(cir,.5,1,1);

		 //TWo points where the middle joint could be
		 Pair fpair = ( rotationPlane.dual() ^ cir.dual() ).dual();
		 Draw(fpair, 1,.5,.5);

		 //Pick One and put the middle frame there
		 Frame middleFrame( Ro::split(fpair,true) );


		 //We can store the `positions in a chain class which will sort out relative orientations for us
		 k[0] = baseFrame;
		 k[1] = secondFrame;
		 k[2] = middleFrame;
		 k[3] = finalFrame;
		 k[4] = targetFrame;

		 //Base Frame will rotate to plane defined by its yaxis and target point
		 Rot r1 =  Gen::ratio( Vec::z, rotationPlane.dual().runit() );
		 k[0].rot( r1 );

		 //for all the other frames, calculate joint rotations and link lengths from current positions
		 k.calcJoints(1);
		 k.links();



		 for (int i = 0; i < 4; ++i){

			 glColor3f(0,1,0);
			 gfx::Glyph::Line( k[i].pos(), k[i+1].pos() );

		     Draw(k[i]);
		 }


		 Draw(ffsphere,1,0,0,.4);
		 Draw(firstSphere,1,0,0,.4);
	}
};

MyApp * myApp;

int main(){


	GLV glv(0,0);

	Window * win = new Window(500,500,"Versor",&glv);

	myApp = new MyApp(win);
	myApp -> initGui();

	glv << *myApp;

	Application::run();

	return 0;

}














