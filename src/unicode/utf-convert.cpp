#include <fstream>
#include <vector>
#include <string>
#include <codecvt>
#include <locale>
#include <iostream>

// Read the content of a UTF-8 encoded file
std::string read_utf8_file(const std::string &filename)
{
    std::ifstream input_file(filename, std::ios::binary);
    std::vector<char> bytes(
        (std::istreambuf_iterator<char>(input_file)),
        std::istreambuf_iterator<char>());
    return std::string(bytes.begin(), bytes.end());
}

// Process Unicode text (e.g., convert to uppercase)
std::u32string process_unicode_text(const std::u32string &input)
{
    std::u32string result;
    for (char32_t ch : input)
    {
        char32_t upper_case_ch = std::towupper(ch);
        result.push_back(upper_case_ch);
    }
    return result;
}

int main()
{
    // Read a UTF-8 encoded file
    std::string utf8_content = read_utf8_file("example.txt");

    // Convert UTF-8 content to UTF-32
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    std::u32string utf32_content = converter.from_bytes(utf8_content);

    // Process Unicode text
    std::u32string processed_content = process_unicode_text(utf32_content);

    // Convert the result back to UTF-8
    std::string output_utf8_content = converter.to_bytes(processed_content);

    // Write the output to stdout
    std::cout << output_utf8_content << std::endl;

    return 0;
}