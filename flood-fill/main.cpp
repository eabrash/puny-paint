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


// Initialize video and create a window, returning the window

SDL_Window * setUpWindow(int canvasSideLength)
{
    std::string windowTitle = "PunyPaint";
    
    // Initialize the video
    
    int initializationResult = SDL_Init(SDL_INIT_VIDEO);
    
    if (initializationResult == -1){
        std::cout << "There was an error";
        exit(-1);
    }
    
    // Initialize the window
    
    SDL_Window *pDisplay = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, canvasSideLength, canvasSideLength+25, SDL_WINDOW_SHOWN);
    
    if (pDisplay == NULL)
    {
        std::cout << "There was a problem setting the display";
        exit(-1);
    }
    
    return pDisplay;
}


// Give all pixels a color of white to make a new drawing canvas

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


// Load tool selectors and color swatches

void drawTools(int *pPixelsStart, int len)
{
    // Load small PNG images representing tools and color options
    
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
    
    // For each small loaded image, get a pointer to its pixel array
    
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

    int *tooltray[16] = {brush, bucket, red, orange, yellow, green, blue, purple, black, gray, white, pink, sand, brown, raspberry, midnightBlue};
    
    // Draw each tool or color's "postage stamp" to the region of the tray at the bottom of the window
    for (int tile = 0; tile < 16; tile++)
    {
        for (int x = 0; x < 25; x++)
        {
            for (int y = 0; y < 25; y++)
            {
                pPixelsStart[(len+y)*len+x+25*tile] = tooltray[tile][y*25+x];
            }
        }
    }
}


// Draw a 3 by 3 dot when the user clicks

void setPixel(int x_coord, int y_coord, int * pPixels, int len, int lineColor)
{
    // Define the box that will be filled by the click (may be smaller than 3px by 3px if at canvas edge)
    
    int xStart = std::max(x_coord-1, 0);
    int xEnd = std::min(x_coord+1, len-1);
    int yEnd = std::min(len-1, y_coord+1);
    int yStart = std::max(y_coord-1, 0);
    
    // Fill in the box with the line color; off-grid coordinates will result in no drawing because they
    // make xStart greater than xEnd (for an off-x) or yStart greater than yEnd (for an off-y)
    
    for(int x = xStart; x <= xEnd; x++)
    {
        for(int y = yStart; y <= yEnd; y++)
        {
            *(pPixels+(y)*len+(x))=lineColor;
        }
    }
}


// Draw a line between two points

void drawLine(int lastXCoord, int lastYCoord, int currentXCoord, int currentYCoord, int *pPixels, int len, int lineColor)
{
//    std::cout << currentXCoord << ", " << currentYCoord << "\n";
    bool isVertical = currentXCoord - lastXCoord == 0;
    
    if (isVertical) // Draw a vertical line (slope is undefined)
    {
        for (int y = std::min(lastYCoord, currentYCoord); y < std::max(currentYCoord, lastYCoord); y++)
        {
            setPixel(currentXCoord, y, pPixels, len, lineColor);
        }
    }
    else    // Determine slope and intercept of line and use to color in the appropriate set of pixels
    {
        float slope = float((currentYCoord - lastYCoord))/float((currentXCoord - lastXCoord));
        float intercept = currentYCoord-(slope*currentXCoord);
        
        if (slope >= 1 || slope <= -1) // Need to go through each y pixel and draw corresponding x
            {
            for (int y = std::min(currentYCoord, lastYCoord); y < std::max(lastYCoord, currentYCoord); y++)
            {
                int x = round((y-intercept)/slope);
                setPixel(x, y, pPixels, len, lineColor);
//                std::cout << "Coloring: " << x << ", " << y << "\n";
            }
        }
        else    // Need to go through each x pixel and draw corresponding y
        {
            for (int x = std::min(currentXCoord, lastXCoord); x <= std::max(currentXCoord, lastXCoord); x++)
            {
                int y = round(slope * x + intercept);
                setPixel(x, y, pPixels, len, lineColor);
//                std::cout << "Coloring: " << x << ", " << y << "\n";
            }
        }
    }
}


// Recursive flood-fill algorithm

void floodfill(int *pPixels, int y, int x, int len, int original_color, int new_color)
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


// Wrapper for recursive flood-fill algorithm (identify and set initial color)

void fillWithPaint(int *pPixels, int x, int y, int len, int new_color)
{
    int original_color = *(pPixels+(y*len)+x);
    
    if (original_color != new_color)
    {
        floodfill(pPixels, y, x, len, original_color, new_color);
    }
}


// Set pencil or paint bucket color based on position of user's click on palette

int setColor (SDL_MouseButtonEvent mEvent, int *pPixels, int canvasSideLength)
{
    if (mEvent.x % 25 == 0) // Click is on gray vertical line between color swatches
    {
        return pPixels[(canvasSideLength+2)*canvasSideLength+mEvent.x+1];
    }
    else if (mEvent.y % 25 == 0) // Click is on the gray horizontal line above/below swatches
    {
        return pPixels[(canvasSideLength+2)*canvasSideLength+mEvent.x-1];
    }
    else   // Click is directly on colored portion of a swatch
    {
        return pPixels[(canvasSideLength+2)*canvasSideLength+mEvent.x];
    }
}

// Draw a box around the selected tool or color tile

void giveFocus (int xStart, int *pPixels, int len)
{
    int tileLength = 25;
    
    for (int x = xStart; x < xStart + tileLength; x++)
    {
        for (int y = 0; y < tileLength; y++)
        {
            if (y == 0 || y == tileLength-1 || x == xStart || x == xStart + tileLength -1)
            {
                pPixels[(len+y)*len+x] = 0x00FF4500;
            }
        }
    }
}

// Overwrite an existing box by returning pixels to the gray of the border

void removeFocus (int xStart, int *pPixels, int len)
{
    int tileLength = 25;
    
    for (int x = xStart; x < xStart + tileLength; x++)
    {
        for (int y = 0; y < tileLength; y++)
        {
            if (y == 0 || y == tileLength-1 || x == xStart || x == xStart + tileLength -1)
            {
                pPixels[(len+y)*len+x] = 0x00A9A9A9;
            }
        }
    }
}


// Main program loop - sets up the canvas and detects and handles user events

int main(int argc, const char * argv[]) {
    
    int canvasSideLength = 400;     // Side length of canvas - canvas is square
    
    SDL_Window *pDisplay = setUpWindow(canvasSideLength);
    SDL_Surface *pSurface = SDL_GetWindowSurface(pDisplay);
    int *pPixels = (int *)pSurface->pixels;
    
    // Draw the white canvas background and the tool tray
    
    drawBackground(pPixels, canvasSideLength);
    drawTools(pPixels, canvasSideLength);
    SDL_UpdateWindowSurface(pDisplay);
    
    // Define helpful coordinates for tool setting
    
    const int WHITE_POS = 250;
    const int BLACK_POS = 200;
    const int PENCIL_POS = 0;
    const int BUCKET_POS = 25;
    const int TILE_WIDTH = 25;

    // Set up the program with the tool on pencil and give focus to pencil
    
    bool buttonPressed = false;
    bool pencil = true;
    int toolFocusX = PENCIL_POS;
    giveFocus(toolFocusX, pPixels, canvasSideLength);
    
    
    // Set up the initial fill color (white) and line color (black) and give focus to the line color
    
    int fillColor = 0x00ffffff;
    int fillColorFocusX = WHITE_POS; //Position of starting fill color swatch (white)
    int lineColor = 0x00000000;
    int lineColorFocusX = BLACK_POS; //Position of starting line color swatch (black)
    giveFocus(lineColorFocusX, pPixels, canvasSideLength);
    
    
    // Initialize  variables that will hold the last X and Y coord (to draw lines between points)
    
    int lastXCoord = 0;
    int lastYCoord = 0;
    
    // Event handling loop (below) based on Lazy Foo SDL Tutorial 03
    
    SDL_Event event;
    bool running = true;
    
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
                if (mEvent.y < canvasSideLength)    // Click occurred on the main canvas - user is drawing
                {
                    if(pencil)
                    {
                        setPixel(mEvent.x, mEvent.y, pPixels, canvasSideLength, lineColor);
                        buttonPressed = true;
                        SDL_CaptureMouse(SDL_TRUE); // Allows tracking of mouse outside of window
                        lastXCoord = mEvent.x;
                        lastYCoord = mEvent.y;
                    }
                    else
                    {
                        fillWithPaint(pPixels, mEvent.x, mEvent.y, canvasSideLength, fillColor);
                    }
                }
                else    // Click occurred on tool tray - user wants to change tools or colors
                {
                    if (mEvent.x < PENCIL_POS + TILE_WIDTH) // User clicked on pencil
                    {
                        pencil = true;
                        removeFocus(toolFocusX, pPixels, canvasSideLength);
                        toolFocusX = PENCIL_POS;
                        giveFocus(toolFocusX, pPixels, canvasSideLength);
                        removeFocus(fillColorFocusX, pPixels, canvasSideLength);
                        giveFocus(lineColorFocusX, pPixels, canvasSideLength);
                        
                    }
                    else if (mEvent.x < BUCKET_POS + TILE_WIDTH) // User clicked on paint bucket
                    {
                        pencil = false;
                        removeFocus(toolFocusX, pPixels, canvasSideLength);
                        toolFocusX = BUCKET_POS;
                        giveFocus(toolFocusX, pPixels, canvasSideLength);
                        removeFocus(lineColorFocusX, pPixels, canvasSideLength);
                        giveFocus(fillColorFocusX, pPixels, canvasSideLength);
                    }
                    else
                    {
                        if (pencil)
                        {
                            lineColor = setColor(mEvent, pPixels, canvasSideLength);
                            removeFocus(lineColorFocusX, pPixels, canvasSideLength);
                            lineColorFocusX = mEvent.x - mEvent.x % TILE_WIDTH;
                            giveFocus(lineColorFocusX, pPixels, canvasSideLength);
                        }
                        else
                        {
                            fillColor = setColor(mEvent, pPixels, canvasSideLength);
                            removeFocus(fillColorFocusX, pPixels, canvasSideLength);
                            fillColorFocusX = mEvent.x - mEvent.x % TILE_WIDTH;
                            giveFocus(fillColorFocusX, pPixels, canvasSideLength);
                        }
                    }
                }
            }
            else if (buttonPressed && event.type == SDL_MOUSEBUTTONUP)
            {
                buttonPressed = false;
                SDL_CaptureMouse(SDL_FALSE);
                SDL_MouseButtonEvent mEvent = *(SDL_MouseButtonEvent *)&event;
                drawLine(lastXCoord, lastYCoord, mEvent.x, mEvent.y, pPixels, canvasSideLength, lineColor);
            }
            else if (buttonPressed && event.type == SDL_MOUSEMOTION)
            {
                SDL_MouseMotionEvent mEvent = *(SDL_MouseMotionEvent *)&event;
                drawLine(lastXCoord, lastYCoord, mEvent.x, mEvent.y, pPixels, canvasSideLength, lineColor);
                lastXCoord = mEvent.x;
                lastYCoord = mEvent.y;
            }
            SDL_UpdateWindowSurface(pDisplay);
        }
    }
    
    
    // Clean up the surface and window before closing
    
    SDL_FreeSurface(pSurface);
    SDL_DestroyWindow(pDisplay);
    
    SDL_Quit();
    
    return 0;
}
