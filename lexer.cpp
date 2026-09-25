#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

enum class TokenType
{
  TOKEN_FLOAT,     // "float"
  TOKEN_INT,       // "int"
  TOKEN_STR,       // "string"
  TOKEN_ID,        // variable or function names
  TOKEN_ASSIGN,    // "="
  TOKEN_MULT,      // "*"
  TOKEN_DIV,       // "/"
  TOKEN_ADD,       // "+"
  TOKNE_SUB,       // "-"
  TOKEN_SEMICOLON, // ";"
  TOKEN_SLASH,     // "/"
  TOKEN_LPAREN,    // "("
  TOKEN_RPAREN,    // ")"
  TOKEN_LBRACE,    // "{"
  TOKEN_RBRACE,    // "}"
  TOKEN_EOF,       // End of File
  TOKEN_UK         // Syntax error / unknown character
};

struct Token
{
  TokenType type;
  std::string lexem;
  int line;
};

class Lexer
{
private:
  std::string src;
  size_t cursor = 0;
  int line = 1;

  char peekChar()
  {
    if (cursor >= src.length())
    {
      return '\0';
    }
    return src[cursor];
  }

  char nextChar()
  {
    if (cursor >= src.length())
    {
      return '\0';
    }
    return src[cursor++];
  }

  void skipWhiteSP()
  {
    while (cursor < src.length())
    {
      char c = peekChar();
      if (c == ' ' || c == '\r' || c == '\t')
      {
        c = nextChar();
      }
    else if (c == '\n')
      {
        line++;
        c = nextChar();
      }
      else
      {
        break;
      }
    }
  }

public:
  explicit Lexer(std::string file) : src(std::move(file)) {}

  Token getNextToken()
  {
    skipWhiteSP();
    if (cursor >= src.length())
    {
      return Token{TokenType::TOKEN_EOF, "", line};
    }

    char c = nextChar();

    switch (c)
    {
    case ';':
      return Token{TokenType::TOKEN_SEMICOLON, ";", line};
    case '(':
      return Token{TokenType::TOKEN_LPAREN, "(", line};
    case ')':
      return Token{TokenType::TOKEN_RPAREN, ")", line};
    case '{':
      return Token{TokenType::TOKEN_LBRACE, "{", line};
    case '}':
      return Token{TokenType::TOKEN_RBRACE, "}", line};
    case '+':
      return Token{TokenType::TOKEN_ADD, "+", line};
    case '-':
      return Token{TokenType::TOKNE_SUB, "-", line};
    case '*':
      return Token{TokenType::TOKEN_MULT, "*", line};
    case '/':
      return Token{TokenType::TOKEN_DIV, "/", line};
    case '=':
      return Token{TokenType::TOKEN_ASSIGN, "=", line};
    default:
      break;
    }

    std::string lexem = "";

    if (std::isalpha(c))
    {
      lexem.push_back(c);
      while (std::isalnum(peekChar()))
      {
        c = nextChar();
        lexem.push_back(c);
      }
       if (lexem == "float")
        {
          return Token{TokenType::TOKEN_FLOAT, lexem, line};
        } 
         if (lexem == "int")
        {
          return Token{TokenType::TOKEN_INT, lexem, line};
        }
        if (lexem == "string")
        {
          return Token{TokenType::TOKEN_STR, lexem, line};
        }
       return Token{TokenType::TOKEN_ID, lexem, line};
    }
    else
    {
    while (cursor < src.length() && !(peekChar() == ' ' || std::isblank(peekChar())))
      {
        lexem += nextChar();
      }
      return Token{TokenType::TOKEN_UK, lexem, line};
    }
  }
};

// can be used to open files to read
// std::vector<std::string> parseLine(std::string &line)
// {
//   std::vector<std::string> args;
//   std::stringstream ss(line);
//   std::string arg;
//   while (ss >> arg)
//   {
//     args.push_back(arg);
//   }
//   return args;
// }
// void parseFile(std::ifstream &file, std::vector<std::vector<std::string>> &parsedLines)
// {
//   if(!file.is_open())
//   {
//     std::cerr << "File can not be open\n";
//     return;
//   }
//   std::string line;
//   while(std::getline(file,line))
//   {
//     parsedLines.push_back(parseLine(line));
//   }
//   file.close();
//   return;
// }

int main()
{

  return 0;
}
