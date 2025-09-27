#ifndef __STRING__
#define __STRING__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <vector>
#include <iostream>

#define VT220_RESET  "\x1B[0m"
#define VT220_RED    "\x1B[31m"
#define VT220_GREEN  "\x1B[32m"
#define VT220_YELLOW "\x1B[38;5;190m"

typedef unsigned char uchar;
typedef unsigned int uint;
typedef __int128_t int128_t;
typedef int (cmp_fn)(const unsigned char*, const unsigned char*);
typedef bool (sub_fn)(const unsigned char*, const unsigned char*);
typedef const unsigned char (str_fn)(const unsigned char*, const unsigned char*);

void THROW_ERROR(const char *fmt, ...);
void ERROR(const char *fmt, ...);
void ALERT(const char *fmt, ...);
#define THROW_ERROR(fmt,...) { \
			char tmps[1024]; \
			snprintf(tmps, sizeof(tmps), "%s[%d]:" fmt, __FUNCTION__, __LINE__, __VA_ARGS__); \
			throw String(tmps); \
			}
#define ERROR(fmt,...) fprintf(stderr, VT220_RED "ERROR!!!%s[%d]: " fmt VT220_RESET "\n", __FILE__, __LINE__, __VA_ARGS__)
#define ALERT(fmt,...) fprintf(stderr, VT220_YELLOW "ALERT!!!%s[%d]: " fmt VT220_RESET "\n", __FILE__, __LINE__, __VA_ARGS__)

template<typename T> T min(T t1, T t2) {
	return ( t1 < t2? t1: t2 );
}

namespace Tools {
	class String;

	class Class {
		public:
			virtual String ToString(void) const = 0;
			friend std::ostream& operator<<(std::ostream& stream, const Class& object);
	};

	class Blob: public Class {
		public:
			static const uchar *EMPTY;

		protected:
			uchar *text;
			size_t length;
			bool str_compatible = false;
			static const char *HexAscii;
			static const char *FullAscii;

		public:
/*test*/	Blob(void): text(const_cast<uchar*>(EMPTY)), length(0) {}
/*test*/	Blob(const char *str, size_t bytes = 0, bool is_binary = false);
/*test*/	Blob(const uchar *str, size_t bytes);
			Blob(const Blob& blob);
			virtual ~Blob(void);

		public:
/*test*/	Blob& operator=(const char *str);
/*test*/	Blob& operator=(const Blob& blob);
/*test*/	Blob& operator=(const String& string);
			bool operator==(const char *str);
			bool operator==(const Blob& blob);
/*test*/	uchar operator[](uint index) const;
/*test*/	void Clear(void);
/*test*/	bool IsEmpty(void) const          			{ return (length == 0); }
/*test*/	size_t GetLength(void) const 				{ return length; }
/*test*/	const uchar *GetText(void) const 			{ return text; }
/**/		String HexDump(void) const;
/*test*/	String ToString(void) const;

		private:
			void copy(const uchar *str, size_t length, bool str_compatible);
	};

	class String: public Blob {
		private:
			const int BUFFER_SIZE = 250;
			uint size = 0;

		private:
			static const unsigned char *my_strstr(const unsigned char *str, const unsigned char *sub);
			static const unsigned char *my_strcasestr(const unsigned char *str, const unsigned char *sub);
			static int my_strcmp(const unsigned char *str1, const unsigned char *str2);
			static int my_strcasecmp(const unsigned char *str1, const unsigned char *str2);
/*tested*/	static bool strsub(const uchar *str, const uchar *sub);
/*tested*/	static bool strcasesub(const uchar *str, const uchar *sub);
/*tested*/	cmp_fn *compare_fn = my_strcmp;
/*tested*/	sub_fn *strsub_fn = strsub;
/*tested*/	const uchar* (*strstr_fn)(const uchar*, const uchar*) = my_strstr;

		public:
/*tested*/	String(void): Blob(), size(0) {}
/*tested*/	String(const char *str, uint offset = 0, int bytes = -1);
/*tested*/  String(int128_t value, uint radix = 10);
/*tested*/	String(const String& string);
/*tested*/	virtual ~String(void) {}

		public: //--- Operator overloads
/*tested*/	bool operator==(const char *str) const;
/*tested*/	bool operator==(const String& string) const;
/*tested*/	friend bool operator==(const char* str, const String& string) {
				if ( (str == nullptr  ||  *str == 0)  ||  string.IsEmpty() ) {
					return false;
				}
				return (string.compare_fn((const unsigned char*)str, string.GetText()) == 0);
			}

/*tested*/	bool operator!=(const char *str) const;
/*tested*/	bool operator!=(const String& string) const;
/*tested*/	friend bool operator!=(const char* str, const String& string) {
				if ( (str == nullptr  ||  *str == 0)  ||  string.IsEmpty() ) {
					return false;
				}
				return (string.compare_fn((const unsigned char*)str, string.GetText()) != 0);
			}

/*tested*/	bool operator>=(const char *str) const;
/*tested*/	bool operator>=(const String& string) const;
/*tested*/	friend bool operator>=(const char* str, const String& string) {
				if ( (str == nullptr  ||  *str == 0)  ||  string.IsEmpty() ) {
					return false;
				}
				return (string.compare_fn((const unsigned char*)str, string.GetText()) >= 0);
			}

/*tested*/	bool operator<=(const char *str) const;
/*tested*/	bool operator<=(const String& string) const;
/*tested*/	friend bool operator<=(const char* str, const String& string) {
				if ( (str == nullptr  ||  *str == 0)  ||  string.IsEmpty() ) {
					return false;
				}
				return (string.compare_fn((const unsigned char*)str, string.GetText()) <= 0);
			}

/*tested*/	bool operator>(const char *str)  const;
/*tested*/	bool operator>(const String& string)  const;
/*tested*/	friend bool operator>(const char* str, const String& string) {
				if ( (str == nullptr  ||  *str == 0)  ||  string.IsEmpty() ) {
					return false;
				}
				return (string.compare_fn((const unsigned char*)str, string.GetText()) > 0);
			}

/*tested*/	bool operator<(const char *str)  const;
/*tested*/	bool operator<(const String& string)  const;
/*tested*/	friend bool operator<(const char* str, const String& string) {
				if ( (str == nullptr  ||  *str == 0)  ||  string.IsEmpty() ) {
					return false;
				}
				return (string.compare_fn((const unsigned char*)str, string.GetText()) < 0);
			}


/*tested*/	String& operator=(const char *str);
/*tested*/	String& operator=(const String& string);
/*tested*/	String& operator+=(const char *str);
/*untested*/String& operator+=(const String& string);
/*tested*/	String  operator+(const char *str) const;
/*tested*/	String  operator+(const String& string) const;
/**/		friend std::ostream& operator<<(std::ostream& stream, const Class& object) {
				stream << object.ToString();
				return stream;
			}
/**/		friend std::ostream& operator<<(std::ostream& stream, const String& string) {
				stream << string.GetText();
				return stream;
			}
/*tested*/	friend String operator+(const char *str, const String& string) {
				char tmps[strlen(str) + string.length + 1];
				snprintf(tmps, sizeof(tmps), "%s%s", str, string.text);
				return tmps;
			}

		public: //--- manipulation methods
/*tested*/	bool StartsWith(const String& sub, uint starting_at = 0) const;
/*tested*/	bool Contains(const String& sub) const;
/**/		String ToString(void) const override		{ return *this; }
/*tested*/	std::vector<String> Split(char key) const;

		public: //--- getters/setters
/*tested*/	uint GetSize(void) const        			{ return size; }
/*tested*/	void SetCaseCompare(bool ignore);

		private:
/*BORKED*/	void resize(uint new_size);

		public:
/*BORKED*/	static String FormatString(const String& fmt, ...);
	};

	FILE *fopen(const String& filename, const String& permissions);
	bool fgets(String& buffer, FILE *fp);
};

#endif
