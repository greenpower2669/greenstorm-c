#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 1800*1
#define HEIGHT 900*1
#define IMG_PATH "pv.png"
#define IMG_PATH2 "pr.png"
#define mtl 4
// prototypage touchscreen multi le 25 06 2021 fg
// remarque id touch premier est 0 attention
// vercteur 0 hors de l'écran corrigé le 28 06 2021 fg

int main (int argc, char *argv[]) {

	// variable declarations
	//SDL_Window *win = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *img = NULL;
	SDL_Texture *img2 = NULL;
	
	int w, h; // texture width & height
	int pw, ph; // transporteur xy sur event
	
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
			return 1;
	SDL_Window* win= SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0); 
    //bool Exit = false;
    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN_DESKTOP;//SDL_WINDOW_FULLSCREEN; 
    bool IsFullscreen = SDL_GetWindowFlags(win) & FullscreenFlag; 
    SDL_SetWindowFullscreen(win, IsFullscreen ? 0 : FullscreenFlag); 
    SDL_ShowCursor(IsFullscreen);
	
	// create the window and renderer
	// note that the renderer is accelerated
	//win = SDL_CreateWindow("Image Loading", 100, 100, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	
	// load our image
	img = IMG_LoadTexture(renderer, IMG_PATH);
	SDL_QueryTexture(img, NULL, NULL, &w, &h);
	img2 = IMG_LoadTexture(renderer, IMG_PATH2);
	SDL_QueryTexture(img2, NULL, NULL, &w, &h);
	 // get the width and height of the texture
	// put the location where we want the texture to be drawn into a rectangle
	// I'm also scaling the texture 2x simply by setting the width and height
	SDL_Rect texr;
	
	texr.x = WIDTH/40; 
	texr.y = HEIGHT/40; 
	texr.w = w*1; 
	texr.h = h*1;
	
	SDL_Rect texrd;
	texrd.x = WIDTH/40*25;
	texrd.y = HEIGHT/40*25; 
	texrd.w = w*1; 
	texrd.h = h*1;
	int gxxi1=0;
	int gyyi1=0;
	int gxxi2=0;
	int gyyi2=0;
	int dxxi1=0;
	int dyyi1=0;
	int dxxi2=0;
	int dyyi2=0;
	
	int gid=110;//110 pourval 0 car 0 est la première touche.
	int vct=100;
	int did=110;
	bool g=false;
	bool d=false;
	int ii=0;//pour vect et aff selon iteration prévoir syncro par le temps de la limite
	int iii=0;//pour conditiond en couches hautes proto  en pause le 25 062021
	// id variables déclaration
	int xx=0;
	int yy=0;
	int gxx=0;
	int gyy=0;
	int dxx=0;
	int dyy=0;
	// coo declaration
	int gxx0=0;
	int gyy0=0;
	int dxx0=0;
	int dyy0=0;
	// coo sauvegarde valeur n t0 avant t1
	int gfx=0;
	int gfy=0;
	int dfx=0;
	int dfy=0;
	// vecteur dif g d par w et h
	int gfx0=0;
	int gfy0=0;
	int dfx0=0;
	int dfy0=0;
	// vecteur n des vect t0 avant 1
	
	pw=1;
	ph=1;	
	// main loop
	while (1) {
		
		for (int i=1;i<3;++i) {
			//
			ii++;
			iii++;
			
		
		// event poll
			SDL_Event e;
			
			if ( SDL_PollEvent(&e) ) {
				yy=int(e.tfinger.y*HEIGHT)-h;
				xx=int(e.tfinger.x*WIDTH)-w;
				//gxx+=e.tfinger.touchId-1;

				if (e.type == SDL_QUIT)
					break;
				else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
					break;
				//
				// set on down and del on release is possible now just init one
				if (e.type==SDL_FINGERDOWN) {
					if (gid==110 and xx<WIDTH/2 and did!=e.tfinger.fingerId){
						gid=e.tfinger.fingerId;
						g=true;
						gxx=xx;
						gyy=yy;
					}
					if (did==110 and xx>WIDTH/2 and gid!=e.tfinger.touchId){
						did=e.tfinger.fingerId;
						d=true;
						dxx=xx;
						dyy=yy;
					}
				}
				if (e.type==SDL_FINGERUP) {
					if (gid==e.tfinger.fingerId){
						g=false;
						gid=110;
						// centralisable en sub vg et vd
						gxx0=gxx;
						gyy0=gyy;
						gfx0=gfx;
						gfy0=gfy;
						gxx=xx;
						gyy=yy;
						//f=0?
				        if (gxx<0 or gxx>WIDTH-texrd.w*mtl){
				            gfx0=(gxx-WIDTH/2)*0.1;
				        }
				        if (gyy<0 or gyy>HEIGHT-texrd.h*mtl){
				          gfy0=(gyy-HEIGHT/2)*0.1;
				        }
					    // f=0?
						// centralisable en sub vg et vd
					}
					if (did==e.tfinger.fingerId){
						d=false;
						did=110;
						// centralisable en sub vg et vd
						dxx0=dxx;
						dyy0=dyy;
						dfx0=dfx;
						dfy0=dfy;
						dxx=xx;
						dyy=yy;
						//f=0?
				        if (dxx<0 or dxx>WIDTH-texrd.w*mtl){
				            dfx0=(dxx-WIDTH/2)*0.1;
				        }
				        if (dyy<0 or dyy>HEIGHT-texrd.h*mtl){
				          dfy0=(dyy-HEIGHT/2)*0.1;
				        }
					    // f=0?
						//dfx=(dxx-dxx0)*2;
						//dfy=(dyy-dyy0)*2;
						// centralisable en sub vg et vd
					}
				}
				
				if (e.type == SDL_FINGERMOTION)
				{
					if (e.tfinger.fingerId==gid){
						// centralisable en sub vg et vd
						gfx0=gfx;
						gfy0=gfy;
						gxx=xx;
						gyy=yy;
						gfx=(gxx-gxx0)*0.3;
						gfy=(gyy-gyy0)*0.3;
						
						// centralisable en sub vg et vd
					}
					if (e.tfinger.fingerId==did){
						// centralisable en sub vg et vd
						
						dxx=xx;
						dyy=yy;
						dfx0=dfx;
						dfy0=dfy;
						dfx=(dxx-dxx0)*0.3;
						dfy=(dyy-dyy0)*0.3;
						// centralisable en sub vg et vd
					}
				
				}
			//
			} 
			if (ii>5){
				
				if (g){
					texr.x = gxx; 
					texr.y = gyy;
					gxxi1=gxx;
					gyyi1=gyy;
					gxxi2=gxxi1;
					gyyi2=gyyi1;
					gxx0=gxxi2;
					gyy0=gyyi2;
				}
				else{
					gxx+=gfx0;
					gyy+=gfy0;
					texr.x = gxx; 
					texr.y = gyy;
								
				if ((gxx<0 or gxx>WIDTH-texr.w*mtl) and  (gyy<0 or gyy>HEIGHT-texr.h*mtl)){
				    gfx0*=-1;
				    gfy0*=-1;
				    while ((gxx<0 or gxx>WIDTH-texr.w*mtl) and  (gyy<0 or gyy>HEIGHT-texr.h*mtl) ){
				        gxx+=gfx0;
				        gyy+=gfy0;
				    }	
				}
				if (gxx<0 or gxx>WIDTH-texr.w*mtl){
				    gfx0*=-1;
				    if (gxx<0 or gxx>WIDTH-texr.w*mtl){
				        gxx+=gfx0;
				    }
				}
				if (gyy<0 or gyy>HEIGHT-texr.h*mtl){
				    gfy0*=-1;
				    while(gyy<0 or gyy>HEIGHT-texr.h*mtl){
				        gyy+=gfy0;
				    }
				        
				}
				}
				if (d){
					dxxi1=dxx;
					dyyi1=dyy;
					dxxi2=dxxi1;
					dyyi2=dyyi1;
					dxx0=dxxi2;
					dyy0=dyyi2;
					texrd.x = dxx; 
					texrd.y = dyy;
					
				}
				else{
					dxx+=dfx0;
					dyy+=dfy0;
					
					texrd.x = dxx; 
					texrd.y = dyy;
				
				
		
				if ((dxx<0 or dxx>WIDTH-texrd.w*mtl) and (dyy<0 or dyy>HEIGHT-texrd.h*mtl) ){
				    dfx0*=-1;
				    dfy0*=-1;
				    while ((dxx<0 or dxx>WIDTH-texrd.w*mtl) and (dyy<0 or dyy>HEIGHT-texrd.h*mtl) ){
				        dxx+=dfx0;
				        dyy+=dfy0;
				    }	
				}
				if (dxx<0 or dxx>WIDTH-texrd.w*mtl){
				    
				    dfx0*=-1;
				    while (dxx<0 or dxx>WIDTH-texrd.w*mtl){
				        dxx+=dfx0;
				    }
				}
				if (dyy<0 or dyy>HEIGHT-texrd.h*mtl){
				    dfy0*=-1;
				    while(dyy<0 or dyy>HEIGHT-texrd.h*mtl){
				        dyy+=dfy0;
				    }
				     
				}
				}
				
			SDL_RenderClear(renderer);
		// copy the texture to the rendering context
			SDL_RenderCopy(renderer, img, NULL, &texr);
			SDL_RenderCopy(renderer, img2, NULL, &texrd);
			SDL_RenderPresent(renderer);   
			ii=0;
			}
			if (iii>1000){//ph
			    gfx0*=.999;
			    gfy0*=.999;
			    dfx0*=.999;
			    dfy0*=.999;
				
			
				iii=0;
				
				
			}
		}
	SDL_Delay(5);	
	}
	
	SDL_DestroyTexture(img);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	
	return 0;
}