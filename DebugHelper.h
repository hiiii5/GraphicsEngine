// ReSharper disable CppClangTidyClangDiagnosticFormatNonliteral

#pragma once

#include <cstdarg>
#include <cstdio>
#include <malloc.h>
#include <string>

static std::string StringFormat(const char* Fmt, ...) {
	va_list argList;
	va_start(argList, Fmt);

	// SUSv2 version doesn't work for buf NULL/size 0, so try printing
	// into a small buffer that avoids the float-rendering and alloca path too...
	char shortBuf[256];
	const size_t needed = static_cast<size_t>(vsnprintf(shortBuf, sizeof shortBuf, Fmt, argList)) + 1;

	if (needed <= sizeof shortBuf) return shortBuf;


	auto p = static_cast<char*>(_malloca(needed)); // on stack
	vsnprintf(p, needed, Fmt, argList);
	return p; // text copied into returned string
}
