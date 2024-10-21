#include <iostream>
using namespace std;

// Estructura de usuario
struct User {
    // atributos
    int id;
    string username;
    string password;
    
    User* next; 
    User* prev;
};

// puntero a la estructura de usuarios
typedef struct User *nodo;

// Función para crear nuevos usuarios e insertarlos en la lista
void newUser(string username, string password, nodo &list) {
    // valida la existencia de usuarios en la lista
    if(list == NULL) {
        nodo newUser = new(struct User);

        newUser->id = 1; 
        newUser->username = username;
        newUser->password = password;

        newUser->next = nullptr;
        newUser->prev = nullptr;
        list = newUser;
    }
    else {
        nodo lastnode = list;
        while (lastnode->next != nullptr) {
            lastnode = lastnode->next;
        }
        nodo newUser = new(struct User);

        newUser->id = lastnode->id + 1;
        newUser->username = username;
        newUser->password = password;

        newUser->next = nullptr;
        newUser->prev = lastnode;
        lastnode->next = newUser;
    }
};

// Muestra los usuarios creados
void listUsers(nodo list) {
    if(list != NULL) {
        cout << list->username << " - ";
        listUsers(list->next);
    }
};

// Función para registrar un nuevo usuario
void signup(nodo &list){
    cout << "\n\t-- SIGNUP --" << endl;
    string username, password;
    cout << "Username: " << endl;
    cin >> username;
    cout << "Password: " << endl;
    cin >> password;

    newUser(username, password, list);
};

// Función para borrar un usuario de la lista
void deleteUser(int loggedIdUser, nodo &list) {
    nodo i = list;
    nodo prev = NULL;

    // valida que hayan usuarios en la lista
    while(i!=NULL) {

        // valida que el id iterado sea el mismo a borrar
        if(i->id == loggedIdUser) {
            
            // valida si el usuario es el primero de la lista
            if(prev == NULL) {
                list = list->next;
            } else {
                prev->next = i->next;
            }

        } else {
            // almacena el nodo previo al iterador
            prev = i;
        }
        // recorre la lista
        i = i->next;
    }
};

// Función que muestra un menú al mantenimiento de usuario (User Maintenance Menu)
void UMM(int loggedIdUser, nodo &list) {
    int opcion;
    bool salir = false;

    while (!salir) {
        cout << "\n\t-- USER MAINTENANCE MENU --" << endl;
        cout << "1) Update User" << endl;
        cout << "2) Delete this User" << endl;
        cout << "3) Go Back" << endl;
        cout << "4) Exit" << endl;
        cout << "Option: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                // Actualizar Usuario
                break;
            case 2:
                // Borrar este Usuario
                deleteUser(loggedIdUser, list);
                cout << "LISTA DE USUARIOS: " << endl;
                listUsers(list);
                //listUsers(list);
                break;
            case 3:
                // Regresar
                salir = true;
                break;
            case 4:
                // Cerrar programa
                //exit(1);
                break;
            default:
                // Valida una opción erronea
                cout << "No valid option, try again." << endl;
                break;
        }
        cout << endl; 
    }
};

// Función que muestra un menú al usuario logueado
void loginMenu(int loggedIdUser, nodo &list) {
    int opcion;
    bool salir = false;

    // Menú al iniciar sesión
    while (!salir) {
        cout << "1) User Maintenance" << endl;
        cout << "2) Search User" << endl;
        cout << "3) Friends List" << endl;
        cout << "4) Publication Maintenance" << endl;
        cout << "5) Chat" << endl;
        cout << "6) Logout" << endl;
        cout << "7) Exit" << endl;
        cout << "Option: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                // Mantenimiento de usuario (Actualizar y Borrar)
                UMM(loggedIdUser, list);
                break;
            case 2:
                // Buscar Usuarios
                break;
            case 3:
                // Menú de amistades (solicitudes de amistad y listado de amigos)
                break;
            case 4:
                // Menú de publicaciones (Publicar, Leer publicaciones, Actualizar y Borrar publicaciones propias)
                break;
            case 5:
                // Menú de chat
                break;
            case 6:
                // Cerrar Sesión
                salir = true;
                break;
            case 7:
                // Terminar programa
                exit(1);
                //break;
            default:
                // Validar opción incorrecta
                cout << "No valid option, try again." << endl;
                break;
        }
        cout << endl; 
    }
};

// Función de inicio de sesión de un usuario
void login(nodo &list){
    cout << "\n\t-- LOGIN --" << endl;
    string username, password;
    cout << "Username: " << endl;
    cin >> username;
    cout << "Password: " << endl;
    cin >> password;

    if (list != NULL) {
        nodo i = list;
        bool check = false;

        while (i != NULL) {
            if (i->username == username && i->password == password) {
                cout << "\n\t-- WELCOME " << username << " --" << endl;
                loginMenu(i->id, list);
                check = true;
                break;
            }
            i = i->next;
        }

        if (!check) {
            cout << "Error: Invalid Credentials" << endl;
        }
    } else {
        cout << "Error: No users created yet." << endl;
    }
};

int main() {
    int opcion;
    bool salir = false;
    nodo list = NULL;

    // Menú principal
    while (!salir) {
        cout << "\t-- MAIN MENU --" << endl;
        cout << "1) Login" << endl;
        cout << "2) Signup" << endl;
        cout << "3) Exit" << endl;
        cout << "Option: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                // Inicio de sesión
                login(list);
                break;
            case 2:
                // Registro de usuarios
                signup(list);
                break;
            case 3:
                // Terminar programa
                salir = true;
                break;
            default:
                // Valida una opción erronea
                cout << "No valid option, try again." << endl;
                break;
        }
        cout << endl; 
    }

    return 0;
}