int main() {
    funcA();
    return 0;
}
// 函数定义
void funcA() {
    std::cout << "In funcA" << std::endl;
    funcB();  // 调用 funcB
    funcC();  // 调用 funcC 
}
void funcB() {
    std::cout << "In funcB" << std::endl;
    funcA();  // 调用 funcA （递归调用）
}
void funcC() {
    std::cout << "In funcC" << std::endl;
    funcD();  // 调用 funcD
}
void funcD() {
    std::cout << "In funcD" << std::endl;
    funcD();  // 自我调用（递归）
}
