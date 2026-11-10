//PROGETTO FRATTALI BENIGNI E SIGRISORELLI 4^AII.
#include <iostream>
#include <conio.h>      //Per usare getch().
#include <cmath>        
#include "graphics2.h"  //Per la grafica.
using namespace std;
const int RIS=800;        //Risoluzione dello schermo.
const int NUM_ITE=20;     //Numero di iterazioni dei frattali di Julia e Mandelbrot.
const int I=10;           //Numero di iterazioni triangolo di Sierpinski.
void converti(int , int, float &, float & );                       //Converte i punti della griglia in coordinate polari.
void incrementa(int &, int &);                                     //Per aumentare a ogni pixel la x e la y del punto girglia.
void funzioneComplessa(float &, float &, float ,float );           //Per il calcolo della Z.
float modulo(float ,float );                                       //Per il calcolo del modulo.
void frattaleJulia(float ,float ); 
void frattaleMandelbrot();
void trovaPunto(int ,int ,int ,int ,int & ,int & );                //Per trovare il punto medio dei lati dei triangoli di sierpinski.
void frattaleSierpinski(int ,int ,int , int , int , int ,int );

struct complesso   //Per rappresentare i numeri complessi.
{
	float re;
	float im;
};

int main()
{
	string opz;
    while(1)
    {
    	//Menù.
    	system("cls");
    	cout<<endl<<"Cosa vuoi fare?"<<endl;   
	    cout<<"1: Julia"<<endl;
	    cout<<"2: Mandelbrot"<<endl;
 	    cout<<"3: Sierpinski"<<endl;
 	    cout<<"4: Crea il tuo frattale"<<endl;
	    cout<<"5: Esci"<<endl;	
	    cout<<endl<<"Inserisci il numero relativo all'opzione: ";
	    do
		{
			//Controllo che l'utente inserisca solo numeri a una cifra.
			cin>>opz;
			if(opz.length()==1 && isdigit(opz[0]))
				break;
			else
				cout<<endl<<"Inserire un solo carattere NUMERICO."<<endl;
		}while(1); 
		switch(opz[0])
	    {
	    	case'1':
	    	{
	    		//Manda a video il frattale di Julia.
	    		int GraphDriver=0,GraphMode=0;
                initgraph(&GraphDriver,&GraphMode,"",RIS,RIS);
				complesso c;
                c.re=0.28;
                c.im=0.01;
                frattaleJulia(c.re,c.im);
				getchg();
				closegraph();
                break;
			}
			case'2':
			{
				//Manda a video il frattale di Mandelbrot.
				int GraphDriver=0,GraphMode=0;
                initgraph(&GraphDriver,&GraphMode,"",RIS,RIS);
				frattaleMandelbrot();
                getchg();
                closegraph();
				break;
			}
			case'3':
			{
				//Manda a video il frattale di Sierpinski.
				int GraphDriver=0,GraphMode=0;
                initgraph(&GraphDriver,&GraphMode,"",RIS,RIS);
                int y1=RIS-200, x1=100, y2=y1, x2=x1+y1, x3=x1+y2/2, y3=y1-y2*0.866;   //Coordinate di inizio e fine dei lati del triangolo. 
				setbkcolor(WHITE);
	            cleardevice();
	            setcolor(DARKGRAY);
				frattaleSierpinski(x1,y1,x2,y2,x3,y3,I);
                getchg();
				closegraph();
				break;
			}
			case'4':
			{
				//Permette all'utente di creare un suo frattale scegliendo i valori di c.
				complesso c;
				cout<<"                                                                     Esempi: (-0.06 ; 0.7)   (-1 ; 0)"<<endl<<"                                                                             (0.15 ; 0.65)   (0.28 ; 0.01)"<<endl;
		  	    cout<<"Scegi il primo valore per il frattale: ";
			    cin>>c.re;
		  	    cout<<"Scegi il secondo valore per il frattale: ";
			    cin>>c.im;
				int GraphDriver=0,GraphMode=0;
                initgraph(&GraphDriver,&GraphMode,"",RIS,RIS);
                frattaleJulia(c.re,c.im);
                getchg();
                closegraph();
				break;
			}
			case '5':
			{
				//Per uscire.
				return 0;
			}
		}
	}
}

void converti(int x, int y, float &re, float &im)  //Converte i punti griglia in coordinate polari.
{
	re=(float)x/(RIS/4)-2;
	im=-((float)y/(RIS/4)-2);
}

void incrementa(int &x, int &y)  //Per aumentare a ogni pixel la x e la y del punto girglia.
{  
	if(y==RIS)
    {
    	if(x!=RIS-1)      
    	  y=0;
    	x++;
	}
    else
	  y++;
}

void funzioneComplessa(float &x,float &y,float xc,float yc)  //Per il calcolo di Z.
{
   float tmp1=x,tmp2=y;              
   x=((tmp1*tmp1)+((tmp2*tmp2)*-1))+(xc); 
   y=2*(tmp1)*(tmp2)+(yc);
}

float modulo(float re, float im)  //Per il calcolo del modulo.
{
	return sqrt(re*re+im*im);
}

void frattaleJulia(float cRe, float cIm)
{
	int xg=0,yg=-1;
    complesso z;
    while(xg<RIS && yg<=RIS)   
    {
    	incrementa(xg,yg);
    	converti(xg,yg,z.re,z.im);
        for(int i=0;i<NUM_ITE;i++)
        {
        	funzioneComplessa(z.re,z.im,cRe,cIm);
    	    if(modulo(z.re,z.im)>2)
    	    {
    	    	putpixel(xg,yg,14);
    	    	break;
			}
	    } 
	}
}

void  frattaleMandelbrot()
{
	int xg=0,yg=-1;
    complesso z;
    complesso c;
    while(xg<RIS && yg<=RIS)   
    {
    	z.re=0;
    	z.im=0;
    	incrementa(xg,yg);
    	converti(xg,yg,c.re,c.im); 
        for(int i=0;i<NUM_ITE;i++)
        {
        	funzioneComplessa(z.re,z.im,c.re,c.im);
    	    if(modulo(z.re,z.im)>2)
    	    {
    	    	putpixel(xg,yg,i);
    	    	break;
			}
	    } 
	}
}

void trovaPunto(int x1,int y1,int x2,int y2,int &x3,int &y3)  //Trovo il punto medio dei lati dei triangoli di Sierpinski.
{
	 x3=(x1+x2)/2;		
	 y3=(y1+y2)/2;
}

void frattaleSierpinski(int x1,int y1,int x2,int y2,int x3,int y3,int i)
{	
    int x4,y4,x5,y5,x6,y6;
    if(i<=0)  //Si ferma quando sono finite le iterazioni.
	  return;
	
	//Disegno i lati del triangolo.
	line(x1,y1,x2,y2);
	line(x2,y2,x3,y3);
	line(x3,y3,x1,y1);
	//Trovo il punto medio dei lati del triangolo.
	trovaPunto(x1,y1,x2,y2,x4,y4);
	trovaPunto(x2,y2,x3,y3,x5,y5);
	trovaPunto(x3,y3,x1,y1,x6,y6);
	//Ripetiamo la funzione ricorsivamente creando triangoli più piccoli all'interno del triangolo.
	frattaleSierpinski(x1,y1,x4,y4,x6,y6,i-1);		
	frattaleSierpinski(x4,y4,x2,y2,x5,y5,i-1);
	frattaleSierpinski(x6,y6,x5,y5,x3,y3,i-1);
}
