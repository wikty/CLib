#ifndef STR_MATCH_H_
#define STR_MATCH_H_


/*
 *	@function
 *		Name:				Ordinary Perfix String Match
 *		Time-Performance:	O(n*m)
 *	@return
 *		-1 => don't match
 *		num => the position of start
 */

extern int prefix_str_match(const char *str, const char *pattern);

/*
 *	@function
 *		Name:				Ordinary Suffix String Match
 *		Time-Performance:	O(n*m)
 */
extern int suffix_str_match(const char *str, const char *pattern);

/*
 *	@function
 *		Name:				KMP String Match
 *		Time-Performance:	O(n/m) ~ O(n)
 *		Description:		The improved version of perfix match
 */
extern int kmp_str_match(const char *str, const char *pattern);

/*
 *	@function
 *		Name:				Boyer-Moore String Match
 *		Time-Performance:	O(n/(m+1))
 *		Description:		The improved version of suffix match
 */

extern int bm_str_match(const char *str, const char *pattern);

/*
 *	@function
 *		Name:				Horspool String Match
 *		Description:		The simplified version of BM
 */
extern int hp_str_match(const char *str, const char *pattern);

/*
 *	@function
 *		Name:				Sunday String Match
 *		Time-Performance:	O(n/m)
 */
extern int sd_str_match(const char *str, const char *pattern);

#endif