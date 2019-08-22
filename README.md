miscela
=====================================
`miscela` is an openFrameworks app i use to layer GLSL fragment shaders and `np-pixelscript` lua scripts. Still highly experimental.

usage is something like this:
```
miscela  /path/to/optional/config.json /path/to/shader.frag /other/shader.frag 
```
Fragment shader use the last script/fragment output as uniform `u_tex0`, png/jpg/gif/bmp images and mov/mp4 video  can be passed and they are overlayed. `.json` files can be passed to set some configs.

You need [ofxDotFrag](https://github.com/npisanti/ofxDotFrag) and [np-pixelscript](https://github.com/npisanti/np-pixelscript)

miscela Nicola Pisanti MIT License 2019   
