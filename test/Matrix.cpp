#include <iostream>
#include <eigen3/Eigen/Dense>

int main() {
    Eigen::MatrixXd mat(2, 2);
    mat << 1, 2, 3, 4;

    Eigen::VectorXd vec(2);
    vec << 5, 6;

    Eigen::VectorXd result = mat * vec;

    std::cout << "Matrix:\n" << mat << "\n\n";
    std::cout << "Vector:\n" << vec << "\n\n";
    std::cout << "Result:\n" << result << std::endl;

    return 0;
}
