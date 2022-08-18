#pragma once
#include <cstdarg>
#include <cstdio>
#include <malloc.h>
#include <string>

static std::string Stringf(const char* Fmt, ...) {
	va_list arg_list;
	va_start(arg_list, Fmt);

	// SUSv2 version doesn't work for buf NULL/size 0, so try printing
	// into a small buffer that avoids the float-rendering and alloca path too...
	char short_buf[256];
	const size_t needed = vsnprintf(short_buf, sizeof short_buf,
									Fmt, arg_list) + 1;
	if (needed <= sizeof short_buf) return short_buf;


	auto p = static_cast<char*>(alloca(needed)); // on stack
	vsnprintf(p, needed, Fmt, arg_list);
	return p; // text copied into returned string
}
