#include <string>
#include "Blob.hpp"

namespace Tools {

//=== Blob ========================================================================================
	const char *Blob::HexAscii = "0123456789ABCDEF";
	const char *Blob::FullAscii =
					"!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
	const uchar *Blob::EMPTY = (uchar*)("");

	Blob::Blob(const char *str, size_t bytes, bool is_binary) {
		str_compatible = !is_binary;
		if ( str != nullptr  &&  *str != 0 ) {
			if ( is_binary ) {
				length = bytes;

			} else {
				if ( bytes == 0 ) {
					bytes = strlen(str);
				}
				length = bytes;
			}
			text = new uchar[bytes + 1];
			memcpy(text, str, bytes);

		} else {
			length = 0;
			text = const_cast<uchar *>(EMPTY);
		}
	}
	Blob::Blob(const Blob& blob): length(blob.length), str_compatible(blob.str_compatible) {
		if ( blob.text != nullptr  &&  blob.text != EMPTY  && *blob.text != 0 ) {
			text = new uchar[length + 1];
			memcpy(text, blob.text, length);

		} else {
			text = const_cast<uchar *>(EMPTY);
		}
	}
	Blob::~Blob(void) {
		if ( text != nullptr  &&  text != EMPTY ) {
			delete [] text;
			text = const_cast<uchar*>(EMPTY);
		}
	}
	Blob& Blob::operator=(const char *str) {
		copy((uchar*)str, strlen(str), true);
		return *this;
	}
	Blob& Blob::operator=(const Blob& blob) {
		copy(blob.text, blob.length, true);
		return *this;
	}
	Blob& Blob::operator=(const String& string) {
		copy(string.text, string.length, true);
		return *this;
	}
	bool Blob::operator==(const char *str) {
		return (strcmp((char*)text, str) == 0);
	}
	bool Blob::operator==(const Blob& blob) {
		return (strcmp((char*)text, (char*)blob.text) == 0);
	}

	uchar Blob::operator[](uint index) const {
		if ( index < length ) {
			return text[index];

		} else {
			return 0xFFu;
		}
	}
	void Blob::Clear(void) {
		if ( text != nullptr  &&  text != EMPTY ) {
			delete [] text;
			text = const_cast<uchar*>(EMPTY);
			length = 0;
		}
	}
	//                 1               2               3               4               5
	//                 v               v               v               v               v
	// 0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0
	// xxxxx:  00 01 02 03  04 05 06 07 | 08 09 0A 0B  0C 0D 0E 0F   0123456789ABCDEF
	String Blob::HexDump(void) const {
		const uint BYTES_WIDE = 16;
		const uint TEXT_INDEX = 0x3C;
		const uint LINE_LEN = 0x4B;
		String result;
		char tmps[LINE_LEN + 1];

		memset(tmps, ' ', sizeof(tmps));
		tmps[sizeof(tmps) - 1] = 0;
		uint index = 0;
		for ( uint i = 0; i < length; i++ ) {
			if ( i % BYTES_WIDE == 0 ) {
				tmps[index++] = ((i >> 12) & 0x0F) + '0';
				tmps[index++] = ((i >>  8) & 0x0F) + '0';
				tmps[index++] = ((i >>  4) & 0x0F) + '0';
				tmps[index++] = (i & 0x0F) + '0';
				tmps[index++] = ':';
				tmps[index++] = ' ';
			}

			tmps[TEXT_INDEX + i] = (text[i] < 0x80? text[i]: '.');

			tmps[index++] = ((text[i] >> 4) & 0x0F) + '0';
			tmps[index++] = (text[i] & 0x0F) + '0';
			tmps[index++] = ' ';
			if ( (i % BYTES_WIDE) == 3 ) {
				tmps[index++] = ' ';

			} else if ( (i % BYTES_WIDE) == 11 ) {
				tmps[index++] = ' ';
				result += tmps;
				memset(tmps, ' ', sizeof(tmps));
				tmps[sizeof(tmps) - 1] = 0;
				index = 0;

			} else if ( (i % BYTES_WIDE) == 7 ) {
				tmps[index++] = '|';
				tmps[index++] = ' ';
			}
		}
		return result;
	}

	String Blob::ToString(void) const {
		char tmps[length * 4], *s = tmps;
		memset(tmps, 0, sizeof(tmps));
		for ( uint i = 0; i < length; i++ ) {
			if ( text[i] < ' '  &&  !(text[i] == '\n'  ||  text[i] == '\t'  ||  text[i] == '\r') ) {
				*s++ = '\\';
				*s++ = 'x';
				*s++ = HexAscii[(text[i] >> 4) & 0xF];
				*s++ = HexAscii[text[i] & 0xF];
			} else {
				*s++ = text[i];
			}
		}
		*s = 0;
		return tmps;
	}

	void Blob::copy(const uchar *str, size_t len, bool str_compat) {
		if ( text != EMPTY  &&  *text != 0 ) {
			delete [] text;
		}
		str_compatible = str_compat;
		length = len;
		text = new uchar[length + 1];
		memcpy(text, str, length);
		text[length] = 0;
	}

//=== String ======================================================================================
/** String::String(const char *str, uint start, uint bytes)
 *
 * 	Purpose: create a String from 'str' starting at 'start' and filling 'bytes' count
 *
 * 	Notes: Yes, this is inefficient. Even the fact that C++ will convert types is a
 * 		problem, but this is "throwaway" code.
 */
	String::String(const char *str, uint offset, int bytes): size(0) {
		str_compatible = true;
		if ( str != nullptr  &&  *str != 0  &&  bytes != 0  &&  offset < strlen(str) ) {
			if ( bytes < 0  ||  bytes > (int)strlen(str) ) {
				bytes = strlen(str);
			}

			length = bytes;
			if ( offset == 0 ) {
				// length = bytes;
				text = new uchar[length + 1];
				memset(text, 0, length + 1);
				memcpy(text, str + offset, length);
// ALERT("offset=%d strlen(str+length)=%lu length=%lu", offset, strlen(str), length);

			} else if ( offset + bytes < strlen(str) ) {
				// length = bytes;
				text = new uchar[length + 1];
				memset(text, 0, length + 1);
				memcpy(text, str + offset, bytes);
// ALERT("offset=%d strlen(str+offset)=%lu length=%lu text=\"%s\" text[0]=%d text[1]=%d", offset, strlen(str+offset), length, text, text[0], text[1]);

			} else if ( offset + bytes >= strlen(str) ) {
				length = strlen(str) - offset;
				text = new uchar[length + 1];
				memset(text, 0, length + 1);
				memcpy(text, str + offset, length);
				text[length] = 0;
// ALERT("offset=%d strlen(str+offset)=%lu length=%lu text=\"%s\" text[0]=%d text[1]=%d", offset, strlen(str+offset), length, text, text[0], text[1]);

			} else {
				ERROR("UNEXPECTED!!!%s", "");
			}

		} else {
			length = 0;
			size = 0;
			text = const_cast<uchar*>(EMPTY);
		}
	}

	String::String(const String& string): size(string.size) {
		if ( !string.IsEmpty() ) {
			str_compatible = true;
			size = length = string.length;
			text = (uchar*)strdup((char*)string.text);
		} else {
			text = const_cast<uchar*>(EMPTY);
			length = 0;
		}
	}

	String::String(int128_t value, uint radix) {
		str_compatible = true;
		if ( 1 < radix  &&  radix <= strlen(FullAscii) ) {
			char tmps[200], *s = tmps + sizeof(tmps) - 2;
			memset(tmps, 0, sizeof(tmps));
			if ( radix < strlen(HexAscii) ) {
				while ( value > 0 ) {
					*--s = HexAscii[value % radix];
					value /= radix;
				}

			} else {
				while ( value > 0 ) {
					*--s = FullAscii[value % radix];
					value /= radix;
				}
			}
			length = strlen(s);
			text = new uchar[length + 1];
			memcpy(text, s, length);

		} else {
			THROW_ERROR("Cannot work with radix=%d!", radix);
		}
	}

	bool String::operator==(const char *str) const {
		if ( str == nullptr  ||  *str == 0 ) {
			if ( IsEmpty() ) {
				return true;
			}
			return false;
		}
		return (compare_fn(text, (const uchar*)str) == 0);
	}

	bool String::operator==(const String& string) const {
		return (compare_fn(text, string.text) == 0);
	}

	bool String::operator!=(const char *str) const {
		if ( str == nullptr  ||  *str == 0) {
			if ( IsEmpty() ) {
				return false;
			}
			return false;
		}
		return (compare_fn(text, (const uchar*)str) != 0);
	}

	bool String::operator!=(const String& string) const {
		return (compare_fn(text, string.text) != 0);
	}

	bool String::operator>=(const char *str) const {
		if ( str == nullptr  ||  *str == 0 ) {
			return true;
		}
		return (compare_fn(text, (const uchar*)str) >= 0);
	}

	bool String::operator>=(const String& string) const {
		return (compare_fn(text, string.text) >= 0);
	}

	bool String::operator<=(const char *str) const {
		if ( IsEmpty() ) {
			return true;
		}
		return (compare_fn(text, (const uchar*)str) <= 0);
	}

	bool String::operator<=(const String& string) const {
		return (compare_fn(text, string.text) <= 0);
	}

	bool String::operator>(const char *str)  const {
		if ( !IsEmpty()  &&  (str == nullptr  ||  *str == 0) ) {
			return true;
		}
		return (compare_fn(text, (const uchar*)str) > 0);
	}

	bool String::operator>(const String& string)  const {
		return (compare_fn(text, string.text) > 0);
	}

	bool String::operator<(const char *str)  const {
		if ( IsEmpty()  &&  (str != nullptr  &&  *str != 0) ) {
			return true;
		}
		return (compare_fn(text, (const uchar*)str) < 0);
	}

	bool String::operator<(const String& string)  const {
		return (compare_fn(text, string.text) < 0);
	}

	String& String::operator=(const char *str) {
		if ( str != nullptr  &&  *str != 0 ) {
			length = strlen(str);
			size = length;
			text = new uchar[size + 1];
			memcpy(text, str, length);
			text[length] = 0;
//FIXME: unit tests need to test for this!
			str_compatible = true;

		} else {
			Clear();
		}
		return *this;
	}

	String& String::operator=(const String& string) {
		if ( !string.IsEmpty() ) {
			if ( text != nullptr  &&  text != EMPTY ) {
				delete [] text;
			}
			length = string.length;
			text = new uchar[length + 1];
			memcpy(text, string.text, length);
			text[length] = 0;
//FIXME: unit tests need to test for this!
			str_compatible = string.str_compatible;

		} else {
			Clear();
		}
		return *this;
	}

	String& String::operator+=(const char *str) {
		if ( str != nullptr  &&  *str != 0 ) {
			int len = strlen(str);
			if ( length + len >= size ) {
				size = length + len + BUFFER_SIZE;
				if ( text != nullptr  &&  text != EMPTY ) {
					delete [] text;
				}
				text = new uchar[size + 1];
				strncpy((char*)text, str, size);
				text[size] = 0;
			}
			length += len;
			strncat((char*)text, str, len);
			text[length] = 0;
		}
		return *this;
	}

	String& String::operator+=(const String& string) {
		if ( !string.IsEmpty() ) {
			// int len = strlen(str);
			if ( length + string.length >= size ) {
				uint new_size = length + string.length + BUFFER_SIZE;
				uchar *tmps = new uchar [new_size];
				memset(tmps, 0, new_size);
				memcpy(tmps, text, length);
				if ( text != nullptr  &&  text != EMPTY ) {
					delete [] text;
				}
				text = tmps;
				size = new_size;
			}
			memcpy(text + length, string.text, string.length);
			length += string.length;
			text[length] = 0;
		}
		return *this;
	}

	// String& String::operator+=(const String& string) {
	// 	if ( string.length > 0 ) {
	// 		if ( length + string.length >= size ) {
	// 			size = length + string.length + BUFFER_SIZE;
	// 			if ( text != nullptr  &&  text != EMPTY ) {
	// 				delete [] text;
	// 			}
	// 			text = new uchar[size + 1];
	// 			text[size] = 0;
	// 		}
	// 		length += string.length;
	// 		strncat((char*)text, (char*)string.text, string.length);
	// 		text[length] = 0;
	// 	}
	// 	return *this;
	// }

	String String::operator+(const char *str) const {
		if ( str != nullptr  &&  *str != 0 ) {
			char tmps[length + strlen(str) + 1];
			snprintf(tmps, sizeof(tmps), "%s%s", text, str);
			return tmps;

		} else {
			return *this;
		}
	}

	String String::operator+(const String& string) const {
		if ( !string.IsEmpty() ) {
			char tmps[length + string.length + 1];
			snprintf(tmps, sizeof(tmps), "%s%s", text, string.text);
			return tmps;

		} else {
			return *this;
		}
	}

//---------------------------------------------------------------------------------------------------------------------------------------------------
	void String::SetCaseCompare(bool ignore) {
		compare_fn = (ignore? my_strcasecmp: my_strcmp);
		strsub_fn = (ignore? strcasesub: strsub);
		if ( ignore ) {
			strstr_fn = my_strcasestr;
		} else {
			strstr_fn = my_strstr;
		}
	}

	bool String::StartsWith(const String& string, uint starting_at) const {
		return strsub_fn(text + starting_at, string.text);
	}

	bool String::Contains(const String& sub) const {
		return ( strstr_fn(text, sub.text) != nullptr );
	}

	std::vector<String> String::Split(char key) const {
		std::vector<String> strings;
		uchar *head = text;
		uchar *tail = text;

		while ( *head != 0 ) {
			if ( *head != key ) {
				head++;
			} else {
				strings.push_back(String((char*)tail, 0, head - tail + 1));
				tail = ++head; // <-- skip past "key"
			}
		}
		if ( tail <= head ) {
			strings.push_back(String((char*)tail));
		}

		return strings;
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
		if ( text == nullptr  ||  text == EMPTY ) {
			text = new uchar[size];
			memset(text, 0, size);

		} else if ( new_length > size ) {
			size = new_length + BUFFER_SIZE;
			uchar *tmps = new uchar[size + 1];
			memset(tmps, 0, size + 1);
			memcpy(tmps, text, length);
			length = new_length;
			delete [] text;
			text = tmps;
		}
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
		return strcmp(reinterpret_cast<const char*>(str1), reinterpret_cast<const char*>(str2));
	}
	int String::my_strcasecmp(const uchar *str1, const uchar *str2) {
		return strcasecmp(reinterpret_cast<const char*>(str1), reinterpret_cast<const char*>(str2));
	}
	bool String::strsub(const uchar *str, const uchar *sub) {
		int test = testNull(str, sub);
		if ( test == -1 ) {
			while ( *sub != 0  &&  *str == *sub ) {
				str++, sub++;
			}
			return (*sub == 0);

		} else {
			return test;
		}
	}

	bool String::strcasesub(const uchar *str, const uchar *sub) {
		int test = testNull(str, sub);
		if ( test == -1 ) {
			while ( *sub != 0  &&  toupper(*str) == toupper(*sub) ) {
				str++, sub++;
			}
			return (*sub == 0);

		} else {
			return test;
		}
	}

	String String::FormatString(const String& fmt, ...) {
		va_list ap;

	//--- Calculate number of bytes
		va_start(ap, fmt);
		uint len = vsnprintf(nullptr, 0, (char*)fmt.GetText(), ap);
		va_end(ap);

	//--- Create buffer
		char buffer[len * 2 + 1];

	//--- Fill
		va_start(ap, fmt);
		vsnprintf(buffer, sizeof(buffer), (char*)fmt.GetText(), ap);
		va_end(ap);

		return buffer;
	}

//---------------------------------------------------------------------------------------------------------------------------------------------------
	FILE *fopen(const String& filename, const String& permissions) {
		return fopen((char*)filename.GetText(), (char*)permissions.GetText());
	}

	bool fgets(String& buffer, FILE *fp) {
		char line[1024], *result;
		do {
			if ( (result = fgets(line, sizeof(line), fp)) != nullptr) {
				buffer += line;
			}
		} while ( result != nullptr  &&  !strchr(line, '\n') );
		return (buffer.IsEmpty());
	}
}