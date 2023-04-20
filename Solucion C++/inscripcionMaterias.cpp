#include <iostream>
#include <fstream>

using namespace std;

const int NUM_CAMPOS = 8;

void ingresarMaterias ();

int main() {
 
    ingresarMaterias();

    return 0;
}



void ingresarMaterias () {
       int numeroMaterias;
    cout << "Ingrese el numero de materias matriculadas: ";
    cin >> numeroMaterias;

    cout << "La cantidad de materias son: " << numeroMaterias << endl; 

    // Crear un objeto ofstream y abrir el archivo fuera del bucle for
    ofstream archivo("cursos.txt");

    int numeroMate = 1;

    for (int i = 0; i < numeroMaterias ; i++) {

        char valores[NUM_CAMPOS][20];

        // Pedir la información del curso al usuario

        cout << "Ingrese Nombre del curso: ";
        cin >> valores[0]; 

        cout << "Ingrese Codigo del curso: ";
        cin >> valores[1]; 

        cout << "Ingrese Creditos del curso: ";
        cin >> valores[2];

        cout << "Ingrese Horas Teoricas del curso: ";
        cin >> valores[3];

        cout << "Ingrese Horas Practicas del curso: ";
        cin >> valores[4]; 

        cout << "Ingrese Horario 1 del curso: ";
        cin >> valores[5]; 

        cout << "Ingrese Horario 2 del curso: ";
        cin >> valores[6]; 

        cout << "Ingrese Horario 3 del curso: ";
        cin >> valores[7]; 

        // Escribir la información del curso en el archivo
        archivo << numeroMate << ',';
        for(int j = 0; j < NUM_CAMPOS; j++) {
            if (j == NUM_CAMPOS - 1) {        
                archivo << valores[j] << endl;
            }
            else {
                archivo << valores[j] << ',';
            }
        }

        // Incrementar el número de curso
        numeroMate++;
    }
        
    // Cerrar el archivo
    archivo.close();

}