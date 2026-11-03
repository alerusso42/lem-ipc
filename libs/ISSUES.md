## sdl_setup issues

On my PC, I have found dependencies problems in installing SDL3 and SDL3_ttf.
If you have access to sudo, you can do as follows.

#### SDL3

There's a useful HTML page offered by SDL team.

```url
https://wiki.libsdl.org/SDL3/README-linux#build-dependencies
```

#### SDL3_ttf

In the dependencies of SDL_ttf (shown in the 'external' directory)
there is freetype, that gave me problems. There is a shell script in the 
directory ('download.sh'), however you can just install it.

Ubuntu:
```bash
sudo apt-get install libfreetype-dev
```

source:
```url
https://stackoverflow.com/questions/79293876/cmake-sdl3-ttf-how-create-as-subdirectory
```
```url
https://openclassrooms.com/forum/sujet/installation-sdlttf-sous-linux-77248
```