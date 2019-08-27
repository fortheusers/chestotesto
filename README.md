# ChestoTesto
[![MIT License](https://img.shields.io/badge/license-MIT-blue.svg?style=flat-square)](https://opensource.org/licenses/MIT) [![discord](https://img.shields.io/discord/339118412414582786.svg?color=blueviolet&label=discord&style=flat-square)](https://discordapp.com/invite/F2PKpEj)

Just a little barebones app written by [CompuCat](https://compucat.me) to test [Chesto](https://gitlab.com/4TU/chesto), the GUI library behind the Homebrew App Store. Targeting PC at first, but the eventual goal is to make this a test app to:
- Validate any Chesto platform
- Test new Chesto features
- Serve as an example "How to build for Chesto" app.

Chesto things not yet implemented:
- DownloadQueue
- ImageElement
- ListElement
- Music

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
