void funcA() {
    funcB();  
    funcC();  
}

void funcB();

int main() {
    funcA();
    printf("hello\n");
    funcE();
    return 0;
}

void funcB() 
{
    funcA();  
}

void funcC() {
    funcD();  
}

void funcD() {
    funcD();  
}

void funcE(){
    funcE();
}
