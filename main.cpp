#include <cstdio>
#include "libs/chesto/src/RootDisplay.hpp"

int main(int argc, char* argv[])
{
  printf("ChestoTesto! Now initializing...");
  RootDisplay* display = new RootDisplay();
	InputEvents* events = new InputEvents(); // the main input handler
  printf("done.\n");

	bool running = true;
  long frames=0;

	while (running)
	{
		bool atLeastOneNewEvent = false;
    TextElement* title = new TextElement("Hi there!", 36);
    //display->elements.push_back(title);
    //display->elements.append(title);
		// get any new input events
		while (events->update())
		{
			// process the inputs of the supplied event
			printf("New input event, d'oh!\n");
      if (events->pressed(B_BUTTON)) return 0;
      display->process(events);
			atLeastOneNewEvent = true;

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
