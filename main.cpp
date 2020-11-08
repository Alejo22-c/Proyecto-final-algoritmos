
#include <iostream>
#include <string>
 
using namespace std;
int main()
{
	cout << "\n ingrese el texto "<<endl;
		char* original = new char[50];
		string hola ;
	getline(cin,hola);
	
  string::size_type pos = 0;
  cout<<"\n codigo maquina: "<<hola<<endl;
  string reserved[11] = {"int", "string","double","char","get line","main","for","return","if","exit","endl"};
  string toStr[11] = {"entero","cadena","doble","caracter","obtener linea","principal","para","retornar","si","salida","finalizar"};
  
  for (int i = 0; i < 11; ++i) 
  {
    while ((pos = hola.find(reserved[i], pos)) < string::npos)
    {
      hola.replace(pos, reserved[i].length(), toStr[i]);
      pos+=toStr[i].size();
    }
    pos = 0;
  }
  
 
  cout << "\n traducido: "<<hola<<endl;
}
