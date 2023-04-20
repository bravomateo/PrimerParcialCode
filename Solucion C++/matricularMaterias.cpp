#include <iostream>
#include <fstream>
using namespace std;

bool sonIguales(char* str1, char* str2);

int contarMaterias();

void horasIndividualesArreglo (int horasMatIndividuales[]);

void matricularHorario(char (&horario)[7][24], char* numeroLista, char* horaClase);

void matricularMaterias(char (&horario)[7][24], const string& nombreArchivo);

int main() {

    // Crear un arreglo de 7 filas y 24 columnas
    char horario[7][24];

    // Asignar valores al arreglo
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 24; j++) {
            horario[i][j] = '-';
        }
    }

    matricularMaterias(horario, "materias.txt");
    
    // Imprimir el horario
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 24; j++) {
            cout << horario[i][j] << " ";
        }
        cout << endl;
    }


    // imprimir arreglo de horas individuales
    int numeroMaterias = contarMaterias();
    int HorasIndividuales[numeroMaterias];

    horasIndividualesArreglo(HorasIndividuales);



    

    //for (int indexMateria = 0; indexMateria < numeroMaterias; indexMateria++)

    for (int indexMateria = 0; indexMateria < 8; indexMateria++) {
        cout << "Materia: "<< indexMateria + 1 << "; Horas de estudio: " << HorasIndividuales[indexMateria] << " ** " << endl;
        cout << endl;
        int HorasIndMaterias = HorasIndividuales[indexMateria];

        for (int horasMateria = HorasIndMaterias; horasMateria > 0 ; horasMateria--) {
            cout << horasMateria << endl;

            // Recorrer todos los días de la semana y explorar cada hora del día
            for (int dia = 0; dia < 7; dia++) { // iterar sobre los días de la semana
                for (int hora = 0; hora < 24; hora++) { // iterar sobre las horas del día
                    if (horario[dia][hora] == '-') { 
                        horario[dia][hora] = static_cast<char>(indexMateria+97);
                        break;
                    } 
                }
            }

            // Imprimir el horario
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 24; j++) {
                    cout << horario[i][j] << " ";
                }
                cout << endl;
            }
        }

    }

    cout << endl;



    return 0;
}



void matricularHorario(char (&horario)[7][24], char* numeroLista, char* horaClase) {
    // Obtener el día de la semana
    char diaSemana = horaClase[0];
    int fila = -1;
    switch(diaSemana) {
        case 'L': fila = 0; break;
        case 'M': fila = 1; break;
        case 'W': fila = 2; break;
        case 'J': fila = 3; break;
        case 'V': fila = 4; break;
        case 'S': fila = 5; break;
        case 'D': fila = 6; break;
    }
    
    // Obtener la hora de inicio y fin de la clase
    int horaInicio = (horaClase[1] - '0') * 10 + (horaClase[2] - '0');
    int horaFin = (horaClase[4] - '0') * 10 + (horaClase[5] - '0');
    
    // Marcar en el horario las horas de la clase
    for (int i = horaInicio; i < horaFin; i++) {
        horario[fila][i] = numeroLista[0];
    }
}

void matricularMaterias(char (&horario)[7][24], const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    

    // #numero,nombre,codigo,creditos,horasTeoricas,horasPracticas,HoraClase1, HoraClase2, HoraClase3
    char* numeroLista    = new char[100];
    char* nombre    = new char[100];
    char* codigo    = new char[100];
    char* creditos  = new char[100];
    char* horasTeoricas  = new char[100];
    char* horasPracticas = new char[100];
    char* horaClase1    = new char[100];
    char* horaClase2    = new char[100];
    char* horaClase3    = new char[100];

    while (
    archivo.getline(numeroLista, 100, ',')  &&
    archivo.getline(nombre, 100, ',')       &&
    archivo.getline(codigo, 100, ',')       &&
    archivo.getline(creditos, 100, ',')     &&
    archivo.getline(horasTeoricas, 100, ',')    &&
    archivo.getline(horasPracticas, 100, ',')   &&
    archivo.getline(horaClase1, 100, ',')   &&
    archivo.getline(horaClase2, 100, ',')   &&
    archivo.getline(horaClase3, 100)
    ) {
    
    // Asignar los respectivos valores al arreglo

        // Llenar Horario para la clase semanal 1
        if (horaClase1[0] != 'X') {    
            matricularHorario(horario, numeroLista, horaClase1);
        }
        
        // Llenar Horario para la clase semanal 2
        if (horaClase2[0] != 'X') {    
            matricularHorario(horario, numeroLista, horaClase2);
        }
        
        // Llenar Horario para la clase semanal 2
        if (horaClase3[0] != 'X') {    
            matricularHorario(horario, numeroLista, horaClase3);
        }

    }

    archivo.close();
    // Liberar la memoria asignada dinámicamente
    delete[] numeroLista;
    delete[] nombre;
    delete[] codigo;
    delete[] creditos;
    delete[] horasTeoricas;
    delete[] horasPracticas;
    delete[] horaClase1;
    delete[] horaClase2;
    delete[] horaClase3;

    archivo.close();
}

void horasIndividualesArreglo (int horasMatIndividuales[]) {
    
    ifstream archivo("materias.txt");

    //int numeroMaterias = contarMaterias(); // tener en cuenta 

    // #numero,nombre,codigo,creditos,horasTeoricas,horasPracticas,HoraClase1, HoraClase2, HoraClase3
    char* numeroLista    = new char[100];
    char* nombre    = new char[100];
    char* codigo    = new char[100];
    char* creditos  = new char[100];
    char* horasTeoricas  = new char[100];
    char* horasPracticas = new char[100];
    char* horaClase1    = new char[100];
    char* horaClase2    = new char[100];
    char* horaClase3    = new char[100];

    int indexacion = 0;


    while (
    archivo.getline(numeroLista, 100, ',')  &&
    archivo.getline(nombre, 100, ',')       &&
    archivo.getline(codigo, 100, ',')       &&
    archivo.getline(creditos, 100, ',')     &&
    archivo.getline(horasTeoricas, 100, ',')    &&
    archivo.getline(horasPracticas, 100, ',')   &&
    archivo.getline(horaClase1, 100, ',')   &&
    archivo.getline(horaClase2, 100, ',')   &&
    archivo.getline(horaClase3, 100)
    ) {
    
    int horasIndividuales;
    char ingles1[] = "2538101";
    char ingles2[] = "2538201";
    char ingles3[] = "2538301";
    char ingles4[] = "2538401";
    char ingles5[] = "2538501";
    char ingles6[] = "2538601";

    if (    sonIguales(codigo, ingles1) == false && 
            sonIguales(codigo, ingles2) == false && 
            sonIguales(codigo, ingles3) == false && 
            sonIguales(codigo, ingles4) == false && 
            sonIguales(codigo, ingles5) == false && 
            sonIguales(codigo, ingles6) == false
            
    ) {
        horasIndividuales = ((static_cast<int>(creditos[0])-48)*48)/16  -  ( (static_cast<int>(horasTeoricas[0])-48) + (static_cast<int>(horasPracticas[0])-48) );
    }

    else {
        horasIndividuales = 4;
    }

    horasMatIndividuales[indexacion] = horasIndividuales;
    indexacion++;

    }

    archivo.close();
    // Liberar la memoria asignada dinámicamente
    delete[] numeroLista;
    delete[] nombre;
    delete[] codigo;
    delete[] creditos;
    delete[] horasTeoricas;
    delete[] horasPracticas;
    delete[] horaClase1;
    delete[] horaClase2;
    delete[] horaClase3;

    archivo.close();


}

int contarMaterias() {
    ifstream archivo("materias.txt");
    int num_lineas = 0;
    string linea;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            num_lineas++;
        }
        archivo.close();
    }

    return num_lineas;
}

bool sonIguales(char* str1, char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return false;
        }
        i++;
    }
    return (str1[i] == '\0' && str2[i] == '\0');
}