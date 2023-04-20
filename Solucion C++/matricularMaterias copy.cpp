#include <iostream>
#include <fstream>

using namespace std;

const int NUM_CAMPOS = 8;

void ingresarMaterias ();

bool sonIguales(char* str1, char* str2);

int contarMaterias();

void horasIndividualesArreglo (int horasMatIndividuales[]);

void matricularHorario(char (&horario)[7][24], char* numeroLista, char* horaClase);

void matricularMaterias(char (&horario)[7][24], const string& nombreArchivo);

void asignarEstudio(char (&horario)[7][24]);

void asignarAlmuerzo(char (&horario)[7][24], int horaAlmuerzo);

void asignarCena(char (&horario)[7][24], int horaCena);

void asignarDescanso (char (&horario)[7][24], int InicioDescanso, int FinDescanso);

char *cargarNombresMaterias(int numLinea);

int main() {

    // Crear un arreglo de 7 filas y 24 columnas
    char horario[7][24];

    // Asignar valores al arreglo
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 24; j++) {
            horario[i][j] = '-';
        }
    }

    matricularMaterias(horario, "materias.txt"); // se inscriben los horarios en el arreglo horario las materias matriculadas 

    asignarDescanso(horario, 22,5);

    asignarAlmuerzo(horario, 12);

    asignarCena(horario, 19);

    asignarEstudio(horario);
    
    
    char horarioFormateado[24][7];
    // Transponer la matriz
    for (int fila = 0; fila < 7; fila++) {
        for (int columna = 0; columna < 24; columna++) {
            horarioFormateado[columna][fila] = horario[fila][columna];
        }
    }

    // imprimir Horario
    
    cout << endl;
    cout << " // --------------------------------------------------------------------------------------------------------- //" << endl;
    cout << "LUN\t\tMAR\t\tMIE\t\tJUE\t\tVIE\t\tSAB\t\tDOM" << endl;
    
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 7; j++) {
            int materiaImprimir = static_cast<int>(horarioFormateado[i][j]) - 48;
            if (materiaImprimir == -3) {
                cout << "*DISPO" << "\t\t";
            }
            else if (materiaImprimir == 42) {
                cout << "DESCAN" << "\t\t";
            }

            else if (materiaImprimir < 9) {
                cout << "OOO" << "\t\t";
            }

            else {
                cout << materiaImprimir  << "\t\t";
            }
        }
        cout << endl;
    }

    cout << " // --------------------------------------------------------------------------------------------------------- //" << endl;

    int numLinea = 4; // Número de línea de la materia que deseas obtener
    char* nombreMateria = cargarNombresMaterias(numLinea);
    cout << "Nombre de la materia en la linea " << numLinea << ": " << nombreMateria << endl;
    delete[] nombreMateria; // Liberar la memoria asignada
 
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

void asignarEstudio(char (&horario)[7][24]) {
    
    int numeroMaterias = contarMaterias();
    int HorasIndividuales[numeroMaterias];

    horasIndividualesArreglo(HorasIndividuales);

    for(int dia = 0; dia < 7; dia++) {
        for(int hora = 0; hora < 24; hora++) {
            for(int i = 0; i < numeroMaterias; i++) {
                    int horasMateria = HorasIndividuales[i];
                    if(horasMateria > 0 && horario[dia][hora] == '-') { // Espacio libre en el horario
                        horario[dia][hora] = 'a' + i ; // Asignar la materia
                        HorasIndividuales[i]--; // Reducir las horas necesarias para la materia
                        break;
                    }
            }
        }
    }

}

void asignarDescanso (char (&horario)[7][24], int InicioDescanso, int FinDescanso) {
    int horaInicioSueno[7] = {InicioDescanso, InicioDescanso, InicioDescanso, InicioDescanso, InicioDescanso, InicioDescanso, InicioDescanso}; // Hora de inicio de sueño para cada día
    int horaFinSueno[7] = {FinDescanso, FinDescanso, FinDescanso, FinDescanso, FinDescanso, FinDescanso, FinDescanso}; // Hora de fin de sueño para cada día

    for(int dia = 0; dia < 7; dia++) {
        for(int hora = 0; hora < 24; hora++) {
            if(hora >= horaInicioSueno[dia] || hora < horaFinSueno[dia]) { // Hora de sueño
                horario[dia][hora] = 'Z'; // Asignar hora de sueño
            }
        }
    }
}

void asignarAlmuerzo(char (&horario)[7][24], int horaAlmuerzo) {
    for(int dia = 0; dia < 7; dia++) {
        horario[dia][horaAlmuerzo] = 'Y'; // Asignar hora de almuerzo
    }
}

void asignarCena(char (&horario)[7][24], int horaCena) {
    for(int dia = 0; dia < 7; dia++) {
        horario[dia][horaCena] = 'V'; // Asignar hora de almuerzo
    }
}

char *cargarNombresMaterias (int numLinea) {
    ifstream archivo("materias.txt");

    char *nombreMateria = new char[100];
    int linea = 0;

    char* numeroLista    = new char[100];
    char* nombre    = new char[100];
    char* codigo    = new char[100];
    char* creditos      = new char[100];
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
        linea++;

        if (linea == numLinea) {
            int n = 0;
            while (nombre[n] != '\0') {
            n++;
        }

        for (int j = 0; j < n; j++) {
            nombreMateria[j] = nombre[j];
        }
        nombreMateria[n] = '\0';

        break;
        }
    }

    archivo.close();
    delete[] numeroLista;
    delete[] nombre;
    delete[] codigo;
    delete[] creditos;
    delete[] horasTeoricas;
    delete[] horasPracticas;
    delete[] horaClase1;
    delete[] horaClase2;
    delete[] horaClase3;

    return nombreMateria;
}