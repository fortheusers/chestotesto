#include <cstdio>
#include "chestoincludes.hpp"
#include "main.hpp"

using namespace std;
using namespace Chesto;

// A Chesto Screen implements three methods: process, render, and rebuildUI
class MainScreen : public Chesto::Screen
{
public:
  // Stateful variables can go here, which either persist or get reconstructed, depending on your app's lifecycle
  int scrollspeed = 1;
  bool physicsOn = false;

  hsv backgroundColor = {0, .55, .45};
  
  //Physics constants.
  float vx = 3;
  float vy = 4;

  // raw pointer references to allow us to manipulate them without rebuilding
  NetImageElement* logo;
  TextElement* lowdown;

  MainScreen() {
    super();
    this->rebuildUI();
    this->hasBackground = true;
  }

  void incPercent(ProgressBar* pbar) {
    pbar->percent = fmod((pbar->percent+0.01), 1);
  }
  void dumbButtonFunc() {
    printf("Why on *earth* would you press the dumb button?\n");
    scrollspeed=-scrollspeed;
    physicsOn=true;

    //clear constraints on the image logo, else it won't be able to move
    logo->constraints.clear();
  }

  bool process(Chesto::InputEvents* events) override {
    // Process input events here
    if(events->pressed(UP_BUTTON) || events->pressed(START_BUTTON)) scrollspeed++;
    if(events->pressed(DOWN_BUTTON) || events->pressed(SELECT_BUTTON)) scrollspeed--;

    //Fade background hue and spin the logo. Deliberately not using modulo here to avoid negative direction issues.
    backgroundColor.h+=(float)scrollspeed*2/10;
    if(backgroundColor.h>=(SCREEN_H/2)) backgroundColor.h=0;
    if(backgroundColor.h<0) backgroundColor.h=(SCREEN_H/2);
    logo->angle=backgroundColor.h;

    // update our bg color on the actual view with our local variable
    ((Element*)this)->backgroundColor=hsv2rgb(backgroundColor);

    //Scroller logic.
    lowdown->position((lowdown->x)-scrollspeed, lowdown->y);
    if(lowdown->x+lowdown->width<0 && scrollspeed >= 0) lowdown->position(SCREEN_W,SCREEN_H-lowdown->height); //Wraparound the scroller.
    if(lowdown->x>SCREEN_W && scrollspeed < 0) lowdown->position(-lowdown->width,SCREEN_H-lowdown->height);

    //Bouncing physics.
    if(physicsOn)
    {
      logo->position(logo->x+vx, logo->y+(int)vy);
      vy+=0.25;
      if(logo->y+logo->height>=lowdown->y) vy*=-0.97;
      if(logo->x <= 0 || logo->x+logo->width >= SCREEN_W) vx*=-.99;
    }
  
    // bubble up for any lifecycle events
    // returning false here means that render is not called
    return Chesto::Screen::process(events) || true; // for chestotesto, we always render (bg changes, lowdown scrolls)
  }

  void render(Element* parent) override {
    // Render additional non-Element UI here, like rectangles or other raw graphics
    // or override this to control the order in which Elements render, if it needs to be customized beyond using the rendering tree
    Chesto::Screen::render(parent);
  }

  void rebuildUI() override {
    /*Instantiate on-screen elements.*/
    auto title = createChild<TextElement>("Welcome to ChestoTesto!", 48)
      ->constrain(ALIGN_CENTER_HORIZONTAL)
      ->constrain(ALIGN_TOP, SCREEN_H/3);

    createChild<Button>("Exit", B_BUTTON)
      ->constrain(ALIGN_TOP | ALIGN_RIGHT, 10)
      ->setAction([] { RootDisplay::mainDisplay->requestQuit(); });

    auto pbar = createChild<ProgressBar>();
    pbar->constrain(ALIGN_CENTER_HORIZONTAL)
      ->constrainToTarget(title, ALIGN_BOTTOM, 0);

    // TODO: Use a vertical Container for all these elements, instead of manual constraints

    auto url = "https://github.com/fortheusers/chesto/raw/main/logo.png";
    logo = createChild<NetImageElement>(url, []() -> Texture* {
        return new ImageElement(RAMFS "res/LOCAL.png");
    }, true);
    logo->constrain(ALIGN_CENTER_HORIZONTAL)
      ->constrainToTarget(title, ALIGN_TOP, 5); // align 5px above title
    logo->setSize(SCREEN_H/14.4, SCREEN_H/14.4);

    auto progressButton = createChild<Button>("Progress!", A_BUTTON)
      ->constrain(ALIGN_CENTER_HORIZONTAL)
      ->constrainToTarget(pbar, ALIGN_BOTTOM, 70)
      ->setAction([this, pbar] { incPercent(pbar); });

    createChild<Button>("Don't press me, I'm a dumb button", X_BUTTON)
      ->constrain(ALIGN_CENTER_HORIZONTAL)
      ->constrainToTarget(progressButton, ALIGN_BOTTOM, 15)
      ->setAction([this] { dumbButtonFunc(); });

    // auto list = createChild<ListElement>()
    //   ->setPosition(0, 0);

    std::string ldt (std::string("Technical lowdown v") + version + std::string(": ") + lowdownText);
    lowdown = createChild<TextElement>(ldt.c_str(), 35);
    lowdown->constrain(ALIGN_BOTTOM)
      ->setPosition(SCREEN_W, 0); // start offscreen to the right
  }

  ~MainScreen() {
    /*If you need any de-init code, do it here.*/
  }
};

// actual entry point
int main(int, char**)
{
  printf("ChestoTesto! Now initializing...\n");
  auto display = make_unique<RootDisplay>();

  // display our main screen
  display->pushScreen(make_unique<MainScreen>());

  // event loop logic is handled by RootDisplay
  return display->mainLoop();
}