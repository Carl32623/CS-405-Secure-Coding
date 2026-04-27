/*
*  Name: Encryption.pp
*
*  Description: This program demonstrates XOR-based encryption and decryption.
*               It reads data from a text file, ecrypts the data using a key, saves
*               the encrypted data to a file, then decrypts the data back and saves
*               the results.
*
*  Author: Carl LaLonde
*
*  Date: 04/05/2026
*/

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <ctime>

using namespace std;

/// <summary>
/// encrypt or decrypt a source string using the provided key
/// </summary>
/// <param name="source">input string to process</param>
/// <param name="key">key to use in encryption / decryption</param>
/// <returns>transformed string</returns>
string encrypt_decrypt(const string& source, const string& key) {
  // get lengths now instead of calling the function every time.
  // this would have most likely been inlined by the compiler, but design for perfomance.
  const auto key_length = key.length();
  const auto source_length = source.length();

  // assert that our input data is good
  assert(key_length > 0);
  assert(source_length > 0);

  string output = source;

  // loop through the source string char by char
  for (size_t i = 0; i < source_length; ++i) { // TODO: student need to change the next line from output[i] = source[i]
    // transform each character based on an xor of the key modded constrained to key length using a mod
      output[i] = source[i] ^ key[i % key_length];
  }

  // our output length must equal our source length
  assert(output.length() == source_length);

  // return the transformed string
  return output;
}

string read_file(const string& filename) {
  //string file_text = "John Q. Smith\nThis is my test string";

  // Open file for read
  ifstream input_file(filename);

  // Creates a buffer to store file data
  stringstream buffer;

  // If the file fails to open.
  if (!input_file) {

      cout << "Error opening file: " << filename << endl;

      return "";
  }
  // Reads the file into the buffer
  buffer << input_file.rdbuf();

  // Converts the buffer data into a string and returns it.
  return buffer.str();
}

string get_student_name(const string& string_data) {
  string student_name;

  // find the first newline
  size_t pos = string_data.find('\n');
  // did we find a newline
  if (pos != string::npos) { // we did, so copy that substring as the student name
    student_name = string_data.substr(0, pos);
  }

  return student_name;
}

void save_data_file(const string& filename, const string& student_name, const string& key, const string& data) {
    // Creates am output file stream using the filename
    ofstream output_file(filename);

    // Check if the file failed to open
    if (!output_file) {

        cout << "Error saving file: " << filename << endl;

        return;
    }
    // Get the current time
    time_t now = time(nullptr);

    // Creates a broken-down time structure to store local time
    tm local_time;

    // Converts current time to local time format
    localtime_s(&local_time, &now);

    // Writes student name, current date, encryption key used, and the actual data.
    output_file << student_name << endl;
    output_file << put_time(&local_time, "%Y-%m-%d") << endl;
    output_file << key << endl;
    output_file << data;
}

int main() {
  cout << "Encyption Decryption Test!" << endl;

  // input file format
  // Line 1: <students name>
  // Line 2: <Lorem Ipsum Generator website used> https://pirateipsum.me/ (could be https://www.lipsum.com/ or one of https://www.shopify.com/partners/blog/79940998-15-funny-lorem-ipsum-generators-to-shake-up-your-design-mockups)
  // Lines 3+: <lorem ipsum generated with 3 paragraphs> 
  //  Fire in the hole bowsprit Jack Tar gally holystone sloop grog heave to grapple Sea Legs. Gally hearties case shot crimp spirits pillage galleon chase guns skysail yo-ho-ho. Jury mast coxswain measured fer yer chains man-of-war Privateer yardarm aft handsomely Jolly Roger mutiny.
  //  Hulk coffer doubloon Shiver me timbers long clothes skysail Nelsons folly reef sails Jack Tar Davy Jones' Locker. Splice the main brace ye fathom me bilge water walk the plank bowsprit gun Blimey wench. Parrel Gold Road clap of thunder Shiver me timbers hempen halter yardarm grapple wench bilged on her anchor American Main.
  //  Brigantine coxswain interloper jolly boat heave down cutlass crow's nest wherry dance the hempen jig spirits. Interloper Sea Legs plunder shrouds knave sloop run a shot across the bow Jack Ketch mutiny barkadeer. Heave to gun matey Arr draft jolly boat marooned Cat o'nine tails topsail Blimey.

  const string file_name = "inputdatafile.txt";
  const string encrypted_file_name = "encrypteddatafile.txt";
  const string decrypted_file_name = "decrytpteddatafile.txt";
  const string source_string = read_file(file_name);
  const string key = "password";

  // get the student name from the data file
  const string student_name = get_student_name(source_string);

  // encrypt sourceString with key
  const string encrypted_string = encrypt_decrypt(source_string, key);

  // save encrypted_string to file
  save_data_file(encrypted_file_name, student_name, key, encrypted_string);

  // decrypt encryptedString with key
  const string decrypted_string = encrypt_decrypt(encrypted_string, key);

  // save decrypted_string to file
  save_data_file(decrypted_file_name, student_name, key, decrypted_string);

  cout << "Read File: " << file_name << " - Encrypted To: " << encrypted_file_name << " - Decrypted To: " << decrypted_file_name << endl;

  // students submit input file, encrypted file, decrypted file, source code file, and key used
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
