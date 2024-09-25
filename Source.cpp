#include <iostream>
#include <string>
#include <vector>
#include <limits>

int main() {
    // Structures to hold data
    struct User {
        std::string username;
        std::string password;
    };

    struct Document {
        std::string tipo_documento;
        std::string numero_documento;
        std::string fecha_emision;
        std::string fecha_vencimiento;
        double valor_nominal;
        double tasa;
    };

    struct Cartera {
        std::string nombre_cartera;
        std::string moneda;
        std::string tipo_tasa;
        std::string fecha_descuento;
        std::vector<Document> documentos;
        double tcea;
    };

    // Hardcoded user for authentication
    User user = { "admin", "1234" };
    std::string input_username, input_password;

    // User authentication
    bool authenticated = false;
    while (!authenticated) {
        std::cout << "=== Inicio de Sesión ===\n";
        std::cout << "Usuario: ";
        std::getline(std::cin, input_username);
        std::cout << "Contraseña: ";
        std::getline(std::cin, input_password);

        if (input_username == user.username && input_password == user.password) {
            authenticated = true;
            std::cout << "\nBienvenido, " << user.username << "!\n\n";
        }
        else {
            std::cout << "\nUsuario o contraseña incorrectos. Intente nuevamente.\n\n";
        }
    }

    // Main menu variables
    std::vector<Cartera> carteras;
    int main_option = 0;

    // Main menu loop
    do {
        std::cout << "=== Menú Principal ===\n";
        std::cout << "1. Crear nueva cartera\n";
        std::cout << "2. Gestionar carteras existentes\n";
        std::cout << "3. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> main_option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        if (main_option == 1) {
            // Create new portfolio
            Cartera nueva_cartera;
            std::cout << "\n=== Crear Nueva Cartera ===\n";
            std::cout << "Nombre de la cartera: ";
            std::getline(std::cin, nueva_cartera.nombre_cartera);
            std::cout << "Moneda (PEN/USD): ";
            std::getline(std::cin, nueva_cartera.moneda);
            std::cout << "Tipo de tasa (Nominal/Efectiva): ";
            std::getline(std::cin, nueva_cartera.tipo_tasa);
            std::cout << "Fecha de descuento (DD/MM/AAAA): ";
            std::getline(std::cin, nueva_cartera.fecha_descuento);
            nueva_cartera.tcea = 0.0; // Initial TCEA
            carteras.push_back(nueva_cartera);
            std::cout << "\nCartera creada exitosamente.\n\n";
        }
        else if (main_option == 2) {
            // Manage existing portfolios
            if (carteras.empty()) {
                std::cout << "\nNo hay carteras disponibles.\n\n";
            }
            else {
                int cartera_option = 0;
                std::cout << "\n=== Gestionar Carteras ===\n";
                for (size_t i = 0; i < carteras.size(); ++i) {
                    std::cout << i + 1 << ". " << carteras[i].nombre_cartera << "\n";
                }
                std::cout << "Seleccione una cartera (0 para volver): ";
                std::cin >> cartera_option;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (cartera_option > 0 && cartera_option <= carteras.size()) {
                    Cartera& selected_cartera = carteras[cartera_option - 1];
                    int manage_option = 0;
                    do {
                        std::cout << "\n=== Opciones de Cartera ===\n";
                        std::cout << "1. Ver detalles de la cartera\n";
                        std::cout << "2. Agregar documentos\n";
                        std::cout << "3. Calcular TCEA\n";
                        std::cout << "4. Generar reporte\n";
                        std::cout << "5. Volver\n";
                        std::cout << "Seleccione una opción: ";
                        std::cin >> manage_option;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if (manage_option == 1) {
                            // View portfolio details
                            std::cout << "\n=== Detalles de la Cartera ===\n";
                            std::cout << "Nombre: " << selected_cartera.nombre_cartera << "\n";
                            std::cout << "Moneda: " << selected_cartera.moneda << "\n";
                            std::cout << "Tipo de tasa: " << selected_cartera.tipo_tasa << "\n";
                            std::cout << "Fecha de descuento: " << selected_cartera.fecha_descuento << "\n";
                            std::cout << "Documentos en cartera: " << selected_cartera.documentos.size() << "\n\n";
                        }
                        else if (manage_option == 2) {
                            // Add documents to portfolio
                            int num_docs = 0;
                            std::cout << "\n¿Cuántos documentos desea agregar? ";
                            std::cin >> num_docs;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                            for (int i = 0; i < num_docs; ++i) {
                                Document nuevo_doc;
                                std::cout << "\n=== Agregar Documento " << i + 1 << " ===\n";
                                std::cout << "Tipo de documento (Letra/Factura): ";
                                std::getline(std::cin, nuevo_doc.tipo_documento);
                                std::cout << "Número de documento: ";
                                std::getline(std::cin, nuevo_doc.numero_documento);
                                std::cout << "Fecha de emisión (DD/MM/AAAA): ";
                                std::getline(std::cin, nuevo_doc.fecha_emision);
                                std::cout << "Fecha de vencimiento (DD/MM/AAAA): ";
                                std::getline(std::cin, nuevo_doc.fecha_vencimiento);
                                std::cout << "Valor nominal: ";
                                std::cin >> nuevo_doc.valor_nominal;
                                std::cout << "Tasa (" << selected_cartera.tipo_tasa << "): ";
                                std::cin >> nuevo_doc.tasa;
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                selected_cartera.documentos.push_back(nuevo_doc);
                                std::cout << "Documento agregado exitosamente.\n";
                            }
                        }
                        else if (manage_option == 3) {
                            // Calculate TCEA (simplified calculation)
                            if (selected_cartera.documentos.empty()) {
                                std::cout << "\nNo hay documentos en la cartera para calcular TCEA.\n";
                            }
                            else {
                                double total_valor_nominal = 0.0;
                                double total_descuento = 0.0;
                                for (const auto& doc : selected_cartera.documentos) {
                                    total_valor_nominal += doc.valor_nominal;
                                    // Simplified discount calculation
                                    double descuento = doc.valor_nominal / (1 + doc.tasa);
                                    total_descuento += descuento;
                                }
                                // Simplified TCEA calculation
                                selected_cartera.tcea = ((total_valor_nominal / total_descuento) - 1) * 100;
                                std::cout << "\nTCEA calculada exitosamente: " << selected_cartera.tcea << "%\n";
                            }
                        }
                        else if (manage_option == 4) {
                            // Generate report
                            std::cout << "\n=== Reporte de Cartera ===\n";
                            std::cout << "Nombre: " << selected_cartera.nombre_cartera << "\n";
                            std::cout << "Moneda: " << selected_cartera.moneda << "\n";
                            std::cout << "Tipo de tasa: " << selected_cartera.tipo_tasa << "\n";
                            std::cout << "Fecha de descuento: " << selected_cartera.fecha_descuento << "\n";
                            std::cout << "TCEA: " << selected_cartera.tcea << "%\n";
                            std::cout << "\n=== Documentos ===\n";
                            for (size_t i = 0; i < selected_cartera.documentos.size(); ++i) {
                                const auto& doc = selected_cartera.documentos[i];
                                std::cout << "Documento " << i + 1 << ":\n";
                                std::cout << "  Tipo: " << doc.tipo_documento << "\n";
                                std::cout << "  Número: " << doc.numero_documento << "\n";
                                std::cout << "  Fecha de emisión: " << doc.fecha_emision << "\n";
                                std::cout << "  Fecha de vencimiento: " << doc.fecha_vencimiento << "\n";
                                std::cout << "  Valor nominal: " << doc.valor_nominal << "\n";
                                std::cout << "  Tasa: " << doc.tasa << "\n";
                            }
                            std::cout << "\nFin del reporte.\n";
                        }
                    } while (manage_option != 5);
                }
            }
        }
    } while (main_option != 3);

    std::cout << "\nGracias por usar el sistema. ¡Hasta luego!\n";
    return 0;
}
