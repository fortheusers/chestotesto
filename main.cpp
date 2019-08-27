#include <cstdio>
#include "chestoincludes.h"

bool running = true;
void quit(){running=false;}
void incPercent(ProgressBar* pbar) {pbar->percent = fmod((pbar->percent+0.01), 1);}

int main(int argc, char* argv[])
{
  printf("ChestoTesto! Now initializing...");
  RootDisplay* display = new RootDisplay();
	InputEvents* events = new InputEvents(); // the main input handler
  printf("done.\n");

  /*Instantiate on-screen elements.*/
  TextElement* title = new TextElement("Welcome to ChestoTesto!", 48);
  title->position(640-(title->width/2), 240);
  display->elements.push_back(title);

  Button* exitButton = new Button("Exit", B_BUTTON);
  exitButton->position(1280-(exitButton->width),0);
  display->elements.push_back(exitButton);
  exitButton->action = std::bind(quit);

  ProgressBar* pbar = new ProgressBar();
  pbar->position(640-(pbar->width/2), 360);
  display->elements.push_back(pbar);

  Button* progressButton = new Button("Progress!", A_BUTTON);
  progressButton->position(640-(progressButton->width/2), pbar->y+10+pbar->height);
  display->elements.push_back(progressButton);
  progressButton->action = std::bind(incPercent, pbar);

  Button* dumbButton = new Button("Don't press me, I'm a dumb button", X_BUTTON);
  dumbButton->position(640-(dumbButton->width/2),progressButton->y+progressButton->height+10);
  display->elements.push_back(dumbButton);
  dumbButton->action = std::bind(printf, "Why on *earth* would you press the dumb button?\n");

  /*Main loop.*/
	while (running)
	{
		bool atLeastOneNewEvent = false;
		while (events->update()) // get any new input events
		{
      display->process(events); // process the inputs of the supplied event
			atLeastOneNewEvent = true;
		}

		// one more event update if nothing changed or there were no previous events seen
		// needed to non-input related processing that might update the screen to take place
    // This is imported from HBAS, wonder if it's even necessary?
		if (!atLeastOneNewEvent) events->update();

		display->render(NULL); //Render all the things.
		//HBAS has a framelimiter here to avoid redrawing frames if there's no new input (or above 60fps).
    //This currently requires direct SDL2 calls for timing, though.
	}

  /*If you need any de-init code, do it here.*/
	return 0;
}
