#ifndef STDARG_H
#define STDARG_H

// https://stackoverflow.com/questions/32291808/how-to-implement-stdarg-in-c

/*
	* Copyright (c) 1992 David I. Bell
	* Permission is granted to use, distribute, or modify this source,
	* provided that this copyright notice remains intact.

	* SIMULATE_STDARG
	*
	* WARNING: This type of stdarg makes assumptions about the stack
	*             that may not be true on your system.  You may want to
	*            define STDARG (if using ANSI C) or VARARGS.
*/

typedef char	*va_list;

#define	va_start(ap,parmn)	(void)((ap) = (char*)(&(parmn) + 1))
#define	va_end(ap) 			(void)((ap) = 0)
#define	va_arg(ap, type)	(((type*)((ap) = ((ap) + sizeof(type))))[-1])

#endif