int main() {
    funcA();
    return 0;
}

void funcA() {
    std::cout << "In funcA" << std::endl;
    funcB();  
    funcC();  
}
void funcB() {
    std::cout << "In funcB" << std::endl;
    funcA();  
}
void funcC() {
    std::cout << "In funcC" << std::endl;
    funcD();  
}
void funcD() {
    std::cout << "In funcD" << std::endl;
    funcD();  
}
