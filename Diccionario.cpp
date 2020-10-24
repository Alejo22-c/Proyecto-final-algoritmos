#include <iostream>
#include <conio.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>

#define CLEAR "cls"
using namespace std;
class menu
{
private:
    string nombre;
    string traduccion;
    string funcion;
    string codigopalabra;

public:
    void agregar();
    void eliminar();
    void modificar();
    void listarpalabras();
    void menuPrincipal();
    void diccionario();
    void mostarRegistro(string codigo);
};

void pausa();
void error();

void menu::menuPrincipal()
{
    int opcion;
    do
    {
        cout<<"                     Registro de palabras reservadas de un IDE"<<endl;
        cout<<""<<endl;
        cout<<""<<endl;
        cout<<"1. Agregar una nueva palabra"<<endl;
        cout<<"2. Diccionario de palabras"<<endl;
        cout<<"3. Listar palabras"<<endl;
        cout<<"4. Eliminar una palabra"<<endl;
        cout<<"5. Modificar una traduccion"<<endl;
        cout<<"6. Salir"<<endl;
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

void menu::agregar()
{
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
        cout<<"Ingresa el codigo de la palabra: ";
        getline(cin,auxCodigo);
        if(auxCodigo=="")
            do
            {
                cout<<"codigo de palabra no valido!, intentalo nuevamente: "<<endl;
                getline(cin,auxCodigo);
            }
            while(auxCodigo=="");
        do
        {
            verificador.seekg(0);
            getline(verificador,codigopalabra);
            while(!verificador.eof())
            {
                getline(verificador,nombre);
                getline(verificador,traduccion);
                getline(verificador,funcion);

                if(codigopalabra==auxCodigo)
                {
                    coincidencia=true;
                    cout<<"Ya existe un cliente con ese codigo!"<<endl;
                    cout<<"El cliente con ese codigo es: "<<nombre<<endl;
                    cout<<"Ingresa un codigo valido!: ";
                    getline(cin,auxCodigo);
                    if(auxCodigo=="")
                        do
                        {
                            cout<<"codigo de cliente no valido!, intentalo nuevamente: ";
                            getline(cin,auxCodigo);
                        }
                        while(auxCodigo=="");

                    break;
                }

                getline(verificador,codigopalabra);
            }

            if(verificador.eof()&&auxCodigo!=codigopalabra)
                coincidencia=false;

        }
        while(coincidencia==true);
        system(CLEAR);
        codigopalabra=auxCodigo;
        cout<<"Ingresar nueva palabra"<<endl;
        cout<<"Ingresa el codigo de la palabra: ";
        cout<<codigopalabra;
        cout<<""<<endl;
        fflush(stdin);
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

        escritura<<codigopalabra<<endl<<nombre<<endl<<traduccion<<endl<<funcion
                 <<endl;

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

void menu::eliminar()
{
    ifstream lectura;
    ofstream auxiliar;
    bool encontrado=false;
    string auxCodigo;
    char respuesta[5];
    lectura.open("datos.txt",ios::in);
    auxiliar.open("auxiliar.txt",ios::out);
    cout<<"Eliminar una palabra de nuestro diccionario"<<endl;
    if(lectura.is_open()&&auxiliar.is_open())
    {
        fflush(stdin);
        cout<<"Ingresa el codigo de la palabra que quieres eliminar: ";
        getline(cin,auxCodigo);
        getline(lectura,codigopalabra);
        while(!lectura.eof())
        {
            getline(lectura,nombre);
            getline(lectura,traduccion);
            getline(lectura,funcion);

            if(auxCodigo==codigopalabra)
            {
                encontrado=true;
                cout<<"Registro Encontrado"<<endl;
                cout<<"Codigo: "<<codigopalabra<<endl;
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
                    auxiliar<<codigopalabra<<endl<<nombre<<endl<<traduccion<<endl<<
					funcion<<endl;

                }

            }
            else
            {
                auxiliar<<codigopalabra<<endl<<nombre<<endl<<traduccion<<endl<<funcion
                        <<endl;
            }
            getline(lectura,codigopalabra);
        }
        if(encontrado==false)
        {
            cout<<"No se encuentra el codigo: "<<auxCodigo<<endl;
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

void menu::diccionario()
{
    string auxCodigo;
    ifstream mostrar;
    bool encontrado=false;
    mostrar.open("datos.txt",ios::in);
    if(mostrar.is_open())
    {
        fflush(stdin);
        cout<<"DICCIONARIO DE PALABRAS RESERVADAS";
        cout<<"Ingresa el codigo de la palabra que deseas consultar detalles: ";
        getline(cin,auxCodigo);
        getline(mostrar,codigopalabra);
        while(!mostrar.eof())
        {
            getline(mostrar,nombre);
            getline(mostrar,traduccion);
            getline(mostrar,funcion);

            if(auxCodigo==codigopalabra)
            {
                encontrado=true;
                cout<<"Registro Encontrado"<<endl;
                cout<<"Codigo: "<<codigopalabra<<endl;
                cout<<"Nombre: "<<nombre<<endl;
                cout<<"Traduuccion: "<<traduccion<<endl;
                cout<<"Funcion: "<<funcion<<endl;
                cout<<""<<endl;
            }

            getline(mostrar,codigopalabra);
        }

        if(encontrado==false)
        {
            cout<<"No se encontro el registro: "<<auxCodigo<<endl;
        }
    }

    else
    {
        error();
    }

    mostrar.close();
    pausa();
}

void menu::modificar()
{
    ifstream lectura;
    ifstream verificador;
    ofstream auxiliar;
    string auxCodigo;
    string codigoModif;
    string auxNombre;
    string auxTraduccion;
    string auxFuncion;
    bool encontrado=false;
    bool coincidencia=false;
    bool mismoCodigo=false;
    lectura.open("datos.txt",ios::in);
    verificador.open("datos.txt",ios::in);
    auxiliar.open("auxiliar.txt",ios::out);
    cout<<"Modificar los datos de una palabra reservada"<<endl;
    if(lectura.is_open()&&verificador.is_open()&&auxiliar.is_open())
    {
        fflush(stdin);
        cout<<"Ingresa el codigo de la palabra que deseas modificar: ";
        getline(cin,auxCodigo);

        if(auxCodigo=="")
        {
            do
            {
                cout<<"codigo de cliente no valido!, intentalo nuevamente: ";
                getline(cin,auxCodigo);
            }
            while(auxCodigo=="");
        }

        codigoModif=auxCodigo;

        getline(lectura,codigopalabra);
        while(!lectura.eof())
        {
            getline(lectura,nombre);
            getline(lectura,traduccion);
            getline(lectura,funcion);

            if(auxCodigo==codigopalabra)
            {
                encontrado=true;
                mostarRegistro(codigoModif);

                cout<<"**********************************************";
                cout<<""<<endl;
                cout<<"Ingresa la nueva informacion para la palabra"<<endl;
                fflush(stdin);
                cout<<"Ingresa el codigo de la palabra: ";
                getline(cin,auxCodigo);
                if(auxCodigo==codigoModif)
                {
                    mismoCodigo=true;
                }
                if(mismoCodigo==false)
                {
                    do
                    {
                        if(auxCodigo==codigoModif)
                        {
                            coincidencia=false;
                            break;
                        }
                        verificador.seekg(0);
                        getline(verificador,codigopalabra);
                        while(!verificador.eof())
                        {
                            getline(verificador,nombre);
                            getline(verificador,traduccion);
                            getline(verificador,funcion);

                            if(auxCodigo==codigopalabra)
                            {
                                coincidencia=true;
                                cout<<"Ya existe una palabra con ese codigo!"<<endl;
                                cout<<"El cliente con ese codigo es: "<<nombre<<endl;
                                cout<<"Ingresa un codigo valido!: ";
                                getline(cin,auxCodigo);

                                if(auxCodigo=="")
                                {
                                    do
                                    {
                                        cout<<"codigo de cliente no valido!, ";
                                        cout<<"intentalo nuevamente: ";
                                        getline(cin,auxCodigo);
                                    }
                                    while(auxCodigo=="");
                                }
                                break;
                            }

                            getline(verificador,codigopalabra);
                        }

                        if(verificador.eof()&&auxCodigo!=codigopalabra)
                        {
                            coincidencia=false;
                        }

                    }
                    while(coincidencia==true);
                }
                system(CLEAR);
                cout<<"***Modificar los datos de una palabra***";
                cout<<"Ingresa el codigo de la palabra que deseas modificar: ";
                cout<<codigoModif;
                mostarRegistro(codigoModif);
                cout<<"**********************************************";
                cout<<""<<endl;
                cout<<"Ingresa la nueva informacion para la palabra"<<endl;
                cout<<""<<endl;
                cout<<"Ingresa el codigo de la palabra: ";
                cout<<auxCodigo;
                cout<<""<<endl;
                fflush(stdin);
                cout<<"Ingresa el nombre de la palabra reservada: ";
                getline(cin,auxNombre);;
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
                auxiliar<<auxCodigo<<endl<<auxNombre<<endl<<auxTraduccion<<endl<<auxFuncion
                        <<endl;
                cout<<"El Registro se ha modificado correctamente."<<endl;
            }


            else
            {

                auxiliar<<codigopalabra<<endl<<nombre<<endl<<traduccion<<endl<<funcion
                        <<endl;
            }


            getline(lectura,codigopalabra);
        }

    }
    else
    {
        error();
    }

    if(encontrado==false)
    {
        cout<<"No se encontro ningun registro con ese codigo!"<<endl;
    }
    lectura.close();
    verificador.close();
    auxiliar.close();
    remove("datos.txt");
    rename("auxiliar.txt","datos.txt");
    pausa();
}

void menu::listarpalabras()
{
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
            cout<<"Codigo: "<<codigopalabra<<endl;
            cout<<""<<endl;
            cout<<"Palabra reservada: "<<nombre<<endl;
            cout<<""<<endl;
            cout<<"Traduccion: "<<traduccion<<endl;
            cout<<""<<endl;
            cout<<"Funcion: "<<funcion<<endl;
            cout<<""<<endl;
            getline(lectura,codigopalabra);
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

void pausa()
{
    cout<<"Presiona Enter para continuar...";
    getch();
    system(CLEAR);
}

int main()
{
    system ("color f2");
    menu inicio;
    inicio.menuPrincipal();
    return 0;
}

void error()
{
    cout<<"No se pudo abrir el archivo de registros, asegurese que el archivo se encuentre en\n";
    cout<<"la misma ubicaci\242n que el programa o que el archivo de texto se llame: \n";
    cout<<"datos.txt, si el archivo tiene otro nombre ren\242mbrelo al ya mencionado\n\n";
}

void menu::mostarRegistro(string codigo)
{

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
            cout<<"REGISTRO ENCONTRADO"<<endl;
            cout<<"Codigo: "<<codigopalabra<<endl;
            cout<<"Palabra reservada: "<<nombre<<endl;
            cout<<"Traduccion: "<<traduccion<<endl;
            cout<<"Funcion: "<<funcion<<endl;
            cout<<""<<endl;
        }

        getline(mostrar,codigopalabra);
    }

    mostrar.close();
}
