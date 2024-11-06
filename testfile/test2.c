int main() {
    funcA();
    return 0;
}

// 函数定义

// funcA 调用 funcB
void funcA() {
    funcB();  // 调用 funcB
}

// funcB 调用 funcC
void funcB() {
    funcC();  // 调用 funcC
}

// funcC 调用 funcD
void funcC() {
    funcD();  // 调用 funcD
}

// funcD 调用 funcA（递归调用）
void funcD() {
    funcA();  // 递归调用 funcA
}
