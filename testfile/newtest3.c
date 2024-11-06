int main() {
    funcA();
    return 0;
}




void funcA() {
    funcB();  
}


void funcB() {
    funcC();  
}


void funcC() {
    funcA();  
}
