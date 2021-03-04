/*
 * Copyright (C) Rida Bazzi, 2020
 *
 * Do not share this file with anyone
 *
 * Do not post this file or derivatives of
 * of this file online
 *
 */
#include <iostream>
#include <cstdlib>
#include "parser.h"

using namespace std;

void Parser::syntax_error()
{
    cout << "SYNTAX ERROR\n";
    exit(1);
}

// this function gets a token and checks if it is
// of the expected type. If it is, the token is
// returned, otherwise, synatx_error() is generated
// this function is particularly useful to match
// terminals in a right hand side of a rule.
// Written by Mohsen Zohrevandi
Token Parser::expect(TokenType expected_type)
{
    Token t = lexer.GetToken();
    if (t.token_type != expected_type)
        syntax_error();
    return t;
}

// Parsing

// This function is simply to illustrate the GetToken() function
// you will not need it for your project and you can delete it
// the function also illustrates the use of peek()
void Parser::ConsumeAllInput()
{
    Token token;
    int i = 1;
    
    token = lexer.peek(i);
    token.Print();
    while (token.token_type != END_OF_FILE)
    {
        i = i+1;
        token = lexer.peek(i);
        token.Print();
    }
   
    token = lexer.GetToken();
    token.Print();
    while (token.token_type != END_OF_FILE)
    {
        token = lexer.GetToken();
        token.Print();
    }

}

void Parser::parse_input() {
  parse_tokens_section();

  Token t;
  t = expect(INPUT_TEXT);
  t = expect(END_OF_FILE);
}

void Parser::parse_tokens_section() {
  parse_token_list();

  Token t;
  t = expect(HASH);
}

void Parser::parse_token_list() {
  parse_token();

  Token t = lexer.peek(1);
  if (t.token_type == COMMA) {
    t = expect(COMMA);
    parse_token_list();
  }
}

void Parser::parse_token() {
  Token t;
  t = expect(ID);

  parse_expr();
}

struct REG * Parser::parse_expr() {
  Token t = lexer.peek(1);
  if (t.token_type == LPAREN) {
    t = expect(LPAREN);
    parse_expr();
    t = expect(RPAREN);

    t = lexer.peek(1);
    if (t.token_type == DOT) {
      t = expect(DOT);
      t = expect(LPAREN);
      parse_expr();
      t = expect(RPAREN);
    }
    else if (t.token_type == OR) {
      t = expect(OR);
      t = expect(LPAREN);
      parse_expr();
      t = expect(RPAREN);
    }
    else if (t.token_type == STAR) {
      t = expect(STAR);
    }
    else {
      syntax_error();
    }
  }
  else if (t.token_type == CHAR) {
    t = expect(CHAR);
  }
  else if (t.token_type == UNDERSCORE) {
    t = expect(UNDERSCORE);
  }
  else {
    syntax_error();
  }
}

int main()
{
	// note: the parser class has a lexer object instantiated in it. You should not be declaring
    // a separate lexer object. You can access the lexer object in the parser functions as shown in the
    // example method Parser::ConsumeAllInput
    // If you declare another lexer object, lexical analysis will not work correctly
    Parser parser;

	//parser.ConsumeAllInput();

	parser.parse_input();
	
}
