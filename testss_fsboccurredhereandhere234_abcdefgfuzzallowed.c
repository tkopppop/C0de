#include <locale.h>
#define AAA/*//{}x*/ ("***\n\n\npronformatstrinbugshahahalamme")
int main(void){setlocale(LC_ALL, "");printf(AAA/*dangerformatstringbugpronwarningsinhereatthereonexploitpossible-securitybulitinsx90csmamawinprogrammerdevelopercoder*/);formatbugstring(10);}
int formatbugstring(int s){
  printf("%s\n", s);
}
