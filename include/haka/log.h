
#ifndef _HAKA_LOG_H
#define _HAKA_LOG_H

#include <wchar.h>
#include <haka/types.h>
#include <haka/container/list.h>


typedef enum {
	HAKA_LOG_FATAL,
	HAKA_LOG_ERROR,
	HAKA_LOG_WARNING,
	HAKA_LOG_INFO,
	HAKA_LOG_DEBUG,

	HAKA_LOG_LEVEL_LAST
} log_level;

const char *level_to_str(log_level level);
void message(log_level level, const wchar_t *module, const wchar_t *message);
void messagef(log_level level, const wchar_t *module, const wchar_t *fmt, ...);
void setlevel(log_level level, const wchar_t *module);
log_level getlevel(const wchar_t *module);

struct logger {
	struct list   list;
	void        (*destroy)(struct logger *state);
	int         (*message)(struct logger *state, log_level level, const wchar_t *module, const wchar_t *message);
	bool          mark_for_remove;
};

void enable_stdout_logging(bool enable);
bool stdout_message(log_level lvl, const wchar_t *module, const wchar_t *message);

bool add_logger(struct logger *logger);
bool remove_logger(struct logger *logger);
void remove_all_logger();

#endif /* _HAKA_LOG_H */
