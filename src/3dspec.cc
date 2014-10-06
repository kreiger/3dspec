/************************************************************************
*                                                                       *
*                                                                       *
*                                                                       *
*                        Kreiger's Specialarbete                        *
*                                                                       *
*                                                                       *
*                                                                       *
************************************************************************/

#include "3dspec.h"	//Inkludera definitionsfilen

Object **objs;		//Deklarera en lista p� pekare till Objekt
int num_objs=0;		//Deklarera en r�knare som h�ller reda p� antalet objekt
BITMAP *scr;		//Deklarera en pekare till en bit minnesomr�de, som man kan skriva till

using namespace std ;

void initialize()	//Initialiseringsrutinen
{
	allegro_init();					//Initialisera Allegro
	install_keyboard();				//Initialisera Allegros Tangentbordsrutiner
	install_timer();				//Initialisera Allegros Timerrutiner
	install_mouse();				//Initialisera Allegros Musrutiner
	set_color_depth(COLDEPTH);			//S�tt f�rgdjupet
	set_gfx_mode(SCRMODE,SCRWIDTH,SCRHEIGHT,0,0);	//Byt sk�rml�ge
	scr = create_bitmap(SCRWIDTH,SCRHEIGHT);	//Allokera minnesomr�de f�r en tempor�r sk�rm
}

int main (int argc, char **argv)
{
  if (argc < 2)	//Om man inte har angett en objektfil
  {
    cout << "Kreiger's specialarbete! Version: "<< VER << " Build: "<< BUILD << endl; 
    cout << "Syntax:" << endl << "3DSPEC <objfile.off>" << endl;
    exit (1);
  }

  objs = new (Object *)[argc-1];	//Allokera minne f�r objektpekarna

  for (int foo=1;argv[foo];foo++)	//L�s in objektfilerna
    if (load_off (argv[foo],foo-1))
      num_objs++;
    else
      exit (1);

  initialize();				//Anropa initialiseringsrutinen

  Entity eye(0,0,-50);			//Skapar ett �ga, och s�tter dess koordinater

  Matrix<float> RotMatX(3,3);		//Skapar rotationsmatriser
  Matrix<float> RotMatY(3,3);
  Matrix<float> RotMatZ(3,3);
  Matrix<float> Result(3,3);

  RotMatX.Unit();			//G�r rotationsmatriserna till enhetsmatriser
  RotMatY.Unit();
  RotMatZ.Unit();

  Vector tmp1,p1;			//Skapar tv� tempor�ra vektorer

  long int frames=0;			//Skapar en variabel som h�ller reda p� antal framess
  float t = time(0);			//Skapar en variabel som h�ller reda p� tiden

  while (1)				//K�r en o�ndlig loop
  {
    for (int foo=0;foo<num_objs;foo++)	//F�r varje objekt, g�r f�ljande:
    {

	//R�kna ut rotationsmatriserna
      RotMatX[1][1] = RotMatX[2][2] = cos(objs[foo]->avelocity[0]);
      RotMatX[2][1] = -(RotMatX[1][2] = sin(objs[foo]->avelocity[0]));
      RotMatY[2][2] = RotMatY[0][0] = cos(objs[foo]->avelocity[1]);
      RotMatY[2][0] = -(RotMatY[0][2] = sin(objs[foo]->avelocity[1]));
      RotMatZ[1][1] = RotMatZ[0][0] = cos(objs[foo]->avelocity[2]);
      RotMatZ[1][0] = -(RotMatZ[0][1] = sin(objs[foo]->avelocity[2]));

	//Multiplicera ihop rotationsmatriserna
      objs[foo]->angles=Result=RotMatX*RotMatY*RotMatZ*objs[foo]->angles;
      
      for (int bar=0;bar<objs[foo]->num_verts;bar++)				//F�r varje vertex i objektet
      {
        objs[foo]->verts[bar]=objs[foo]->origverts[bar]*Result;  		//Rotera
      }
      for (int bar=0;bar<objs[foo]->num_polys;bar++)				//F�r varje polygon i objektet
      {
        objs[foo]->polys[bar].normal=objs[foo]->polys[bar].orignormal*Result;  //Rotera normalen

        tmp1 = eye.origin-(objs[foo]->origin + objpolyvert(foo,bar,0));		//Vektorn mellan f�rsta vertexen och �gat
	tmp1.Normalize();							//Normera vektorn

        float dot = ((tmp1) | eye.front());					//R�kna ut skal�rprodukten av vektorn och �gats "fram�tvektor"

        if (dot >= 0) continue;							//�r polygonen bakom �gat? I s� fall, g� till n�sta polygon

	dot = (tmp1 | objs[foo]->polys[bar].normal);				//R�kna ut skal�rprodukten av vektorn och polygonens normal
        if (dot < 0) continue; 							//�r polygonen bortv�nd?

	int col = (int)(dot*255);
	col = makecol(col,col,col); 						//Best�m f�rg p� polygonen med ledning av vinkeln mot den

	int nv=objs[foo]->polys[bar].num_verts;					//Placera antalet punkter i polygonen i en tempor�r variabel
	int p[nv*2];								//Allokera minne f�r sk�rm koordinaterna
        for (int baz=0;baz<nv;baz++)						//F�r varje punkt i polygonen
        {
          p1 = (objs[foo]->origin + objpolyvert(foo,bar,baz)) - eye.origin;	//Placera �gat i origo
	  p1*=eye.angles;							//Rotera punkten runt �gat

          p[baz*2] = (int)(HSCRW + HSCRW*(p1[0] / (p1[2])));	//Spara sk�rm-X och sk�rm-Y 
          p[baz*2+1] = (int)(HSCRH - HSCRW*(p1[1] / (p1[2])));
        }
	polygon(scr,nv,p,col);	//L�t allegro rita ut polygonen
      }
    }

    if (key[KEY_Q]) objs[0]->avelocity[0]+=OROT;	//L�s in knapptryckningar f�r rotation av objektet
    if (key[KEY_A]) objs[0]->avelocity[0]-=OROT;
    if (key[KEY_W]) objs[0]->avelocity[1]+=OROT;
    if (key[KEY_S]) objs[0]->avelocity[1]-=OROT;
    if (key[KEY_E]) objs[0]->avelocity[2]+=OROT;
    if (key[KEY_D]) objs[0]->avelocity[2]-=OROT;
    eye.avelocity.Clear();	//Nollst�ll �gats rotation

    int mx;
    int my;
    get_mouse_mickeys(&mx,&my);		//L�s in musen

    (eye.avelocity[1])+=(float)(mx)*0.001;	//�ka p� �gats rotationshastighet
    (eye.avelocity[0])+=(float)(my)*0.001;
    if (key[KEY_PGUP]) eye.avelocity[2]+=0.01;
    if (key[KEY_HOME]) eye.avelocity[2]-=0.01;

    if (mouse_b & 2) eye.origin += (eye.front());	//L�s in musknapparna
    if (mouse_b & 1) eye.origin -= (eye.front());	//Och flytta �gat d�refter
    if (key[KEY_RIGHT]) eye.origin += (eye.right()*0.1);
    if (key[KEY_LEFT]) eye.origin -= (eye.right()*0.1);
    if (key[KEY_UP]) eye.origin += (eye.up()*0.1);
    if (key[KEY_DOWN]) eye.origin -= (eye.up()*0.1);
 
    if (key[KEY_ESC]) break;	//Om anv�ndaren trycker ESC, avsluta o�ndlighetsloopen

	//Skapa en rotationsmatris f�r �gat
    RotMatX[1][1] = RotMatX[2][2] = cos(eye.avelocity[0]);
    RotMatX[2][1] = -(RotMatX[1][2] = sin(eye.avelocity[0]));
    RotMatY[2][2] = RotMatY[0][0] = cos(eye.avelocity[1]);
    RotMatY[2][0] = -(RotMatY[0][2] = sin(eye.avelocity[1]));
    RotMatZ[1][1] = RotMatZ[0][0] = cos(eye.avelocity[2]);
    RotMatZ[1][0] = -(RotMatZ[0][1] = sin(eye.avelocity[2]));

    eye.angles=(eye.angles*RotMatX*RotMatY*RotMatZ);	//Multiplicera ihop �gats rotation

    blit(scr,screen,0,0,0,0,SCRWIDTH,SCRHEIGHT);	//Skicka ut alltihop till sk�rmen
    clear(scr);						//T�m det tempor�ra sk�rmminnet
    frames++;						//�ka p� antalet frames
  }

  shut_down();						//Anropa nedst�ngningsrutinen

	//Skriv ut antalet frames, hur l�ng tid det tagit, och frames per sekund
  cout << "Frames: " << frames << endl;
  cout << "Time:   " << (t=(time(0)-t)) << endl;
  float fps = ((float) frames)/t;
  cout << "FPS:    " << fps << endl;
}
END_OF_MAIN()

void shut_down()	//Nedst�ngningsrutinen
{
  for (int foo=0;foo<num_objs;foo++)
  {
    delete objs[foo];			//Deallokera minne f�r objekten
  }
  delete[] objs;			//Deallokera minne f�r objektpekarne

  destroy_bitmap(scr);			//Deallokera minnet f�r tempor�rsk�rmen
  set_gfx_mode(GFX_TEXT,0,0,0,0);	//St�ll tillbaka sk�rml�get till text
}
