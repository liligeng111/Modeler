#ifndef UTIL_H__
#define UTIL_H__
/*
This file is added by Odin
Put here all the utility functions, 
which include, but not necessarily:

debug functions:
output to console, output to specific log file.
print mat3 and mat4 matrix.

view some internal image buffer in a new window
(The function I considered adding in impressionist.)

Miscellaneous functions regarding various trivial bonus.
for sophisticated bonus, should create separate files.
*/

/*
The secrete of showing a console while program is running:
select MTd or MDd mode for c runtime library ?
ensure about the flag: _CONSOLE or -mconsole ?? 
still quite confused about the c runtime library...
this is not the right way of learning...

Anyway, switching to release mode will get rid of the black console.
*/

/*
One issue for my updated is, now the generated executable
may not be as portable as before, because it will rely on some .dll file in system.
*/


#endif // UTIL_H__