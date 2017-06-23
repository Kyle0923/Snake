# Snake in C
A project I did in Sep 2016.

# Description
A console game developped in C. This was my first attempt in developping "games" in C. It built the base for my later console-based graphic programs.

# Takeaways
To produce a "graphic" output in a console window, point lattice may be a good solution. Using a two dimensional character array, I was able to map the gaming area. The indexes are the X & Y coordinates and the character is the pattern you want to show on that particular point.
Couples functions I found useful:
<conio.h>
kbhit() checks if keyboard is hit.
getch() gets a character without echo back on the screen. This function would block your thread, so I usually use kbhit() to check before call getch().
<stdlib.h>
sleep(int m_sec) on Windows, it suspends the thread for m_sec milliseconds. On some platforms, the parameter is second instead of millisecond.
system(string str) allows programmer to call console commands. system("cls") is helpful when you want to clean up the console screen.

Although this codes works, there are a lot to improve.
Overuse of global variables: could cause insecure data access.
Use of the "forbidden" goto.
Naming of variables and functions did not follow any convention. This can cause the codes hard to read.
