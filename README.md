# Raylib Pong
**Pong game created with Raylib**

Just a test with plain C and Raylib. Checking old school game development!

## Some thoughts about this development
This is a pet project and I did it to get in touch with Raylib. I found awesome that I coud deliver a game within 2 days not knowing Raylib previously. This is a bare-bones library: no sprites, no engine, no elaborated gimmicks.

**Good things**

- Raylib is **small**. You can link it either dynamically or statically. If you are building your program with static linking the resulting executable file is going to be reasonably small, so you can distribute it easily.
- It is **straightforward**. Functions are properly named and self-documented.
- It is **modular and well organized**.
- `raylib.h` **contains all the information** required to write code. This is the same info you can read here. Just open the file in another tab of your editor and show it when required.
- It manages to abstract inconvinient boilerplate code so your programs are less cluttered. **_Noise to Signal ratio_ in your code is low**. This is important.

**Bad things**

- It seems that there are **discrepancies** between the documentation in the [wiki](https://github.com/raysan5/raylib/wiki) and what you find trying to build a project. There is a prepackaged version for Windows, which it is great, but you still have to make changes in paths, etc., and binaries are not generated where documentation states. You have to create some folders.
- I had almost no problems configuring and running my project in Linux but in Windows (same machine) it runs at 2fps instead of 60fps, and I don't know why.
- It took me a while to get it running in macOS. At first, it was a problem of installing the library with `brew`. This version (`2.0.0`) is not the last version (`2.4-dev`) that was in the repository when I cloned it in Linux. I guess I used some future functions that didn't appear in version `2.0.0`.
- I found it **difficult to configure XCode** to produce a static application that I could distribute to my friends. I gave up. It compiles dinamically and runs, yes, but I am a bit inept and I couldn't build a complete macOS app.
- I also gave up trying to build the **HMTL5** version of the program. I installed nodejs and all the other auxiliary elements. I even managed to create `libraylib.bc`, but no way to finish a complete build. `Makefile` seems to be configured only for Windows for building HTML5.
