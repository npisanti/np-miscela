miscela
=====================================
`miscela` is an openFrameworks app i use to layer GLSL fragment shaders and Lua scripts in realtime. Still highly experimental.

usage is something like this:
```
miscela /path/to/script.lua /path/to/shader.frag /other/shader.frag
```
Lua scripts are overlayed, fragment shader use the last script/fragment output as uniform `u_tex0`

You need [ofxLua](https://github.com/danomatika/ofxLua) and [ofxDotFrag](https://github.com/npisanti/ofxDotFrag).

miscela Nicola Pisanti MIT License 2019   
