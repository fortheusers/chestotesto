# ChestoTesto
[![MIT License](https://img.shields.io/badge/license-MIT-blue.svg?style=flat-square)](https://opensource.org/licenses/MIT) [![discord](https://img.shields.io/discord/339118412414582786.svg?color=blueviolet&label=discord&style=flat-square)](https://discordapp.com/invite/F2PKpEj)

Just a little barebones app written by [CompuCat](https://compucat.me) to test [Chesto](https://gitlab.com/4TU/chesto), the GUI library behind the Homebrew App Store. Targeting PC at first, but the eventual goal is to make this a test app to:
- Validate any Chesto platform
- Test new Chesto features
- Serve as an example "How to build for Chesto" app.

Chesto things not yet implemented:
- DownloadQueue
- ListElement
- Music

### Controls
- Pressing (A) progresses the progress bar.
- Pressing (B) exits ChestoTesto.
- Pressing up or down controls the speed of the scroller. (So does plus/minus...or start/select.)
- Pressing (X) does the same thing as pressing the dumb button...and why on *earth* would you press the dumb button?

### Technical lowdown:
*(This text is also in the bottom scroller.)*

Technical lowdown v\<ChestoTesto version\>: All the text pieces (including this scroller) are TextElements. This scroller is also an annoyingly wide TextElement - too large to be contained in a single texture, so it's stored as a giant surface and there's some funky on-the-fly cropping instead going on. If you're reading this, then text rendering, font loading, and large surfaces all work! The buttons are...well, Buttons; you can test InputEvents by interacting with them. Pressing (A) should also let you test the ProgressBar in the center of the screen. The spinning check mark is an ImageElement with a brand-new Chesto feature...rotation! Background colors are just a constant HSV fade modifying the RootDisplay every loop. That's about it! This is kinda demosceney, so greetings to: vgmoose, rw, quarky, crc32, pwsincd, Whovian9369, and the rest of 4TU staff and community, plus satelliteseeker, lft, and probably somebody I'm forgetting. This is CompuCat signing off. ~~

#### Building for PC
```
#Install dependencies on Ubuntu/Debian-alikes
sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-gfx-dev gcc g++ git

git clone --recursive https://gitlab.com/4TU/chestotesto
cd chestotesto
make
```

### License
This software is licensed under the MIT License.
