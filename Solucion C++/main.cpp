#include <iostream>
#include <fstream>
using namespace std;


void matricularHorario(char (&horario)[7][24], char* numeroLista, char* horaClase);

int main() {
    ifstream archivo("materias.txt");

    // Crear un arreglo de 7 filas y 24 columnas
    char horario[7][24];

    // Asignar valores al arreglo
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 24; j++) {
            horario[i][j] = '-';
        }
    }
    

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


        // Imprimir el horario
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 24; j++) {
                cout << horario[i][j] << " ";
        }
        cout << endl;
    }
    cout << horaClase1 << " " << horaClase2 << " " << horaClase3 << endl;
    cout << endl;
    

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
