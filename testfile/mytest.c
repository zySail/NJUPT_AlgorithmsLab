// mytest.c test more complex condition

void funcA() {
    funcB();  
    funcC();  
}

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
