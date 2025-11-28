#ifndef __STRING__
#define __STRING__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <vector>
#include <iostream>

void THROW_ERROR(const char *fmt, ...);
void ERROR(const char *fmt, ...);
void ALERT(const char *fmt, ...);
#define THROW_ERROR(fmt,...) { \
			char tmps[1024]; \
			snprintf(tmps, sizeof(tmps), "%s[%d]:" fmt, __FUNCTION__, __LINE__, __VA_ARGS__); \
			throw Tools::String(tmps); \
		}
#define ERROR(fmt,...) fprintf(stderr, VT220_RED "ERROR!!!%s[%d]: " fmt VT220_RESET "\n", __FILE__, __LINE__, __VA_ARGS__)
#define ALERT(fmt,...) fprintf(stderr, VT220_YELLOW "ALERT!!!%s[%d]: " fmt VT220_RESET "\n", __FILE__, __LINE__, __VA_ARGS__)

typedef unsigned char uchar;
typedef unsigned int uint;

template<typename T> T min(T t1, T t2) {
	return ( t1 < t2? t1: t2 );
}

namespace Tools {
	typedef unsigned char uchar;
	typedef unsigned int uint;
	typedef int (cmp_fn)(const uchar*, const uchar*);
	typedef bool (sub_fn)(const uchar*, const uchar*);
	typedef const uchar* (str_fn)(const uchar*, const uchar*);

	class String;

	class Class {
		public:
			virtual String toString(void) const = 0;
			friend std::ostream& operator<<(std::ostream& stream, const Class& object);
	};

	class Blob: public Class {
		public:
			static const uchar *EMPTY;

		protected:
			uchar *mText;
			size_t mLength;
			bool mStrCompatible = false;
			static const char *mHexAscii;
			static const char *mFullAscii;

		public:
/*test*/	Blob(void): mText(const_cast<uchar*>(EMPTY)), mLength(0) {}
/*test*/	Blob(const uchar *str, size_t bytes = 0, bool is_binary = false);
/*test*/	Blob(const char *str, size_t bytes = 0): Blob((uchar*)str, bytes, false) {}
			Blob(const Blob& blob);
			virtual ~Blob(void);

		public:
/*test*/	Blob& operator=(const char *str);
/*test*/	Blob& operator=(const Blob& blob);
/*test*/	Blob& operator=(const String& string);
			bool operator==(const char *str);
			bool operator==(const Blob& blob);
/*test*/	uchar operator[](uint index) const;
/*test*/	virtual void clear(void);

/*test*/	bool isEmpty(void) const					{ return (mLength == 0); }
/*test*/	size_t getLength(void) const 				{ return mLength; }
/*test*/	const uchar *getText(void) const 			{ return mText; }
/**/		bool isStrCompatible(void) const			{ return mStrCompatible; }
/**/		String hexDump(void) const;
/*test*/	String toString(void) const;

		private:
			void copy(const uchar *str, size_t length, bool str_compatible);
	};

	class String: public Blob {
		public:
			static const uint BUFFER_SIZE = 250;

		private:
			uint mBufferSize = 0;

		public:
			static int my_strcmp(const unsigned char *str1, const unsigned char *str2);
			static int my_strcasecmp(const unsigned char *str1, const unsigned char *str2);
			static const unsigned char *my_strstr(const unsigned char *str, const unsigned char *sub);
			static const unsigned char *my_strcasestr(const unsigned char *str, const unsigned char *sub);
/*tested*/	static bool strsub(const char *str, const char *sub);
/*tested*/	static bool strcasesub(const char *str, const char *sub);

		private:
/*tested*/	cmp_fn *compare_fn = (cmp_fn*)my_strcmp;
/*tested*/	sub_fn *strsub_fn = (sub_fn*)strsub;
/*tested*/	str_fn *strstr_fn = (str_fn*)my_strstr;

		public:
/*tested*/	String(void): Blob(), mBufferSize(BUFFER_SIZE) {}
/*tested*/	String(const char *str, uint offset = 0, int bytes = -1);
/*tested*/	String(const String& string);
/*tested*/	virtual ~String(void) {}

		public: //--- Operator overloads
/*tested*/	bool operator==(const char *str) const;
/*tested*/	bool operator==(const String& string) const;
/*tested*/	friend bool operator==(const char* str, const String& string);

/*tested*/	bool operator!=(const char *str) const;
/*tested*/	bool operator!=(const String& string) const;
/*tested*/	friend bool operator!=(const char* str, const String& string);

/*tested*/	bool operator>=(const char *str) const;
/*tested*/	bool operator>=(const String& string) const;
/*tested*/	friend bool operator>=(const char* str, const String& string);

/*tested*/	bool operator<=(const char *str) const;
/*tested*/	bool operator<=(const String& string) const;
/*tested*/	friend bool operator<=(const char* str, const String& string);

/*tested*/	bool operator>(const char *str)  const;
/*tested*/	bool operator>(const String& string)  const;
/*tested*/	friend bool operator>(const char* str, const String& string);

/*tested*/	bool operator<(const char *str)  const;
/*tested*/	bool operator<(const String& string)  const;
/*tested*/	friend bool operator<(const char* str, const String& string);

/*tested*/	String& operator=(const char *str);
/*tested*/	String& operator=(const String& string);
/*tested*/	String& operator+=(const char *str);
/*untested*/String& operator+=(const String& string);
/*tested*/	String  operator+(const char *str) const;
/*tested*/	String  operator+(const String& string) const;
/*tested*/	friend String operator+(const char *str, const String& string);
/**/		friend std::ostream& operator<<(std::ostream& stream, const Class& object) { return stream << object.toString(); }
/**/		friend std::ostream& operator<<(std::ostream& stream, const String& string) { return stream << string.getText(); }

		public: //--- test methods
/*tested*/	bool startsWith(const String& sub, uint starting_at = 0) const;
/*tested*/	bool contains(const String& sub) const;

		public: //--- manipulation methods
/*tested*/	virtual void clear(void) override;
/*tested*/	std::vector<String> split(char key) const;
/*tested*/	String encode(void) const;
/*tested*/	String trimRight(void) const;
/*tested*/	String trimLeft(void) const;
/*tested*/	String trim(void) const;
/**/	static String toString(long long value, uint radix = 10);

		public: //--- getters/setters
/*tested*/	String toString(void) const override		{ return *this; }
/*tested*/	uint getBufferSize(void) const				{ return mBufferSize; }
/*tested*/	void setCaseCompare(bool ignore);

		private:
/*tested*/	void resize(uint new_size);

		public:
/*BORKED*/	static String formatString(const String& fmt, ...);
			static String wideCharToString(wchar_t wchar);
	};

	FILE *fopen(const String& filename, const String& permissions);
	bool fgets(String& buffer, FILE *fp);

	class File {
		public:
			static String readFile(const String& filename) {
			    FILE *fp = fopen(filename, "r");
				if (fp != NULL) {
					fseek(fp, 0, SEEK_END);
					size_t file_size = ftell(fp);
					fseek(fp, 0, SEEK_SET);
					char *buffer = new char[file_size + 1];
					size_t bytes_read = fread(buffer, 1, file_size, fp);
					fclose(fp);

					if ( bytes_read != file_size ) {
						delete [] buffer;
						throw String::formatString("Error reading file: expected %ld bytes, read %zu\n", file_size, bytes_read);
					}

					buffer[file_size] = '\0';
					return buffer;

				} else {
					throw String::formatString("Error opening file: %s", filename.getText());
				}
			}
	};
};

#endif
