#include <iostream>
#include <fstream>
using namespace std;


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

int main() {
    // Crear un arreglo de 7 filas y 24 columnas
    char horario[7][24];

    // Asignar valores al arreglo
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 24; j++) {
            horario[i][j] = 'D';
        }
    }
    

    char numeroLista1[] = "1";
    char horaClase1[] = "L18-24";
    matricularHorario(horario, numeroLista1, horaClase1);

    char numeroLista2[] = "2";
    char horaClase2[] = "M06-08";
    matricularHorario(horario, numeroLista2, horaClase2);
    
    // Imprimir el horario
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 24; j++) {
            cout << horario[i][j];
        }
        cout << endl;
    }
    
    return 0;
}

