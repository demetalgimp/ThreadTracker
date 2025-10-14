#include <string>
#include "Memory.hpp"

#define VT220_RESET  "\x1B[0m"
#define VT220_RED    "\x1B[31m"
#define VT220_GREEN  "\x1B[32m"
#define VT220_YELLOW "\x1B[38;5;190m"

namespace Tools {

//=== Memory ========================================================================================
	// const char *Memory::HexAscii = "0123456789ABCDEF";
	const char *Memory::mFullAscii =
					// "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
					"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
	const uchar *Memory::EMPTY = (uchar*)("");

	Memory::Memory(const uchar *str, size_t bytes, bool is_binary) {
		mStrCompatible = !is_binary;
		if ( str != nullptr  &&  *str != 0 ) {
			if ( is_binary ) {
				mLength = bytes;

			} else {
				if ( bytes == 0 ) {
					bytes = strlen((const char*)str);
				}
				mLength = bytes;
			}
			mText = new uchar[mLength + 1];
			memcpy(mText, str, mLength);

		} else {
			mLength = 0;
			mText = const_cast<uchar *>(EMPTY);
			mStrCompatible = (str != nullptr);
		}
	}
	Memory::Memory(const Memory& memory): mLength(memory.mLength), mStrCompatible(memory.mStrCompatible) {
		if ( memory.mText != nullptr  &&  memory.mText != EMPTY  && *memory.mText != 0 ) {
			mText = new uchar[mLength + 1];
			memcpy(mText, memory.mText, mLength);

		} else {
			mText = const_cast<uchar *>(EMPTY);
		}
	}
	Memory::~Memory(void) {
		if ( mText != nullptr  &&  mText != EMPTY ) {
			delete [] mText;
		}
		mText = const_cast<uchar*>(EMPTY);
	}
	Memory& Memory::operator=(const char *str) {
		if ( str == nullptr ) {
			clear();

		} else {
			copy((uchar*)str, strlen(str), true);
			mStrCompatible = true;
		}
		return *this;
	}
	Memory& Memory::operator=(const Memory& memory) {
		copy(memory.mText, memory.mLength, true);
		mStrCompatible = memory.mStrCompatible;
		return *this;
	}
	Memory& Memory::operator=(const String& string) {
		copy(string.mText, string.mLength, true);
		mStrCompatible = string.isStrCompatible();
		return *this;
	}
	bool Memory::operator==(const char *str) {
		if ( str == nullptr ) {
			return (mLength == 0);
		}
		return (strcmp((char*)mText, str) == 0);
	}
	bool Memory::operator==(const Memory& memory) {
		return (strcmp((char*)mText, (char*)memory.mText) == 0);
	}

	uchar Memory::operator[](uint index) const {
		if ( index < mLength ) {
			return mText[index];

		} else {
			return 0xFFu;
		}
	}
	void Memory::clear(void) {
		if ( mText != nullptr  &&  mText != EMPTY ) {
			delete [] mText;
			mText = const_cast<uchar*>(EMPTY);
			mLength = 0;
			mStrCompatible = false;
		}
	}
	//                 1               2               3               4               5
	//                 v               v               v               v               v
	// 0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0
	// xxxxx:  00 01 02 03  04 05 06 07 | 08 09 0A 0B  0C 0D 0E 0F   0123456789ABCDEF
	String Memory::hexDump(void) const {
		String result;
		const uint BYTES_ADDRESS = 5 + 1; // +1 for the ':' character
		const uint SPACING_BYTES = 8;
		const uint BYTES_PER_LINE = 16;
		const uint TEXT_SECTION_INDEX = 0x3D;
		const uint LINE_LEN = 0x50;//BYTES_WIDE * 3 + BYTES_WIDE + BYTES_ADDRESS + SPACING_BYTES;
		// char tmps[LINE_LEN + 1];
		char *tmps = new char[LINE_LEN + 1];

		memset(tmps, ' ', LINE_LEN);
		tmps[LINE_LEN] = 0;
		uint index = 0;
		bool dirty = false;
		for ( uint i = 0; i < mLength; i++ ) {

		//--- if this is the start of a new line, print the offset
			if ( i % BYTES_PER_LINE == 0 ) {
				tmps[index++] = mFullAscii[((i >> 16) & 0x0F)];
				tmps[index++] = mFullAscii[((i >> 12) & 0x0F)];
				tmps[index++] = mFullAscii[((i >>  8) & 0x0F)];
				tmps[index++] = mFullAscii[((i >>  4) & 0x0F)];
				tmps[index++] = mFullAscii[((i >>  0) & 0x0F)];
				tmps[index++] = ':';
				tmps[index++] = ' ';
				tmps[LINE_LEN - 1] = '\n';
				dirty = true;
			}

		//--- print the ASCII character (or a '.' if not printable)
			tmps[TEXT_SECTION_INDEX + i % BYTES_PER_LINE] = (isprint(mText[i])? mText[i]: '.');

		//--- print the hex value
			tmps[index++] = mFullAscii[((mText[i] >> 4) & 0x0F)];
			tmps[index++] = mFullAscii[((mText[i] >> 0) & 0x0F)];
			tmps[index++] = ' ';

		//--- add extra spacing for readability
			if ( (i % BYTES_PER_LINE) == 3  ||  (i % BYTES_PER_LINE) == 11 ) {
				tmps[index++] = ' ';

			} else if ( (i % BYTES_PER_LINE) == 7 ) {
				tmps[index++] = '|';
				tmps[index++] = ' ';
			}

			if ( i % BYTES_PER_LINE == BYTES_PER_LINE - 1 ) {
				result += tmps;
				memset(tmps, ' ', LINE_LEN);
				tmps[LINE_LEN] = 0;
				index = 0;
				dirty = false;
			}
		}
		if ( dirty ) {
			result += tmps;
		}
		delete [] tmps;
		return result;
	}

	String Memory::toString(void) const {
		char tmps[mLength * 4], *s = tmps;
		memset(tmps, 0, sizeof(tmps));
		for ( uint i = 0; i < mLength; i++ ) {
			if ( mText[i] < ' '  &&  !(mText[i] == '\n'  ||  mText[i] == '\t'  ||  mText[i] == '\r') ) {
				*s++ = '\\';
				*s++ = 'x';
				*s++ = mFullAscii[(mText[i] >> 4) & 0xF];
				*s++ = mFullAscii[mText[i] & 0xF];
			} else {
				*s++ = mText[i];
			}
		}
		*s = 0;
		return tmps;
	}

	void Memory::copy(const uchar *str, size_t len, bool str_compat) {
		if ( mText != EMPTY  &&  *mText != 0 ) {
			delete [] mText;
		}

		if ( str != nullptr  &&  len != 0 ) {
			mStrCompatible = str_compat;
			mLength = len;
			mText = new uchar[mLength + 1];
			memcpy(mText, str, mLength);
			mText[mLength] = 0;

		} else {
			mLength = 0;
			mText = (uchar*)EMPTY;
		}
	}

//=== String ======================================================================================================================
/** String::String(const char *str, uint start, uint bytes)
 *
 * 	Purpose: create a String from 'str' starting at 'start' and filling 'bytes' count
 *
 * 	Notes: Yes, this is inefficient. Even the fact that C++ will convert types is a
 * 		problem, but this is "throwaway" code.
 */
	String::String(const char *str, uint offset, int bytes): mBufferSize(BUFFER_SIZE) {
		mStrCompatible = true;
		mLength = (str != nullptr? strlen(str): 0);
		if ( str != nullptr  &&  *str != 0  &&  bytes != 0  &&  offset < mLength ) {
			if ( bytes < 0  ||  bytes > (int)mLength ) {
				bytes = mLength;
			}

			mLength = bytes;

		//--- if the offset is 0, we can just copy the string
			if ( offset == 0 ) {
				// NO-OP

		//--- if the offset + bytes is less than the string length, we can copy 'bytes' count
			} else if ( offset + bytes < strlen(str) ) {
				// NO-OP

		//--- if the offset + bytes is greater than the string length, we can only copy to the end of the string
			} else if ( offset + bytes >= strlen(str) ) {
				mLength = strlen(str) - offset;

			} else {
				ERROR("UNEXPECTED!!!%s", "");
			}

// ALERT("max_size=%d offset=%d strlen(str+offset)=%lu length=%lu text=\"%s\" text[0]=%d text[1]=%d", mBufferSize, offset, strlen(str+offset), mLength, mText, mText[0], mText[1]);
			mBufferSize = mLength;
			mText = new uchar[mBufferSize + 1];
			memset(mText, 0, mLength + 1);
			memcpy(mText, str + offset, mLength);
			mText[mLength] = 0;

		} else {
			mLength = 0;
			mText = new uchar[mBufferSize + 1];
			memset(mText, 0, mBufferSize + 1);
		}
	}

	String::String(const String& string): mBufferSize(string.mBufferSize) {
		mStrCompatible = true;
		if ( !string.isEmpty() ) {
			mBufferSize = mLength = string.mLength;
			mText = (uchar*)strdup((char*)string.mText);

		} else {
			mText = new uchar[mBufferSize + 1];
			memset(mText, 0, mBufferSize + 1);
			mLength = 0;
		}
	}

	bool String::operator==(const char *str) const {
		// return ( ((str == nullptr  ||  *str == 0)  &&  isEmpty())  ||  (compare_fn(mText, (const uchar*)str) == 0) );
		return (compare_fn(mText, (const uchar*)str) == 0);
	}

	bool String::operator==(const String& string) const {
		// return ( (string.isEmpty()  &&  isEmpty())  ||  (compare_fn(mText, string.mText) == 0) );
		return (compare_fn(mText, string.mText) == 0);
	}

	bool String::operator!=(const char *str) const {
		// return ( !((str == nullptr  ||  *str == 0)  &&  isEmpty())  ||  (compare_fn(mText, (const uchar*)str) != 0) );
		return (compare_fn(mText, (const uchar*)str) != 0);
	}

	bool String::operator!=(const String& string) const {
		// return ( !(string.isEmpty()  &&  isEmpty())  ||  (compare_fn(mText, string.mText) != 0) );
		return (compare_fn(mText, string.mText) != 0);
	}

	bool String::operator>=(const char *str) const {
		// return ( ((str == nullptr  ||  *str == 0)  &&  isEmpty() ) );// ||  (compare_fn(mText, (const uchar*)str) >= 0) );
		return (compare_fn(mText, (const uchar*)str) >= 0);
	}

	bool String::operator>=(const String& string) const {
		// return ( (string.isEmpty()  &&  isEmpty())  ||  (compare_fn(mText, string.mText) >= 0) );
		return (compare_fn(mText, string.mText) >= 0);
	}

	bool String::operator<=(const char *str) const {
		// return ( (( str == nullptr  ||  *str == 0)  &&  isEmpty() )  ||  (compare_fn(mText, (const uchar*)str) <= 0) );
		return (compare_fn(mText, (const uchar*)str) <= 0);
	}

	bool String::operator<=(const String& string) const {
		// return ( (string.isEmpty()  &&  isEmpty())  || (compare_fn(mText, string.mText) <= 0) );
		return (compare_fn(mText, string.mText) <= 0);
	}

	bool String::operator>(const char *str)  const {
		// return ( ((str == nullptr  ||  *str == 0)  &&  !isEmpty())  ||  (compare_fn(mText, (const uchar*)str) > 0) );
		return (compare_fn(mText, (const uchar*)str) > 0);
	}

	bool String::operator>(const String& string)  const {
		// return (string.isEmpty()  &&  !isEmpty())  ||  (compare_fn(mText, string.mText) > 0);
		return (compare_fn(mText, string.mText) > 0);
	}

	bool String::operator<(const char *str)  const {
		// return (isEmpty()  &&  (str != nullptr  &&  *str != 0))  ||  (compare_fn(mText, (const uchar*)str) < 0);
		return (compare_fn(mText, (const uchar*)str) < 0);
	}

	bool String::operator<(const String& string)  const {
		// return string.isEmpty()  ||  (compare_fn(mText, string.mText) < 0);
		return (compare_fn(mText, string.mText) < 0);
	}

	String& String::operator=(const char *str) {
		if ( str != nullptr  &&  *str != 0 ) {
			resize(strlen(str));
			memcpy(mText, str, strlen(str));
			mLength = strlen(str);
			mText[mLength] = 0;

	//--- This is a special case. Since we are assigning an empty string, we need to assume that the programmer wants to add more text later
		} else {
			clear();
		}

		mStrCompatible = true;
		return *this;
	}

	String& String::operator=(const String& string) {
		if ( !string.isEmpty() ) {
			resize(string.mLength);
			memcpy(mText, string.mText, string.mLength);
			mLength = string.mLength;
			mText[mLength] = 0;
			mStrCompatible = string.mStrCompatible;

		} else {
			clear();
		}
		return *this;
	}

	String& String::operator+=(const char *str) {
		if ( str != nullptr  &&  *str != 0 ) {
			int len = strlen(str);
			resize(mLength + len);
			memcpy(mText + mLength, str, len);
			mLength += len;
			mText[mLength] = 0;
		}
		return *this;
	}

	String& String::operator+=(const String& string) {
		if ( !string.isEmpty() ) {
			resize(mLength + string.mLength);
			memcpy(mText + mLength, string.mText, string.mLength);
			mLength += string.mLength;
			mText[mLength] = 0;
		}
		return *this;
	}

	String String::operator+(const char *str) const {
		if ( str != nullptr  &&  *str != 0 ) {
			char tmps[mLength + strlen(str) + 1];
			snprintf(tmps, sizeof(tmps), "%s%s", mText, str);
			return tmps;

		} else {
			return *this;
		}
	}

	String String::operator+(const String& string) const {
		if ( !string.isEmpty() ) {
			char tmps[mLength + string.mLength + 1];
			snprintf(tmps, sizeof(tmps), "%s%s", mText, string.mText);
			return tmps;

		} else {
			return *this;
		}
	}
	bool operator==(const char* str, const String& string) {
		if ( (str == nullptr  ||  *str == 0)  ||  string.isEmpty() ) {
			return false;
		}
		return (string.compare_fn((const unsigned char*)str, string.getText()) == 0);
	}
	bool operator!=(const char* str, const String& string) {
		if ( (str == nullptr  ||  *str == 0)  ||  string.isEmpty() ) {
			return false;
		}
		return (string.compare_fn((const unsigned char*)str, string.getText()) != 0);
	}
	bool operator>=(const char* str, const String& string) {
		if ( (str == nullptr  ||  *str == 0)  ||  string.isEmpty() ) {
			return false;
		}
		return (string.compare_fn((const unsigned char*)str, string.getText()) >= 0);
	}
	bool operator<=(const char* str, const String& string) {
		if ( (str == nullptr  ||  *str == 0)  ||  string.isEmpty() ) {
			return false;
		}
		return (string.compare_fn((const unsigned char*)str, string.getText()) <= 0);
	}
	bool operator>(const char* str, const String& string) {
		if ( (str == nullptr  ||  *str == 0)  ||  string.isEmpty() ) {
			return false;
		}
		return (string.compare_fn((const unsigned char*)str, string.getText()) > 0);
	}
	bool operator<(const char* str, const String& string) {
		if ( (str == nullptr  ||  *str == 0)  ||  string.isEmpty() ) {
			return false;
		}
		return (string.compare_fn((const unsigned char*)str, string.getText()) < 0);
	}
	String operator+(const char *str, const String& string) {
		char tmps[strlen(str) + string.mLength + 1];
		snprintf(tmps, sizeof(tmps), "%s%s", str, string.mText);
		return tmps;
	}


//---------------------------------------------------------------------------------------------------------------------------------------------------
	void String::setCaseCompare(bool ignore) {
		compare_fn = (cmp_fn*)(ignore? my_strcasecmp: my_strcmp);
		strsub_fn = (sub_fn*)(ignore? strcasesub: strsub);

		if ( ignore ) {
			strstr_fn = my_strcasestr;

		} else {
			strstr_fn = my_strstr;
		}
	}

	bool String::startsWith(const String& string, uint starting_at) const {
		return strsub_fn(mText + starting_at, string.mText);
	}

	bool String::contains(const String& sub) const {
		return ( strstr_fn(mText, sub.mText) != nullptr );
	}

	void String::clear(void) {
		if ( mText != nullptr  &&  mText != EMPTY ) {
			delete [] mText;
			mText = const_cast<uchar*>(EMPTY);
			mLength = 0;
		}
		mBufferSize = BUFFER_SIZE;
		mText = new uchar[mBufferSize + 1];			// <-- create a new buffer & initialize it
		memset(mText, 0, mBufferSize + 1);
	}

	std::vector<String> String::split(char key) const {
		std::vector<String> strings;
		uchar *head = mText;
		uchar *tail = mText;

		while ( *head != 0 ) {
			if ( *head != key ) {
				head++;
			} else {
				// strings.push_back(String((char*)tail, 0, head - tail + 1));
				strings.push_back(String((char*)tail, 0, head - tail));
				tail = ++head; // <-- skip past "key"
			}
		}

		if ( tail <= head ) {
			strings.push_back(String((char*)tail));
		}

		return strings;
	}

	String String::trim(void) const {

	//--- Trim right
		uchar tmps[mLength + 1], *s = tmps + mLength - 1;
		memcpy(tmps, mText, mLength + 1);
		while ( s != tmps  &&  isspace(*s) ) {
			*s-- = 0;
		}

	//--- Trim left
		s = tmps;
		while ( *s != 0 ) {
			if ( !isspace(*s) ) {
				break;
			}
			s++;
		}

		return (char*)s;
	}

	String String::trimRight(void) const {
		uchar tmps[mLength + 1], *s = tmps + mLength - 1;
		memcpy(tmps, mText, mLength + 1);
		while ( s >= tmps  &&  isspace(*s) ) {
			*s-- = 0;
		}

		return (char*)tmps;
	}
	String String::trimLeft(void) const {
		uchar *s = mText;
		while ( *s != 0  ) {
			if ( !isspace(*s) ) {
				break;
			}
			s++;
		}
		return (char*)s;
	}

	String String::toString(long long value, uint radix) {
		char tmps[200], *s = tmps + sizeof(tmps) - 2;
		memset(tmps, 0, sizeof(tmps));

		bool negative = ( value < 0  &&  radix == 10 );
		if ( negative ) {
			value = -value;
		}

		if ( value == 0 ) {
			return String("0");
		}

		if ( 2 < radix  &&  radix <= strlen(mFullAscii) ) {
			while ( value > 0 ) {
				*--s = mFullAscii[value % radix];
				value /= radix;
			}

		} else if ( radix == 2 ) {
			while ( value > 0 ) {
				*--s = ((value & 1)? '1': '0');
				value >>= 1;
			}

		} else {
			THROW_ERROR("Cannot work with radix=%d!", radix);
		}

		if ( negative ) {
			*--s = '-';
		}
		return String(s);
	}

	String String::encode(void) const {
		char *tmps = new char[mLength * 4 + 1], *s = tmps;
		for ( size_t i = 0; i < mLength; i++ ) {
			switch ( mText[i] ) {
				case '\r': *s++ = '\\'; *s++ = 'r'; break;
				case '\n': *s++ = '\\'; *s++ = 'n'; break;
				case '\f': *s++ = '\\'; *s++ = 'f'; break;
				case '\b': *s++ = '\\'; *s++ = 'b'; break;
				case '\t': *s++ = '\\'; *s++ = 't'; break;
				case '\v': *s++ = '\\'; *s++ = 'v'; break;
				case '\a': *s++ = '\\'; *s++ = 'a'; break;
				// case '\e': *s++ = '\\'; *s++ = 'e'; break;
				// case  '"': *s++ = '\\'; *s++ = '"'; break;
				default:
					if ( ' ' <= mText[i]  &&  mText[i] <= '~' ) {
						*s++ = mText[i];

					} else {
						static const char *hex_alpha = "0123456789ABCDEF";
						*s++ = '\\';
						*s++ = 'x';
						*s++ = hex_alpha[(mText[i] >> 4) & 0xF];
						*s++ = hex_alpha[mText[i] & 0xF];
					}
					break;
			}
		}
		*s = 0;
		String string(tmps);
		delete [] tmps;
		return string;
	}

	static int testNull(const uchar *str, const uchar *sub) {
		if ( str != nullptr  &&  (sub == nullptr  ||  *sub == 0) ) {
			return 1;

		} else if ( str != nullptr  &&  sub != nullptr ) {
			return -1;

		} else {
			return 0;
		}
	}

	void String::resize(uint new_length) {

	//--- If new_length is zero, clear the string
		if ( mText == nullptr  ||  mText == EMPTY ) {
			mText = new uchar[(new_length < mBufferSize? mBufferSize : new_length) + 1];
			memset(mText, 0, mBufferSize);

	//--- If new_length is greater than current length, replace the buffer and copy the current buffer
		} else if ( new_length > mBufferSize ) {
			mBufferSize = new_length + BUFFER_SIZE;		// <-- Add some extra space to avoid too many resizes
			uchar *tmps = new uchar[mBufferSize + 1];		// <-- +1 for null terminator
			memset(tmps, 0, mBufferSize + 1);				// <-- Clear the new buffer
			memcpy(tmps, mText, mLength);					// <-- Copy the current buffer
			tmps[mLength] = 0;							// <-- Null terminate the new buffer
			delete [] mText;								// <-- Because the test for a nullptr, we can delete the old buffer
			mText = tmps;								// <-- Point to the new buffer

	//--- Else, there's enough space in the current buffer, so do nothing
		} else {
			// No-op
		}
	}
	Tools::String String::wideCharToString(wchar_t wchar) {
		char tmps[sizeof(wchar_t) + 1] = {' ', ' ', ' ', ' ', 0}, *s = tmps;
		for ( int i = 3; i >= 0; i-- ) {
			char c = (char)((wchar >> (i << 3)) & 0xFF);
			if ( c != 0 ) {
				*s++ = c;
			}
		}
		return String(tmps);
	}

	const uchar *String::my_strstr(const uchar *str, const uchar *sub) {
		const char *result = strstr((const char*)str, (const char*)sub);
		return (const uchar*)result;
	}
	const uchar *String::my_strcasestr(const uchar *str, const uchar *sub) {
		const char *result = strcasestr((const char*)str, (const char*)sub);
		return (const uchar*)result;
	}
	int String::my_strcmp(const uchar *str1, const uchar *str2) {
		if ( str1 == nullptr ) {
			return ( (str2 == nullptr  ||  *str2 == 0)? 0: -1 );

		} else if ( str2 == nullptr ) {
			return ( str1 != nullptr );

		} else if ( *str1 == 0  &&  *str2 == 0 ) {
			return 0;
		}
		return strcmp(reinterpret_cast<const char*>(str1), reinterpret_cast<const char*>(str2));
	}
	int String::my_strcasecmp(const uchar *str1, const uchar *str2) {
		if ( (str1 == nullptr  ||  *str1 == 0)  &&  (str2 == nullptr  ||  *str2 == 0) ) {
			return 0;
		}
		return strcasecmp(reinterpret_cast<const char*>(str1), reinterpret_cast<const char*>(str2));
	}
	bool String::strsub(const char *str, const char *sub) {
		int test = testNull((const uchar*)str, (const uchar*)sub);
		if ( test == -1 ) {
			while ( *sub != 0  &&  *str == *sub ) {
				str++, sub++;
			}
			return (*sub == 0);

		} else {
			return test;
		}
	}

	bool String::strcasesub(const char *str, const char *sub) {
		int test = testNull((const uchar*)str, (const uchar*)sub);
		if ( test == -1 ) {
			while ( *sub != 0  &&  toupper(*str) == toupper(*sub) ) {
				str++, sub++;
			}
			return (*sub == 0);

		} else {
			return test;
		}
	}

	String String::formatString(const String& fmt, ...) {
		va_list ap;

	//--- Calculate number of bytes
		va_start(ap, fmt);
		uint len = vsnprintf(nullptr, 0, (char*)fmt.getText(), ap);
		va_end(ap);

	//--- Create buffer
		char buffer[len * 2 + 1];

	//--- Fill
		va_start(ap, fmt);
		vsnprintf(buffer, sizeof(buffer), (char*)fmt.getText(), ap);
		va_end(ap);

		return buffer;
	}

//---------------------------------------------------------------------------------------------------------------------------------------------------
	FILE *fopen(const String& filename, const String& permissions) {
		return ::fopen((char*)filename.getText(), (char*)permissions.getText());
	}

	bool fgets(String& buffer, FILE *fp) {
		char line[1024], *result;
		do {
			if ( (result = fgets(line, sizeof(line), fp)) != nullptr) {
				buffer += line;
			}
		} while ( result != nullptr  &&  !strchr(line, '\n') );
		return (buffer.isEmpty());
	}
}