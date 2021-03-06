/*************************************************************************/
/* Copyright (c) 2004                                                    */
/* Daniel Sleator, David Temperley, and John Lafferty                    */
/* Copyright (c) 2009 Linas Vepstas                                      */
/* All rights reserved                                                   */
/*                                                                       */
/* Use of the link grammar parsing system is subject to the terms of the */
/* license set forth in the LICENSE file included with this software.   */ 
/* This license allows free redistribution and use in source and binary  */
/* forms, with or without modification, subject to certain conditions.   */
/*                                                                       */
/*************************************************************************/
#ifndef _LINK_GRAMMAR_ERROR_H_
#define _LINK_GRAMMAR_ERROR_H_

#include "link-includes.h"

/* User verbosity levels are 1-4, to be used for user info/debug.
 * For now hard-coded numbers are still used instead of D_USER_BASIC/TIMES. */
#define D_USER_BASIC 1   /* Basic verbosity level. */
#define D_USER_TIMES 2   /* Display step times. */
#define D_USER_FILES 3   /* Display data file search and locale setup. */
// #define D_USER_X  4   /* Not in use yet. */
#define D_USER_MAX   4   /* Maximum user verbosity level. */

typedef struct
{
	Sentence sent;
} err_ctxt;

typedef enum
{
	Fatal = 1,
	Error,
	Warn,
	Info,
	Debug
} severity;

void err_msg(err_ctxt *, severity, const char *fmt, ...) GNUC_PRINTF(3,4);
const char *feature_enabled(const char *, ...);

/**
 * Print a debug message at verbosity >= level.
 * Preceding the level number by a + (+level) adds printing of the
 * function name.
 * Level numbers 2 to D_USER_MAX are not printed on verbosity>D_USER_MAX,
 * because they are designed only for extended user information.
 * The !debug variable can be set to a comma-separated list of functions
 * in order to restrict the debug messages to these functions only.
 */
#define lgdebug(level, ...) \
(((verbosity>=(level)) && (((level)<=1) || \
	!(((level)<=D_USER_MAX) && (verbosity>D_USER_MAX))) && \
	(('\0' == debug[0]) || \
	feature_enabled(debug, __func__, __FILE__, NULL))) \
	? ((STRINGIFY(level)[0] == '+' ? (void)printf("%s: ", __func__) : (void)0), \
	(void)printf(__VA_ARGS__)) : (void)0)

/**
 * Wrap-up a debug-messages block.
 * Preceding the level number by a + (+level) adds printing of the
 * function name.
 * The !debug variable can be set to a comma-separated list of functions
 * in order to restrict the debug messages to these functions only.
 *
 * Return true if the debug-messages block should be executed, else false.
 *
 * Usage example, for debug messages at verbosity V:
 * if (debug_level(V))
 * {
 * 	print_disjunct(d);
 * }
 */
#define debug_level(level) \
(((verbosity>=(level)) && (((level)<=1) || \
	!(((level)<=D_USER_MAX) && (verbosity>D_USER_MAX))) && \
	(('\0' == debug[0]) || \
	feature_enabled(debug, __func__, __FILE__, NULL))) \
	? ((STRINGIFY(level)[0] == '+' ? printf("%s: ", __func__) : 0), true) \
	: false)

/**
 * Return TRUE if the given feature (a string) is set in the !test variable
 * (a comma-separated feature list).
 */
#define test_enabled(feature) \
	(('\0' != test[0]) ? feature_enabled(test, feature, NULL) : NULL)

#endif
