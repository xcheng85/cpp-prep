// How unicode works ? 

// Unicode, the Universal Character Set (UCS), and various character encoding formats
// UTF Encoding Formats: map Unicode code points to sequences of bytes
// UTF-8 UTF-16 utf-32

// wchar_t , is used to represent wide characters
// wchar_t is 16 bits on Windows and 32 bits on Unix-like systems.

// developers are encouraged to use external libraries, such as ICU or Boost.Locale, 
// for character encoding conversions.

//Prefer UTF-8 for Storage and Transmission text-processing scenarios.

// When manipulating Unicode text, use Unicode-aware functions and libraries instead of relying on legacy C++ functions

class Solution {
public:
    bool isAnagram(string s, string t) {
       //s and t consist of lowercase English letters.
       vector<int> bucket(26, 0);
       for(const auto& c : s) {
        ++bucket[c-'a'];
       }
        for(const auto& c : t) {
        --bucket[c-'a'];
       }

       for(const auto& b:bucket) {
            if(b != 0) {
                return false;
            }
       }
       return true;
    }
};