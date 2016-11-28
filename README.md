# PunyPaint

PunyPaint started life as a flood fill algorithm written for the command line. It's gradually developed into a flood fill implementation using SDL in which you can also draw lines and select colors - a kind of miniature paint program. PunyPaint has a long (long long) way to go before it's going to displace real paint programs, but it's a great sandbox for graphical display and interaction using C++ and SDL.

![](https://aos.iacpublishinglabs.com/question/aq/700px-394px/how-will-i-know-when-my-cat-is-ready-to-have-her-kittens_d689f18b-3b25-45a2-8f1d-f07c8ced23b4.jpg?domain=cx.aos.ask.com).

##How to run PunyPaint:

1. Clone the repo. If you build the program using Xcode, it will expect the repo to be cloned directly into Documents (i.e., /Documents/puny-paint where puny-paint is the cloned repo).

2. Install the SDL2 and SDL2_image libraries. You can find excellent system-specific instructions for [installing SDL2]() and [installing SDL2_image]() on Lazy Foo's SDL2 website. Make sure to put them where the site indicates.

3. **Option 1:** Run the pre-built executable. Go into the "Executable Version" folder of the repo and either double-click the flood-fill executable file (in Finder)) or run $ open flood-fill in the command line. PunyPaint should open. If you do not see a paint program-like window opening and see an error saying "Library not loaded," please make sure that you have both SDL2 and SDL2_image libraries installed according to the instructions in the above links.

4. **Option 2:** Open Xcode and peruse the code, then do the build yourself. If you put the repo immediately inside Documents, the image paths should work, but this may not be true for all systems. If you get image-related errors upon building and running, try clicking on one of the images in the resource folder and using the location panel in the dropdown at the right of the screen to see the location of the image "Relative to Build Products". If you tweak the paths in the drawTools method of main.cpp to match the path you see for the image location, this may fix your image loading errors.

If you get errors that are not fixed by installation of SDL2 or SDL2_image or by edits to the image paths, please [email me](mailto:emabrash@gmail.com) and I will try to figure out and fix the problem.

##Why doesn't it do X?

There is a lot that PunyPaint doesn't do...yet!

[TODO] Known issues/upcoming tasks:
* Add undo capability
* Make lines "non-dotted" (continuous) when mouse is moving fast
* Highlight current tool and color selection

##How can I learn to use SDL2?

I highly recommend [Lazy Foo's tutorials](http://lazyfoo.net/tutorials/SDL/index.php), which got (and continue to get) me off the ground, as well as the [SDL2 Wiki](https://wiki.libsdl.org/).
