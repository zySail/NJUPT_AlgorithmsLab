// mytest.c test more complex condition

int funcA(); // function declare

int main() {
    funcA();
    printf("hello world"); // not defined function
    return 0;
}


void funcA() // "{" in next line
{
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
