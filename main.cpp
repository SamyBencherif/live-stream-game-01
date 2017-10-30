//Using SDL and standard IO
#include </usr/local/include/SDL2/SDL.h>
#include <stdio.h>

//Github @celesta +contrib

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

SDL_Renderer* renderer;
SDL_Texture* gHelloWorld_tex;

//Attempts to create SDL window, returns true if sucessful
bool init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow( "My Snail Bby", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//create renderer from window
			renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gHelloWorld = SDL_LoadBMP( "snail_static.bmp" );
	if( gHelloWorld == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
		success = false;
	}

	return success;
}

void close()
{
	//Deallocate surface (already done).
	//SDL_FreeSurface( gHelloWorld );
	gHelloWorld = NULL;

	SDL_DestroyTexture(gHelloWorld_tex);
	gHelloWorld_tex = NULL;

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{

			//I think my gameloop should go here:
			SDL_Rect dstrect;


			dstrect.x = 0;
			dstrect.y = 0;
			dstrect.w = 100;
			dstrect.h = 100;

			bool running = true;

			SDL_Event event;

			//Loading_Surf = SDL_LoadBMP("Background.bmp");
			gHelloWorld_tex = SDL_CreateTextureFromSurface(renderer, gHelloWorld);
			SDL_FreeSurface(gHelloWorld);

			while (running)
			{

				dstrect.x += 1;

				//now why doesn't this render anything?

				SDL_SetRenderDrawColor(renderer, 20, 0, 0, 255);

				SDL_RenderClear(renderer);

				//Apply the image
				SDL_RenderCopy(renderer, gHelloWorld_tex, NULL, &dstrect);

				SDL_RenderPresent(renderer);

				//Update the surface
				//SDL_UpdateWindowSurface( gWindow );

				//Event Handling
				while( SDL_PollEvent( &event ) )
				{
					switch( event.type )
					{
						case SDL_KEYDOWN:
							printf( "Key press detected\n" );
							break;

						case SDL_KEYUP:
							printf( "Key release detected\n" );
							break;

						case SDL_WINDOWEVENT:
							if (event.window.event == SDL_WINDOWEVENT_CLOSE)
							{
								printf("Window Close Event\n");
								running = false;
							}
							break;

						default:
							break;
					}
			}
		}
		}
	}
	//Free resources and close SDL
	close();

	return 0;
}