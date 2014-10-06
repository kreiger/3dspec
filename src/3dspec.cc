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

Object **objs;		//Deklarera en lista på pekare till Objekt
int num_objs=0;		//Deklarera en räknare som håller reda på antalet objekt
BITMAP *scr;		//Deklarera en pekare till en bit minnesområde, som man kan skriva till

using namespace std ;

void initialize()	//Initialiseringsrutinen
{
	allegro_init();					//Initialisera Allegro
	install_keyboard();				//Initialisera Allegros Tangentbordsrutiner
	install_timer();				//Initialisera Allegros Timerrutiner
	install_mouse();				//Initialisera Allegros Musrutiner
	set_color_depth(COLDEPTH);			//Sätt färgdjupet
	set_gfx_mode(SCRMODE,SCRWIDTH,SCRHEIGHT,0,0);	//Byt skärmläge
	scr = create_bitmap(SCRWIDTH,SCRHEIGHT);	//Allokera minnesområde för en temporär skärm
}

int main (int argc, char **argv)
{
  if (argc < 2)	//Om man inte har angett en objektfil
  {
    cout << "Kreiger's specialarbete! Version: "<< VER << " Build: "<< BUILD << endl; 
    cout << "Syntax:" << endl << "3DSPEC <objfile.off>" << endl;
    exit (1);
  }

  objs = new (Object *)[argc-1];	//Allokera minne för objektpekarna

  for (int foo=1;argv[foo];foo++)	//Läs in objektfilerna
    if (load_off (argv[foo],foo-1))
      num_objs++;
    else
      exit (1);

  initialize();				//Anropa initialiseringsrutinen

  Entity eye(0,0,-50);			//Skapar ett öga, och sätter dess koordinater

  Matrix<float> RotMatX(3,3);		//Skapar rotationsmatriser
  Matrix<float> RotMatY(3,3);
  Matrix<float> RotMatZ(3,3);
  Matrix<float> Result(3,3);

  RotMatX.Unit();			//Gör rotationsmatriserna till enhetsmatriser
  RotMatY.Unit();
  RotMatZ.Unit();

  Vector tmp1,p1;			//Skapar två temporära vektorer

  long int frames=0;			//Skapar en variabel som håller reda på antal framess
  float t = time(0);			//Skapar en variabel som håller reda på tiden

  while (1)				//Kör en oändlig loop
  {
    for (int foo=0;foo<num_objs;foo++)	//För varje objekt, gör följande:
    {

	//Räkna ut rotationsmatriserna
      RotMatX[1][1] = RotMatX[2][2] = cos(objs[foo]->avelocity[0]);
      RotMatX[2][1] = -(RotMatX[1][2] = sin(objs[foo]->avelocity[0]));
      RotMatY[2][2] = RotMatY[0][0] = cos(objs[foo]->avelocity[1]);
      RotMatY[2][0] = -(RotMatY[0][2] = sin(objs[foo]->avelocity[1]));
      RotMatZ[1][1] = RotMatZ[0][0] = cos(objs[foo]->avelocity[2]);
      RotMatZ[1][0] = -(RotMatZ[0][1] = sin(objs[foo]->avelocity[2]));

	//Multiplicera ihop rotationsmatriserna
      objs[foo]->angles=Result=RotMatX*RotMatY*RotMatZ*objs[foo]->angles;
      
      for (int bar=0;bar<objs[foo]->num_verts;bar++)				//För varje vertex i objektet
      {
        objs[foo]->verts[bar]=objs[foo]->origverts[bar]*Result;  		//Rotera
      }
      for (int bar=0;bar<objs[foo]->num_polys;bar++)				//För varje polygon i objektet
      {
        objs[foo]->polys[bar].normal=objs[foo]->polys[bar].orignormal*Result;  //Rotera normalen

        tmp1 = eye.origin-(objs[foo]->origin + objpolyvert(foo,bar,0));		//Vektorn mellan första vertexen och ögat
	tmp1.Normalize();							//Normera vektorn

        float dot = ((tmp1) | eye.front());					//Räkna ut skalärprodukten av vektorn och ögats "framåtvektor"

        if (dot >= 0) continue;							//Är polygonen bakom ögat? I så fall, gå till nästa polygon

	dot = (tmp1 | objs[foo]->polys[bar].normal);				//Räkna ut skalärprodukten av vektorn och polygonens normal
        if (dot < 0) continue; 							//Är polygonen bortvänd?

	int col = (int)(dot*255);
	col = makecol(col,col,col); 						//Bestäm färg på polygonen med ledning av vinkeln mot den

	int nv=objs[foo]->polys[bar].num_verts;					//Placera antalet punkter i polygonen i en temporär variabel
	int p[nv*2];								//Allokera minne för skärm koordinaterna
        for (int baz=0;baz<nv;baz++)						//För varje punkt i polygonen
        {
          p1 = (objs[foo]->origin + objpolyvert(foo,bar,baz)) - eye.origin;	//Placera ögat i origo
	  p1*=eye.angles;							//Rotera punkten runt ögat

          p[baz*2] = (int)(HSCRW + HSCRW*(p1[0] / (p1[2])));	//Spara skärm-X och skärm-Y 
          p[baz*2+1] = (int)(HSCRH - HSCRW*(p1[1] / (p1[2])));
        }
	polygon(scr,nv,p,col);	//Låt allegro rita ut polygonen
      }
    }

    if (key[KEY_Q]) objs[0]->avelocity[0]+=OROT;	//Läs in knapptryckningar för rotation av objektet
    if (key[KEY_A]) objs[0]->avelocity[0]-=OROT;
    if (key[KEY_W]) objs[0]->avelocity[1]+=OROT;
    if (key[KEY_S]) objs[0]->avelocity[1]-=OROT;
    if (key[KEY_E]) objs[0]->avelocity[2]+=OROT;
    if (key[KEY_D]) objs[0]->avelocity[2]-=OROT;
    eye.avelocity.Clear();	//Nollställ ögats rotation

    int mx;
    int my;
    get_mouse_mickeys(&mx,&my);		//Läs in musen

    (eye.avelocity[1])+=(float)(mx)*0.001;	//Öka på ögats rotationshastighet
    (eye.avelocity[0])+=(float)(my)*0.001;
    if (key[KEY_PGUP]) eye.avelocity[2]+=0.01;
    if (key[KEY_HOME]) eye.avelocity[2]-=0.01;

    if (mouse_b & 2) eye.origin += (eye.front());	//Läs in musknapparna
    if (mouse_b & 1) eye.origin -= (eye.front());	//Och flytta ögat därefter
    if (key[KEY_RIGHT]) eye.origin += (eye.right()*0.1);
    if (key[KEY_LEFT]) eye.origin -= (eye.right()*0.1);
    if (key[KEY_UP]) eye.origin += (eye.up()*0.1);
    if (key[KEY_DOWN]) eye.origin -= (eye.up()*0.1);
 
    if (key[KEY_ESC]) break;	//Om användaren trycker ESC, avsluta oändlighetsloopen

	//Skapa en rotationsmatris för ögat
    RotMatX[1][1] = RotMatX[2][2] = cos(eye.avelocity[0]);
    RotMatX[2][1] = -(RotMatX[1][2] = sin(eye.avelocity[0]));
    RotMatY[2][2] = RotMatY[0][0] = cos(eye.avelocity[1]);
    RotMatY[2][0] = -(RotMatY[0][2] = sin(eye.avelocity[1]));
    RotMatZ[1][1] = RotMatZ[0][0] = cos(eye.avelocity[2]);
    RotMatZ[1][0] = -(RotMatZ[0][1] = sin(eye.avelocity[2]));

    eye.angles=(eye.angles*RotMatX*RotMatY*RotMatZ);	//Multiplicera ihop ögats rotation

    blit(scr,screen,0,0,0,0,SCRWIDTH,SCRHEIGHT);	//Skicka ut alltihop till skärmen
    clear(scr);						//Töm det temporära skärmminnet
    frames++;						//Öka på antalet frames
  }

  shut_down();						//Anropa nedstängningsrutinen

	//Skriv ut antalet frames, hur lång tid det tagit, och frames per sekund
  cout << "Frames: " << frames << endl;
  cout << "Time:   " << (t=(time(0)-t)) << endl;
  float fps = ((float) frames)/t;
  cout << "FPS:    " << fps << endl;
}
END_OF_MAIN()

void shut_down()	//Nedstängningsrutinen
{
  for (int foo=0;foo<num_objs;foo++)
  {
    delete objs[foo];			//Deallokera minne för objekten
  }
  delete[] objs;			//Deallokera minne för objektpekarne

  destroy_bitmap(scr);			//Deallokera minnet för temporärskärmen
  set_gfx_mode(GFX_TEXT,0,0,0,0);	//Ställ tillbaka skärmläget till text
}
