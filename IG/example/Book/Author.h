/* Header for Author class (Author.h) */
#ifndef AUTHOR_H
#define AUTHOR_H
 
#include <string>
 
class Author {
private:
   std::string name;
   std::string email;
   char gender;   // 'm', 'f', or 'u' for unknown
 
public:
   Author(const std::string & name, const std::string & email, char gender);
          // & specifies pass by reference, const for non-mutable
   std::string getName() const;
   std::string getEmail() const;
   void setEmail(const std::string & email);
   char getGender() const;
   void print() const;
};
 
#endif