# Cube Encryption Program

This program implements the Cube encryption algorithm to encrypt and decrypt data. The encryption key is stored in a separate `key.txt` file.

## Prerequisites

To run this program, you need the following:

- C++ compiler supporting C++11 or later
- Standard Library (STL)

## Usage

1. Clone the repository or download the source code files.
   - `https://github.com/Kalashyan-1/Cube-Encryption.git`

2. Compile the program using the following command: 
   - `g++ -std=c++11 -o cube_encryption main.cpp  encryption.cpp`


3. Run the program by executing the compiled binary:
   - `./cube_encryption` 


4. The program will prompt you to enter the text you want to encrypt.

5. After entering the text, the program will perform the encryption using the Cube encryption algorithm and store the encryption key in the `key.txt` file.

6. The program will read the encryption key from the `key.txt` file and perform the decryption process.

## File Structure

- `encryption.cpp`: The main C++ source code file containing the implementation of the Cube encryption algorithm and the program logic.
- `key.txt`: The file where the encryption key is stored.

## Algorithm Details

The Cube encryption algorithm used in this program involves rotating the characters of the input text in various ways based on a secret key. The encryption key determines the rotation operations to perform on the text, while the decryption process reverses these operations to retrieve the original text.

## Contributions

Contributions to the program are welcome! If you find any issues or have suggestions for improvements, please submit an issue or pull request.
