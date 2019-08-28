#include <cstdio>
#include "chestoincludes.hpp"
#include "main.hpp"

bool running = true;
int scrollspeed = 1;
bool physicsOn = false;
void quit(){running=false;}
void incPercent(ProgressBar* pbar) {pbar->percent = fmod((pbar->percent+0.01), 1);}
void dumbButtonFunc() {printf("Why on *earth* would you press the dumb button?\n"); scrollspeed=-scrollspeed; physicsOn=true;}

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

  ImageElement* logo = new ImageElement(ROMFS "res/LOCAL.png");
  logo->resize(50, 50);
  logo->position(640-(logo->width/2), title->y-5-logo->height);
  display->elements.push_back(logo);

  Button* progressButton = new Button("Progress!", A_BUTTON);
  progressButton->position(640-(progressButton->width/2), pbar->y+10+pbar->height);
  display->elements.push_back(progressButton);
  progressButton->action = std::bind(incPercent, pbar);

  Button* dumbButton = new Button("Don't press me, I'm a dumb button", X_BUTTON);
  dumbButton->position(640-(dumbButton->width/2),progressButton->y+progressButton->height+10);
  display->elements.push_back(dumbButton);
  dumbButton->action = std::bind(dumbButtonFunc);

  ListElement* list = new ListElement();
  list->position(0, 0);
  display->elements.push_back(list);

  std::string ldt (std::string("Technical lowdown v") + version + std::string(": ") + lowdownText);
  TextElement* lowdown = new TextElement(ldt.c_str(), 35);
  lowdown->position(1280,720-lowdown->height);
  display->elements.push_back(lowdown);

  /*Button* buttons[10];
  for(int i=0; i<10; i++)
  {
    buttons[i]=new Button("HAI", 0);
    display->elements.push_back(buttons[i]);
  }*/

  hsv backgroundColor = {0, .55, .45};

  //Physics constants.
  float vx = 3;
  float vy = 4;


  /*Main loop.*/
	while (running)
	{
    bool atLeastOneNewEvent = false;
		while (events->update()) // get any new input events
		{
      display->process(events); // process the inputs of the supplied event
      if(events->pressed(UP_BUTTON) || events->pressed(START_BUTTON)) scrollspeed++;
      if(events->pressed(DOWN_BUTTON) || events->pressed(SELECT_BUTTON)) scrollspeed--;
			atLeastOneNewEvent = true;
		}

		// one more event update if nothing changed or there were no previous events seen
		// needed to non-input related processing that might update the screen to take place
    // This is imported from HBAS, wonder if it's even necessary?
		if (!atLeastOneNewEvent) events->update();

    //Fade background hue and spin the logo. Deliberately not using modulo here to avoid negative direction issues.
    backgroundColor.h+=(float)scrollspeed*2/10;
    if(backgroundColor.h>=360) backgroundColor.h=0;
    if(backgroundColor.h<0) backgroundColor.h=360;
    logo->angle=backgroundColor.h;
    display->backgroundColor=hsv2rgb(backgroundColor);

    //Scroller logic.
    lowdown->position((lowdown->x)-scrollspeed, lowdown->y);
    if(lowdown->x+lowdown->width<0 && scrollspeed >= 0) lowdown->position(1280,720-lowdown->height); //Wraparound the scroller.
    if(lowdown->x>1280 && scrollspeed < 0) lowdown->position(-lowdown->width,720-lowdown->height);

    //Bouncing physics.
    if(physicsOn)
    {
      logo->position(logo->x+vx, logo->y+(int)vy);
      vy+=0.25;
      if(logo->y+logo->height>=lowdown->y) vy*=-0.97;
      if(logo->x <= 0 || logo->x+logo->width >= 1280) vx*=-.99;
    }

		display->render(NULL); //Render all the things.
		//HBAS has a framelimiter here to avoid redrawing frames if there's no new input (or above 60fps).
    //This currently requires direct SDL2 calls for timing, though.
	}

  /*If you need any de-init code, do it here.*/
	return 0;
}
