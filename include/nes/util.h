#ifndef UTIL_BBD4DD2B5CBD4C30896BDF4F80C872AF_H
#define UTIL_BBD4DD2B5CBD4C30896BDF4F80C872AF_H

#include <string>
#include <cstdlib>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

namespace nes::util
{
	enum : char
	{
		lc_white,
		lc_green,
		lc_yellow,
		lc_red
	};

#ifndef WIN32
	constexpr auto ANSI_CLEAR 				= "\033[2J\033[3J";
	constexpr auto ANSI_CONSOLE_TITLE_BEGIN = "\033]0;";
	constexpr auto ANSI_CONSOLE_TITLE_END 	= "\007";
	constexpr auto ANSI_RESET_CURSOR 		= "\033[H";
	constexpr auto ANSI_RESET_COLOR 		= "\033[0m";
	constexpr auto ANSI_WHITE 				= "\033[01;37m";
	constexpr auto ANSI_GREEN 				= "\033[01;32m";
	constexpr auto ANSI_YELLOW 				= "\033[01;33m";
	constexpr auto ANSI_RED 				= "\033[22;31m";
#endif

	inline void set_console_title(const std::string& text)
	{
#ifdef WIN32
		SetConsoleTitleA(text.c_str());
#else
		printf("%s%s%s", ANSI_CONSOLE_TITLE_BEGIN, text.c_str(), ANSI_CONSOLE_TITLE_END);
#endif
	}

	inline void clear_console()
	{
#ifdef WIN32
		const auto h = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_SCREEN_BUFFER_INFO inf{}; DWORD written{};
		GetConsoleScreenBufferInfo(h, &inf);
		FillConsoleOutputCharacterA(h, ' ', inf.dwSize.X * inf.dwSize.Y, {0, 0}, &written);
		FillConsoleOutputAttribute(h, inf.wAttributes, inf.dwSize.X * inf.dwSize.Y, {0, 0}, &written);
		SetConsoleCursorPosition(h, {0, 0});
#else
		printf("%s%s", ANSI_CLEAR, ANSI_RESET_CURSOR);
#endif
	}

	inline void set_color(char col)
	{
#ifdef WIN32
		WORD c{};
		switch (col)
		{
			case lc_white:
				c = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
				break;
			case lc_green:
				c = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
				break;
			case lc_red:
				c = FOREGROUND_RED | FOREGROUND_INTENSITY;
				break;
			case lc_yellow:
				c = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
				break;
			default:break;
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
#else
		std::string c{};
		switch (col)
		{
			case lc_white:
				c = ANSI_WHITE;
				break;
			case lc_green:
				c = ANSI_GREEN;
				break;
			case lc_red:
				c = ANSI_RED;
				break;
			case lc_yellow:
				c = ANSI_YELLOW;
				break;
			default:break;
		}

		printf("%s", c.c_str());
#endif
	}

	inline void clear_color()
	{
#ifdef WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
#else
		printf(ANSI_RESET_COLOR);
#endif
	}

	template<typename... F>
	inline void log_status(const std::string& status, char col, const std::string& text, F... fmt)
	{
		printf("[ ");

		set_color(col);
		printf("%s", status.c_str());
		clear_color();

		printf(" ] ");
		printf(text.c_str(), fmt...);
		printf("\n");
	}

	template<typename... F>
	inline void log_info(const std::string& text, F... fmt)
	{
		printf("[ INFO ] ");
		printf(text.c_str(), fmt...);
		printf("\n");
	}

	template<typename... F>
	inline void log_debug(const std::string& text, F... fmt)
	{
#ifdef _DEBUG
		log_status("DEBG", lc_white, text, fmt...);
#endif
	}

	template<typename... F>
	inline void log_ok(const std::string& text, F... fmt)
	{
		log_status(" OK ", lc_green, text, fmt...);
	}

	template<typename... F>
	inline void log_warning(const std::string& text, F... fmt)
	{
		log_status("WARN", lc_yellow, text, fmt...);
	}

	template<typename... F>
	inline void log_fail(const std::string& text, F... fmt)
	{
		log_status("FAIL", lc_red, text, fmt...);
	}
}

#endif //UTIL_BBD4DD2B5CBD4C30896BDF4F80C872AF_H
