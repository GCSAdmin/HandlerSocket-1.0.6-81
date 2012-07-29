
// vim:sw=2:ai

/*
 * Copyright (C) 2010 DeNA Co.,Ltd.. All rights reserved.
 * See COPYRIGHT.txt for details.
 */

#ifndef DENA_CONFIG_HPP
#define DENA_CONFIG_HPP

#include <string>
#include <map>

static
void
print_timestamp(
/*===============*/
	FILE*  file) /*!< in: file where to print */
{
#ifdef __WIN__
	SYSTEMTIME cal_tm;

	GetLocalTime(&cal_tm);

	fprintf(file,"%02d%02d%02d %2d:%02d:%02d",
		(int)cal_tm.wYear % 100,
		(int)cal_tm.wMonth,
		(int)cal_tm.wDay,
		(int)cal_tm.wHour,
		(int)cal_tm.wMinute,
		(int)cal_tm.wSecond);
#else
	struct tm* cal_tm_ptr;
	time_t	   tm;
	time(&tm);

	cal_tm_ptr = localtime(&tm);

	fprintf(file,"%02d%02d%02d %2d:%02d:%02d ",
		cal_tm_ptr->tm_year % 100,
		cal_tm_ptr->tm_mon + 1,
		cal_tm_ptr->tm_mday,
		cal_tm_ptr->tm_hour,
		cal_tm_ptr->tm_min,
		cal_tm_ptr->tm_sec);
#endif
}

#define DENA_VERBOSE(lv, x) if (dena::verbose_level >= (lv)) { print_timestamp(stderr); (x); }

namespace dena {

struct config : public std::map<std::string, std::string> {
  std::string get_str(const std::string& key, const std::string& def = "")
    const;
  long long get_int(const std::string& key, long long def = 0) const;
};

void parse_args(int argc, char **argv, config& conf);

extern unsigned int verbose_level;

};

#endif

