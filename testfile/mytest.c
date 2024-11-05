// mytest.c test more complex condition

int main() {
    funcA();
    return 0;
}

void funcA() {
    funcB();  
    funcC();  
}

void funcB() {
    funcA();  
}

void funcC() {
    funcD();  
}

void funcD() {
    funcD();  
}
