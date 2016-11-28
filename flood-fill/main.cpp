//  main.cpp
//  With help from:
//  https://www.libsdl.org/release/SDL-1.2.15/docs/html/guidebasicsinit.html
//  http://lazyfoo.net/tutorials/SDL/02_getting_an_image_on_the_screen/index.php
//  https://wiki.libsdl.org/MigrationGuide
//

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>


void floodfill(int *pPixels, int y, int x, int len, int original_color, int new_color)
{
    if (original_color != new_color)
    {
        if (*(pPixels+(y*len)+x) == original_color)
        {
            *(pPixels+(y*len)+x) = new_color;
        
            if (y+1 < len)
            {
                floodfill(pPixels, y+1, x, len, original_color, new_color);
            }
            
            if (y-1 >= 0)
            {
                floodfill(pPixels, y-1, x, len, original_color, new_color);
            }

            if (x+1 < len)
            {
                floodfill(pPixels, y, x+1, len, original_color, new_color);
            }

            if (x-1 >= 0)
            {
                floodfill(pPixels, y, x-1, len, original_color, new_color);
            }
        }
    }
}

void paint(int *pPixels, int x, int y, int len, int new_color)
{
    int original_color = *(pPixels+(y*len)+x);
    floodfill(pPixels, y, x, len, original_color, new_color);
}

// Fill the background with its color

void drawBackground(int *pPixels, int len)
{
    
    for (int i = 0; i < len+25; i++)
    {
        for (int j = 0; j < len; j++)
        {
            *pPixels=0x00ffffff;
            pPixels += 1;
        }
    }
    
}

void drawTools(int *pPixelsStart, int len)
{
    SDL_Surface* pBrushIcon = IMG_Load("../../../../../../../../Documents/puny-paint/resources/brush.png");
    SDL_Surface* pBucketIcon = IMG_Load("../../../../../../../../Documents/puny-paint/resources/paintbucket.png");
    SDL_Surface* pRed = IMG_Load("../../../../../../../../Documents/puny-paint/resources/red.png");
    SDL_Surface* pOrange = IMG_Load("../../../../../../../../Documents/puny-paint/resources/orange.png");
    SDL_Surface* pYellow = IMG_Load("../../../../../../../../Documents/puny-paint/resources/yellow.png");
    SDL_Surface* pGreen = IMG_Load("../../../../../../../../Documents/puny-paint/resources/green.png");
    SDL_Surface* pBlue = IMG_Load("../../../../../../../../Documents/puny-paint/resources/blue.png");
    SDL_Surface* pPurple = IMG_Load("../../../../../../../../Documents/puny-paint/resources/purple.png");
    SDL_Surface* pBlack = IMG_Load("../../../../../../../../Documents/puny-paint/resources/black.png");
    SDL_Surface* pGray = IMG_Load("../../../../../../../../Documents/puny-paint/resources/gray.png");
    SDL_Surface* pWhite = IMG_Load("../../../../../../../../Documents/puny-paint/resources/white.png");
    SDL_Surface* pPink = IMG_Load("../../../../../../../../Documents/puny-paint/resources/pink.png");
    SDL_Surface* pSand = IMG_Load("../../../../../../../../Documents/puny-paint/resources/sand.png");
    SDL_Surface* pBrown = IMG_Load("../../../../../../../../Documents/puny-paint/resources/brown.png");
    SDL_Surface* pRaspberry = IMG_Load("../../../../../../../../Documents/puny-paint/resources/raspberry.png");
    SDL_Surface* pMidnightBlue = IMG_Load("../../../../../../../../Documents/puny-paint/resources/midnight_blue.png");
    
    int *brush = (int *)pBrushIcon->pixels;
    int *bucket = (int *)pBucketIcon->pixels;
    int *red = (int *)pRed->pixels;
    int *orange = (int *)pOrange->pixels;
    int *yellow = (int *)pYellow->pixels;
    int *green = (int *)pGreen->pixels;
    int *blue = (int *)pBlue->pixels;
    int *purple = (int *)pPurple->pixels;
    int *black = (int *)pBlack->pixels;
    int *gray = (int *)pGray->pixels;
    int *white = (int *)pWhite->pixels;
    int *pink = (int *)pPink->pixels;
    int *sand = (int *)pSand->pixels;
    int *brown = (int *)pBrown->pixels;
    int *raspberry = (int *)pRaspberry->pixels;
    int *midnightBlue = (int *)pMidnightBlue->pixels;
    
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < len; j++)
        {
            if (j < 25)
            {
                pPixelsStart[(len+i)*len+j] = brush[i*25+j];
            }
            else if (j < 50)
            {
                pPixelsStart[(len+i)*len+j] = bucket[i*25+j-25];
            }
            else if (j < 75)
            {
                pPixelsStart[(len+i)*len+j] = red[i*25+j-50];
            }
            else if (j < 100)
            {
                pPixelsStart[(len+i)*len+j] = orange[i*25+j-75];
            }
            else if (j < 125)
            {
                pPixelsStart[(len+i)*len+j] = yellow[i*25+j-100];
            }
            else if (j < 150)
            {
                pPixelsStart[(len+i)*len+j] = green[i*25+j-125];
            }
            else if (j < 175)
            {
                pPixelsStart[(len+i)*len+j] = blue[i*25+j-150];
            }
            else if (j < 200)
            {
                pPixelsStart[(len+i)*len+j] = purple[i*25+j-175];
            }
            else if (j < 225)
            {
                pPixelsStart[(len+i)*len+j] = black[i*25+j-200];
            }
            else if (j < 250)
            {
                pPixelsStart[(len+i)*len+j] = gray[i*25+j-225];
            }
            else if (j < 275)
            {
                pPixelsStart[(len+i)*len+j] = white[i*25+j-250];
            }
            else if (j < 300)
            {
                pPixelsStart[(len+i)*len+j] = pink[i*25+j-275];
            }
            else if (j < 325)
            {
                pPixelsStart[(len+i)*len+j] = sand[i*25+j-300];
            }
            else if (j < 350)
            {
                pPixelsStart[(len+i)*len+j] = brown[i*25+j-325];
            }
            else if (j < 375)
            {
                pPixelsStart[(len+i)*len+j] = raspberry[i*25+j-350];
            }
            else
            {
                pPixelsStart[(len+i)*len+j] = midnightBlue[i*25+j-375];
            }
        }
    }
}

// Drawing a dot

void setPixel(int x, int y, int * pPixels, int len, SDL_Window * window, int lineColor)
{
    int xStart = std::max(x-1, 0);
    int xEnd = std::min(x+1, len-1);
    int yEnd = std::min(len-1, y+1);
    int yStart = std::max(y-1, 0);
    
    for(int xx = xStart; xx <= xEnd; xx++)
    {
        for(int yy = yStart; yy <= yEnd; yy++)
        {
            *(pPixels+(yy)*len+(xx))=lineColor;
        }
    }
    
    SDL_Rect rects[1];
    SDL_Rect rect;
    rect.x = xStart;
    rect.y = yStart;
    rect.w = 3;
    rect.h = 3;
    rects[0] = rect;
    
    SDL_UpdateWindowSurfaceRects(window, rects, 1);
}


int main(int argc, const char * argv[]) {
    
    int myArrayLength = 400;                //Actual size of desired grid (side length)
    
    SDL_Window *pDisplay;
    SDL_Surface *pSurface;
    
    std::string windowTitle = "PunyPaint";
    
    // Initialize the video
    
    int initializationResult = SDL_Init(SDL_INIT_VIDEO);
    
    if (initializationResult == -1){
        std::cout << "There was an error";
        exit(-1);
    }
    
    // Initialize the window
    
    
    pDisplay = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, myArrayLength, myArrayLength+25, SDL_WINDOW_SHOWN);
    
    if (pDisplay == NULL)
    {
        std::cout << "There was a problem setting the display";
        exit(-1);
    }
    
    // Get the surface and its pixels from the window so it can be drawn to
    
    pSurface = SDL_GetWindowSurface(pDisplay);
    int *pPixels = (int *)pSurface->pixels;
    
    // Populate board with first generation and display it
    
    drawBackground(pPixels, myArrayLength);
    drawTools(pPixels, myArrayLength);
    SDL_UpdateWindowSurface(pDisplay);
    
    // Event handling loop (below) based on Lazy Foo SDL Tutorial 03
    SDL_Event event;
    bool running = true;
    
    // Update board and display each new generation
    
    bool buttonPressed = false;
    bool pencil = true;
    int fillColor = 0x00ffffff;
    int lineColor = 0x00000000;
    
    while (running)
    {
        while (SDL_PollEvent (&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_MouseButtonEvent mEvent = *(SDL_MouseButtonEvent *)&event;
                if (mEvent.y < myArrayLength)
                {
                    if(pencil)
                    {
                        setPixel(mEvent.x, mEvent.y, pPixels, myArrayLength, pDisplay, lineColor);
                        buttonPressed = true;
                    }
                    else
                    {
                        paint(pPixels, mEvent.x, mEvent.y, myArrayLength, fillColor);
                        SDL_UpdateWindowSurface(pDisplay);
                    }
                }
                else
                {
                    if (mEvent.x < 25)
                    {
                        pencil = true;
                    }
                    else if (mEvent.x < 50)
                    {
                        pencil = false; //That is, paintbucket is true
                    }
                    else
                    {
                        if (mEvent.x % 25 == 0)
                        {
                            if (pencil)
                            {
                                lineColor = pPixels[(myArrayLength+2)*myArrayLength+mEvent.x+1];
                            }
                            else
                            {
                                fillColor = pPixels[(myArrayLength+2)*myArrayLength+mEvent.x+1];
                            }
                        }
                        else if (mEvent.x % 25 == 0)
                        {
                            if (pencil)
                            {
                                lineColor = pPixels[(myArrayLength+2)*myArrayLength+mEvent.x-1];
                            }
                            else
                            {
                                fillColor = pPixels[(myArrayLength+2)*myArrayLength+mEvent.x-1];
                            }
                        }
                        else
                        {
                            if (pencil)
                            {
                                lineColor = pPixels[(myArrayLength+2)*myArrayLength+mEvent.x];
                            }
                            else
                            {
                                fillColor = pPixels[(myArrayLength+2)*myArrayLength+mEvent.x];
                            }
                        }
                    }
                }
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                if(pencil)
                {
                    buttonPressed = false;
                    SDL_MouseButtonEvent mEvent = *(SDL_MouseButtonEvent *)&event;
                    setPixel(mEvent.x, mEvent.y, pPixels, myArrayLength, pDisplay, lineColor);
                }
            }
            else if (buttonPressed && event.type == SDL_MOUSEMOTION)
            {
                if(pencil)
                {
                    SDL_MouseMotionEvent mEvent = *(SDL_MouseMotionEvent *)&event;
                    setPixel(mEvent.x, mEvent.y, pPixels, myArrayLength, pDisplay, lineColor);
                }
            }
        }
    }
    
    SDL_FreeSurface(pSurface);
    SDL_DestroyWindow(pDisplay);
    
    SDL_Quit();
    
    return 0;
}
