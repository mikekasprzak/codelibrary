// - ------------------------------------------------------------------------------------------ - //
// A class that, given a string, breaks it down in to elements //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __WhitespaceTokenizer_H__
#define __WhitespaceTokenizer_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <sstream>

#include "Data/DataBlock.h"
// - ------------------------------------------------------------------------------------------ - //
class cWhitespaceTokenizer {
	std::stringstream Data;
	std::stringstream Line;
	std::string CurrentToken;
		
public:
	cWhitespaceTokenizer( const char* FileName )
	{
		// Load the contents of FileName in to a string //
		DataBlock* Block = new_DataBlock( FileName );
		Data << std::string( (char*)Block->Data, Block->Size );
		delete_DataBlock( Block );
		
		// Process the next (first) line //
		NextLine();
	}

public:
	// Steps the tokenizer to the next line, returns false if no lines left //
	bool NextLine() {
		// Loop until we're sure we find a line with a usable token //
		do {
			// Grab a whole line in to a string //
			std::string TempString;
			getline( Data, TempString );
			Line.clear();
			Line << TempString;
			
			// Read the next token //
			NextToken();
			
			// In case we happen to breach the end of Data, no token found //
			if ( Data.eof() )
				return false;
		} while ( Line.eof() );
		
		// Token found //
		return true;
	}
	
	// Steps the tokenizer to the next token on this line, returns false if no tokens left //
	bool NextToken() {
		// Store the stream position, just in case //
		std::streampos Position = Line.tellg();
		
		// Grab the next token of the line //
		Line >> CurrentToken;
		
		// If the token begins with a quote, it's a string //
		// NOTE: multi-line strings not supported. //
		if ( CurrentToken[0] == '\"' ) {
			// Undo the step //
			Line.seekg( Position );
			
			// Seek out the first quote (hack) //
			getline( Line, CurrentToken, '\"' );
			
			// Store the contents up until the 2nd quote //
			getline( Line, CurrentToken, '\"' );
		}
		// If the token begins with a "/" //
		else if ( CurrentToken[0] == '/' ) {
			// If it's followed by a 2nd "/", it's a C++ line comment //
			if ( CurrentToken[1] == '/' ) {
				// Jump to the end of the line //
				Line.seekg( 0, std::ios_base::end );
				// Return that we failed to find a suitable token //
				return false;
			}
			// Note: Block comments would only work for a singe line, without a flag. //
		}
			
		return !Line.eof();
	}
	
	// Returns true if the next token exists //
	bool IsTokenAvailable() {
		return !Line.eof();
	}

public:
	// Tests if the current token matches a pattern //
	bool IsStringToken( const char* Pattern ) {
		return CurrentToken == std::string( Pattern );
	}
	
	// Returns the current token as a string //
	const std::string StringToken() {
		return CurrentToken;
	}
	
	// Returns the current token as a string, and steps to the next token //
	const std::string StepStringToken() {
		const std::string Token = StringToken();
		NextToken();
		return Token;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Tests if the current token matches a pattern //
	bool IsIntegerToken( const int Pattern ) {
		return atoi(CurrentToken.c_str()) == Pattern;
	}
	
	// Returns the current token as an Integer //
	const int IntegerToken() {
		return atoi(CurrentToken.c_str());
	}
	
	// Returns the current token as an Integer, and steps to the next token //
	const int StepIntegerToken() {
		const int Token = IntegerToken();
		NextToken();
		return Token;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Tests if the current token matches a pattern //
	bool IsFloatToken( const float Pattern ) {
		return atof(CurrentToken.c_str()) == Pattern;
	}
	
	// Returns the current token as a Float //
	const float FloatToken() {
		return atof(CurrentToken.c_str());
	}
	
	// Returns the current token as a Float, and steps to the next token //
	const float StepFloatToken() {
		const float Token = FloatToken();
		NextToken();
		return Token;
	}
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __WhitespaceTokenizer_H__ //
// - ------------------------------------------------------------------------------------------ - //
