#include <cstdio>
#include "chestoincludes.h"

bool running = true;
void quit(){running=false;}

int main(int argc, char* argv[])
{
  printf("ChestoTesto! Now initializing...");
  RootDisplay* display = new RootDisplay();
	InputEvents* events = new InputEvents(); // the main input handler
  printf("done.\n");


  long frames=0;

  ProgressBar* pbar = new ProgressBar();
  pbar->position(401, 480);
  display->elements.push_back(pbar);

  TextElement* title = new TextElement("Hi there!", 36);
  title->position(410, 460);
  display->elements.push_back(title);

  Button* exitButton = new Button("Exit", B_BUTTON);
  exitButton->position(0,0);
  display->elements.push_back(exitButton);
  exitButton->action = std::bind(quit);

	while (running)
	{
		bool atLeastOneNewEvent = false;
		// get any new input events
		while (events->update())
		{
			// process the inputs of the supplied event
      //if (events->pressed(B_BUTTON)) return 0;
      display->process(events);
			atLeastOneNewEvent = true;
      if (events->pressed(A_BUTTON)) pbar->percent = fmod((pbar->percent+0.01), 1);
      printf("New input event, d'oh! %f \%\n", pbar->percent);
		}

		// one more event update if nothing changed or there were no previous events seen
		// needed to non-input related processing that might update the screen to take place
		//if ((!atLeastOneNewEvent && !viewChanged) || display->showingSplash)
		//{
			events->update();
		//	viewChanged |= display->process(events);
		//}
		display->render(NULL); //Render all the things.
		//HBAS has a framelimiter here to avoid redrawing frames if there's no new input (or above 60fps).
    //This currently requires direct SDL2 calls for timing, though.
	}
	return 0;
}
