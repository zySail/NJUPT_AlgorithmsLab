int main() {
    funcA();
    return 0;
}




void funcA() {
    funcB();  
    funcC();  
}


void funcB() {
    funcD();  
}


void funcC() {
    funcD();  
}


void funcD() {
    funcA();  
}
