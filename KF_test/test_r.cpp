#include <opencv2/opencv.hpp>
#include <eigen3/Eigen/Dense>


using namespace Eigen;

class KalmanFilter {
public:
    KalmanFilter(const MatrixXd& A, const MatrixXd& H, const MatrixXd& Q, const MatrixXd& R)
        : A(A), H(H), Q(Q), R(R) {
        // 初始化状态估计和误差协方差矩阵
        x_hat = VectorXd::Zero(A.rows());
        P = MatrixXd::Identity(A.rows(), A.rows());
    }

    // 预测函数
    void predict() {
        x_hat = A * x_hat;
        P = A * P * A.transpose() + Q;
    }

    // 更新函数
    void update(const VectorXd& z) {
        VectorXd y = z - H * x_hat;
        MatrixXd S = H * P * H.transpose() + R;
        MatrixXd K = P * H.transpose() * S.inverse();

        x_hat = x_hat + K * y;
        P = (MatrixXd::Identity(A.rows(), A.rows()) - K * H) * P;
    }

    // 获取当前状态估计
    VectorXd getState() const {
        return x_hat;
    }

private:
    MatrixXd A;  // 状态转移矩阵
    MatrixXd H;  // 测量矩阵
    MatrixXd Q;  // 过程噪声协方差
    MatrixXd R;  // 测量噪声协方差

    VectorXd x_hat;  // 状态估计
    MatrixXd P;      // 误差协方差
};

int main() {
    // 创建背景图像
    cv::Mat background(600, 800, CV_8UC3, cv::Scalar(0, 0, 0));

    // 创建窗口
    cv::namedWindow("Kalman Filter Ball Prediction 3D", cv::WINDOW_AUTOSIZE);

    // 小球的初始位置和速度（三维）
    VectorXd state(6);
    state << 100, 100, 50, 5, 2, 1; // x, y, z, vx, vy, vz

    // 小球的测量矩阵
    MatrixXd H_measure(3, 6);
    H_measure << 1, 0, 0, 0, 0, 0,
                  0, 1, 0, 0, 0, 0,
                  0, 0, 1, 0, 0, 0;

    // 状态转移矩阵，这里简化为匀速运动
    MatrixXd A(6, 6);
    A << 1, 0, 0, 1, 0, 0,
         0, 1, 0, 0, 1, 0,
         0, 0, 1, 0, 0, 1,
         0, 0, 0, 1, 0, 0,
         0, 0, 0, 0, 1, 0,
         0, 0, 0, 0, 0, 1;

    // 过程噪声协方差
    MatrixXd Q(6, 6);
    Q << 0.1, 0, 0, 0, 0, 0,
         0, 0.1, 0, 0, 0, 0,
         0, 0, 0.1, 0, 0, 0,
         0, 0, 0, 0.1, 0, 0,
         0, 0, 0, 0, 0.1, 0,
         0, 0, 0, 0, 0, 0.1;

    // 测量噪声协方差
    MatrixXd R(3, 3);
    R << 0.1, 0, 0,
         0, 0.1, 0,
         0, 0, 0.1;

    // 卡尔曼滤波器
    KalmanFilter kf_ball(A, H_measure, Q, R);

    // 主循环
    while (true) {
        // 小球运动模拟
        state(0) += state(3); // 更新 x 位置
        state(1) += state(4); // 更新 y 位置
        state(2) += state(5); // 更新 z 位置

        // 预测步骤
        kf_ball.predict();

        // 获取预测位置
        VectorXd predicted_state = kf_ball.getState();

        // 更新步骤，测量为预测位置加上一些噪声
        VectorXd measurement = H_measure * state + VectorXd::Random(3) * 5.0;
        kf_ball.update(measurement);

        // 清空背景图像
        background.setTo(cv::Scalar(0, 0, 0));

        // 画预测位置的小球
        cv::Point3d predicted_position(predicted_state(0), predicted_state(1), predicted_state(2));
        cv::circle(background, cv::Point2d(predicted_position.x, predicted_position.y), 10, cv::Scalar(225, 255, 0), -1);

        // 画真实位置的小球
        cv::Point3d real_position(state(0), state(1), state(2));
        cv::circle(background, cv::Point2d(real_position.x, real_position.y), 10, cv::Scalar(0, 0, 255), -1);

        // 显示图像
        imshow("Kalman Filter Ball Prediction 3D", background);

        // 检测按键事件，如果按下ESC键，退出循环
        if (cv::waitKey(30) == 27) {
            break;
        }
    }

    return 0;
}
