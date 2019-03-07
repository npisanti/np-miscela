miscela
=====================================
`miscela` is an openFrameworks app i use to layer GLSL fragment shaders and Lua scripts in realtime. It also can be used as addon to have a sandbox for the very same files. Still highly experimental.

usage is something like this:
```
miscela /path/to/script.lua /path/to/shader.frag /other/shader.frag
```

Lua scripts are overlayed, fragment shader use the last script/fragment output as uniform `u_tex0`


For Lua scripting i'm using [nanovg](https://github.com/memononen/nanovg) binded with the help of [ofxLua](https://github.com/danomatika/ofxLua), that i just tweaked a bit. 


miscela Nicola Pisanti MIT License 2019   
ofxLua Copyright (c) Dan Wilcox 2011-2017   
nanovg Copyright (c) 2013 Mikko Mononen memon@inside.org    
