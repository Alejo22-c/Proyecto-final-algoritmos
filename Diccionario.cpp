#include <iostream>
#include <conio.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <string>
#define CLEAR "cls"
using namespace std;

class menu
{
private:
    string nombre;
    string traduccion;
    string funcion;
    string codigopalabra;
    string hola;

public:
    void agregar();
    void eliminar();
    void modificar();
    void listarpalabras();
    void diccionario();
    void mostarRegistro(string codigo);
    void PrincipalMenu();
    void menuPrincipal();
    void traductor();
};

void pausa();
void error();

    

void menu::PrincipalMenu(){
	int opc;
	do{
		cout<<"						PROYECTO FINAL DE ALGORITMOS :)\n\n\n";
		cout<<"1.Diccionario\n";
		cout<<"2.Traductor de codigo fuente\n";
		cout<<"3.Salir\n\n";
		cout<<"Opcion: ";
		cin>>opc;
		system(CLEAR);
		switch(opc){
			default:
            cout<<"Ha ingresado una opcion no valida!"<<endl;
            break;
            
            case 1:
            	menuPrincipal();
            	break;
            case 2:{
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
            	break;
			}
            case 3:
            	break;
		}
	}while(opc!=3);
}
	
void menu::menuPrincipal(){
    int opcion;
    do
    {
        cout<<"                     PROYECTO DICCIONARIO DE PALABRAS RESERVADAS"<<endl;
        cout<<""<<endl;
        cout<<""<<endl;
        cout<<"1. Agregar una nueva palabra"<<endl;
        cout<<"2. Diccionario"<<endl;
        cout<<"3. Listar palabras"<<endl;
        cout<<"4. Eliminar una palabra"<<endl;
        cout<<"5. Modificar una traduccion"<<endl;
        cout<<"6. Salir\n\n"<<endl;
        cout<<"Opcion: ";
        cin>>opcion;
        system(CLEAR);
        switch(opcion)
        {
        default:
            cout<<"Ha ingresado una opcion no valida!"<<endl;
            break;

        case 1:
            agregar();
            break;

        case 2:
            diccionario();
            break;

        case 3:
            listarpalabras();
            break;

        case 4:
            eliminar();
            break;

        case 5:
            modificar();
            break;

        case 6:
            break;
        }
    }
    while(opcion!=6);
}

void menu::agregar(){
    ofstream escritura;
    ifstream verificador;
    string auxCodigo;
    bool coincidencia=false;
    verificador.open("datos.txt",ios::in);
    escritura.open("datos.txt",ios::app);
    if(escritura.is_open()&&verificador.is_open())
    {
        cout<<"AGREGAR UNA PALABRA AL DICCIONARIO"<<endl;
        fflush(stdin);
        cout<<""<<endl;
        cout<<""<<endl;
        
        codigopalabra=auxCodigo;
        cout<<"\n Ingresar nueva palabra\n\n"<<endl;
        cout<<"Ingresa el nombre de la palabra reservada: ";
        getline(cin,nombre);
        cout<<""<<endl;
        fflush(stdin);
        cout<<"Ingresa la traduccion de la palabra: ";
        getline(cin,traduccion);
        cout<<""<<endl;
        fflush(stdin);
        cout<<"Ingresa la funcion de la palabra reservada: ";
        getline(cin,funcion);
        cout<<""<<endl;
        fflush(stdin);

        escritura<<"\n"<<nombre<<endl<<traduccion<<endl<<funcion<<endl;

        cout<<"El registro se ha completado correctamente."<<endl;
        cout<<""<<endl;
    }

    else
    {
        error();
    }

    escritura.close();
    verificador.close();
    pausa();
}

void menu::eliminar(){
    ifstream lectura;
    ofstream auxiliar;
    bool encontrado=false;
    string auxNombre;
    char respuesta[5];
    lectura.open("datos.txt",ios::in);
    auxiliar.open("auxiliar.txt",ios::out);
    cout<<"Eliminar una palabra de nuestro diccionario"<<endl;
    if(lectura.is_open()&&auxiliar.is_open())
    {
        fflush(stdin);
        cout<<"Ingresa la palabra que quieres eliminar: ";
        getline(cin,auxNombre);
        getline(lectura,nombre);
        while(!lectura.eof())
        {
            getline(lectura,nombre);
            getline(lectura,traduccion);
            getline(lectura,funcion);

            if(auxNombre==nombre)
            {
                encontrado=true;
                cout<<"Registro Encontrado"<<endl;
                cout<<"Palabra reservada: "<<nombre<<endl;
                cout<<"Traduccion: "<<traduccion<<endl;
                cout<<"Funcion: "<<funcion<<endl;
                cout<<""<<endl;
                cout<<"Realmente deseas eliminar a: "<<nombre<<" (s/n)?: ";
                cin.getline(respuesta,5);
                if(strcmp(respuesta,"s")==0||strcmp(respuesta,"S")==0||
                        strcmp(respuesta,"si")==0||strcmp(respuesta,"SI")==0||
                        strcmp(respuesta,"Si")==0||strcmp(respuesta,"sI")==0)
                {
                    cout<<"Se ha eliminado correctamente la palabra";
                }

                else
                {

                    cout<<"Palabra reservada aun registrada :)";
                    auxiliar<<"\n"<<nombre<<endl<<traduccion<<endl<<funcion<<endl;

                }

            }
            else
            {
                auxiliar<<"\n"<<nombre<<endl<<traduccion<<endl<<funcion<<endl;
            }
            getline(lectura,nombre);
        }
        if(encontrado==false)
        {
            cout<<"No se encuentra la palabra: "<<auxNombre<<endl;
        }

    }
    else
    {
        error();
    }
    lectura.close();
    auxiliar.close();
    remove("datos.txt");
    rename("auxiliar.txt","datos.txt");
    pausa();
}

void menu::diccionario(){
    string auxNombre;
    ifstream mostrar;
    bool encontrado=false;
    mostrar.open("datos.txt",ios::in);
    if(mostrar.is_open())
    {
        fflush(stdin);
        cout<<"DICCIONARIO DE PALABRAS RESERVADAS"<<endl;
        cout<<""<<endl;
        cout<<"Ingresa el nombre de la palabra que deseas consultar detalles: ";
        getline(cin,auxNombre);
        getline(mostrar,nombre);
        while(!mostrar.eof())
        {
        	getline(mostrar,nombre);
            getline(mostrar,traduccion);
            getline(mostrar,funcion);

            if(auxNombre==nombre)
            {
                encontrado=true;
                cout<<"Registro Encontrado"<<endl;
        		cout<<""<<endl;
                cout<<"Nombre: "<<nombre<<endl;
                cout<<"Traduccion: "<<traduccion<<endl;
                cout<<"Funcion: "<<funcion<<endl;
                cout<<""<<endl;
            }

            getline(mostrar,nombre);
        }

        if(encontrado==false)
        {
            cout<<"No se encontro el registro: "<<auxNombre<<endl;
        }
    }

    else
    {
        error();
    }

    mostrar.close();
    pausa();
}

void menu::modificar(){
    ifstream lectura;
    ifstream verificador;
    ofstream auxiliar;
    string nombreModif;
    string auxNombre;
    string auxTraduccion;
    string auxFuncion;
    bool coincidencia=false;
	bool mismoNombre=false;
	bool encontrado=false;
    lectura.open("datos.txt",ios::in);
    verificador.open("datos.txt",ios::in);
    auxiliar.open("auxiliar.txt",ios::out);
    cout<<"Modificar los datos de una palabra reservada"<<endl;
    if(lectura.is_open()&&verificador.is_open()&&auxiliar.is_open())
    {
        fflush(stdin);
        cout<<"Ingresa la palabra que deseas modificar: ";
        getline(cin,auxNombre);

        if(auxNombre=="")
        {
            do
            {
                cout<<"Palabra no valida!, intentalo nuevamente: ";
                getline(cin,auxNombre);
            }
            while(auxNombre=="");
        }

        nombreModif=auxNombre;

        getline(lectura,nombre);
        while(!lectura.eof())
        {
            getline(lectura,nombre);
            getline(lectura,traduccion);
            getline(lectura,funcion);

            if(auxNombre==nombre)
            {
                encontrado=true;
                mostarRegistro(nombreModif);

                cout<<"**********************************************";
                cout<<""<<endl;
                cout<<"***Modificar los datos de una palabra***";
                cout<<"Ingresa la palabra que deseas modificar: ";
                cout<<nombreModif;
                mostarRegistro(nombreModif);
                cout<<"**********************************************";
                cout<<""<<endl;
                cout<<"Ingresa la nueva informacion para la palabra"<<endl;
                cout<<""<<endl;
                cout<<"Ingresa el nuevo nombre de la palabra reservada: ";
                getline(cin,auxNombre);
                fflush(stdin);
                cout<<""<<endl;
                cout<<"Ingresa la traduccion de la palabra: ";
                getline(cin,auxTraduccion);
                cout<<""<<endl;
                fflush(stdin);
                cout<<"Ingresa la funcion de la palabra: ";
                getline(cin,auxFuncion);
                cout<<""<<endl;
                fflush(stdin);
                auxiliar<<"\n"<<auxNombre<<endl<<auxTraduccion<<endl<<auxFuncion<<endl;
                cout<<"El Registro se ha modificado correctamente."<<endl;
            }


            else
            {

                auxiliar<<"\n"<<nombre<<endl<<traduccion<<endl<<funcion<<endl;
            }


            getline(lectura,nombre);
		}      

    }
    else
    {
        error();
    }

    if(encontrado==false)
    {
        cout<<"No se encontro ninguna palabra!"<<endl;
    }
    lectura.close();
    verificador.close();
    auxiliar.close();
    remove("datos.txt");
    rename("auxiliar.txt","datos.txt");
    pausa();
}

void menu::listarpalabras(){
    int i=0;
    ifstream lectura;
    lectura.open("datos.txt",ios::in);
    if(lectura.is_open())
    {
        cout<<"LISTADO DE TODAS LAS PALABRAS";
        getline(lectura,codigopalabra);
        cout<<""<<endl;
        cout<<""<<endl;
        while(!lectura.eof())
        {
            i++;
            getline(lectura,nombre);
            getline(lectura,traduccion);
            getline(lectura,funcion);
            cout<<"Palabra reservada: "<<nombre<<endl;
            cout<<"Traduccion: "<<traduccion<<endl;
            cout<<"Funcion: "<<funcion<<endl;
            cout<<""<<endl;
            getline(lectura,nombre);
        }

        if(i==1)
            cout<<"Hay una sola palabra registrada en el diccionario."<<endl;

        else

            cout<<"Hay un total de "<<i<<" palabras registradas en este diccionario"<<endl;
    }
    else
    {
        error();
    }
    lectura.close();
    pausa();
}

void pausa(){
    cout<<"Presiona Enter para continuar...";
    getch();
    system(CLEAR);
}

int main(){
    system ("color f0");
    menu inicio;
    inicio.PrincipalMenu();
    return 0;
}

    

void error(){
    cout<<"No se pudo abrir el archivo de registros, asegurese que el archivo se encuentre en\n";
    cout<<"la misma ubicaci\242n que el programa o que el archivo de texto se llame: \n";
    cout<<"datos.txt, si el archivo tiene otro nombre ren\242mbrelo al ya mencionado\n\n";
}

void menu::mostarRegistro(string codigo){

    ifstream mostrar;
    mostrar.open("datos.txt",ios::in);
    getline(mostrar,codigopalabra);
    while(!mostrar.eof())
    {
        getline(mostrar,nombre);
        getline(mostrar,traduccion);
        getline(mostrar,funcion);

        if(codigo==codigopalabra)
        {
            cout<<"REGISTRO ENCONTRADO\n\n"<<endl;
            cout<<"Palabra reservada: "<<nombre<<endl;
            cout<<"Traduccion: "<<traduccion<<endl;
            cout<<"Funcion: "<<funcion<<endl;
            cout<<""<<endl;
        }

        getline(mostrar,codigopalabra);
    }

    mostrar.close();
}

void traductor(){
	
}
