#include <opencv2/core/types.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <eigen3/Eigen/Dense>

//这个滤波器是基于图像坐标系进行观测的，效果很好，但是不适合我们的应用，同时也没有Z轴的信息
//使用相关空间
using namespace std;
using namespace Eigen;

cv::Mat img;
cv::Point predicted_position;

class KalmanFilter {
public:
    // 构造函数，初始化卡尔曼滤波器的参数
    KalmanFilter(const MatrixXd& A, const MatrixXd& H, const MatrixXd& Q, const MatrixXd& R)
        : A(A), H(H), Q(Q), R(R) {
        // 初始化状态估计和误差协方差矩阵
        x_hat = VectorXd::Zero(A.rows());// 初始状态估计向量 创建一个维度为 A.rows() 的零向量 
        P = MatrixXd::Identity(A.rows(), A.rows());// 初始误差协方差矩阵
        //创建一个单位矩阵，该矩阵的大小是 A.rows()×A.rows()，即与状态转移矩阵 A 的行数相同。
    }

    // 预测函数，根据上一时刻的状态估计和误差协方差矩阵，预测当前时刻的状态估计和误差协方差矩阵
    void predict() {
        x_hat = A * x_hat;// 预测状态 ^k​=Ax^k−1​
        P = A * P * A.transpose() + Q;// 更新误差协方差矩阵 Pk​=APk−1​AT+Q
    }
    /*
    x^k​ 是状态估计向量。
    A 是状态转移矩阵。
    Pk是误差协方差矩阵。
    Q是过程噪声协方差矩阵。
    */
    //矩阵的转置操作可以使用 transpose() 函数来实现！！！！！！
    // 更新函数，根据当前时刻的状态估计和误差协方差矩阵，计算当前时刻的状态估计和误差协方差矩阵
    void update(const VectorXd& z) {
        VectorXd y = z - H * x_hat;// 计算残差（测量值与预测值的差异） yk​=zk​−Hx^k​
        MatrixXd S = H * P * H.transpose() + R;// 计算残差协方差矩阵 Sk​=HPk​HT+R
        MatrixXd K = P * H.transpose() * S.inverse();// 计算卡尔曼增益  Kk​=Pk​HTSk−1​

        x_hat = x_hat + K * y;// 更新状态估计 x^k​=x^k​+Kk​yk​
        P = (MatrixXd::Identity(A.rows(), A.rows()) - K * H) * P;// 更新误差协方差矩阵
        // Pk​=(I−Kk​H)Pk
    }
    /*
    H 是测量矩阵。
    zk​ 是测量向量。
    R 是测量噪声协方差矩阵。
    yk​ 是测量残差。
    Sk​ 是残差协方差矩阵。
    Kk​ 是卡尔曼增益。
    I 是单位矩阵。
    */

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

//一些中规中矩的图像识别
void getContours(cv::Mat imgDil, KalmanFilter& kf_ball) {
    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    string objectType;
    cv::findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for (int i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);

        vector<vector<cv::Point>> conPoly(contours.size());
        vector<cv::Rect> boundRect(contours.size());

        if (area > 3000) {
            double peri = arcLength(contours[i], 1);
            cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, 1);
            cv::Rect rect = cv::boundingRect(conPoly[i]);

            kf_ball.predict();//先调用一个预测函数，开始卡尔曼的第一步
            VectorXd predicted_state = kf_ball.getState();//获取当前的状态，开始卡尔曼的第二步
            predicted_position = cv::Point(predicted_state(0), predicted_state(1));
            //将获得的空间向量的X,Y转化为平面上的像素坐标方便opencv显示

            cv::rectangle(img, rect, cv::Scalar(0, 255, 255), 2);
            int x = rect.width / 2;
            int y = rect.height / 2;

            cv::Point measure_center = cv::Point(rect.x + x, rect.y + y);

            VectorXd measurement(3);//创建一个维度为3的向量的测量向量
            measurement << rect.x + x, rect.y + y, 0;//将中心坐标作为测量向量的参数、
            //通过 rect.x + x，我们将矩形框左上角的 x 坐标加上宽度的一半，从而得到矩形框的水平中心点 x 坐标。
            //同理，rect.y + y 则是矩形框的垂直中心点 y 坐标。
            kf_ball.update(measurement);//调用更新函数，更新卡尔曼滤波器的状态
            cv::circle(img,measure_center,10,cv::Scalar(255,0,0),3);
            cv::circle(img, predicted_position, 10, cv::Scalar(0, 255, 0), 3);
            
            //调试用的输出，输出测量值和预测值
            cout<<"measure Position: "<<measure_center<<endl;
            cout << "Predicted Position: " << predicted_position << endl;
        }
    }
}


//一些中规中矩的图像识别，制作一个遮罩，然后在遮罩上进行识别
void findcolor(cv::Mat img, KalmanFilter& kf_ball) {
    cv::Mat imgHSV;
    cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

    vector<vector<int>> mycolor{{0, 49, 255, 123, 255, 255}};

    for (int i = 0; i < mycolor.size(); i++) {
        cv::Scalar lower(mycolor[i][0], mycolor[i][1], mycolor[i][2]);
        cv::Scalar upper(mycolor[i][3], mycolor[i][4], mycolor[i][5]);
        cv::Mat mask;
        inRange(imgHSV, lower, upper, mask);
        cv::imshow("mask", mask);
        getContours(mask, kf_ball);
    }
}

void test01() {
    cv::VideoCapture capture;
    capture.open(0);

    // 初始化卡尔曼滤波器
    //初始化系统的运动状态，
    //这里我们假设物体的初始位置是 (100,100,50)
    //初始速度是 (5,2,1)
    //VectorXd state(6);
    // /*
    // x-坐标: 100
    // y-坐标: 100
    // z-坐标: 50
    // x˙-方向速度: 5
    // y˙-方向速度: 2
    // z˙-方向速度: 1
    // */
    //state << 100, 100, 50, 5, 2, 1;  废弃，根本没用这个变量！！！

    //测量矩阵 （一般不做更改 因为这个是一个映射矩阵）
    double location_inf_rate =1;
    MatrixXd H_measure(3, 6);
    H_measure << location_inf_rate, 0, 0, 0, 0, 0,
                  0, location_inf_rate, 0, 0, 0, 0,
                  0, 0, location_inf_rate, 0, 0, 0;
    //如果需要引入速度信息那么需要建立一个6*6的矩阵和下面的一样！！！
    // 状态转移矩阵 描述了如何从系统状态空间到测量空间的映射 这是一个常数是在建模的时候就设计好的，后面不会改变
    //H（measure）​ 是一个 3×6 的矩阵，表示系统状态向量中有6个元素，而测量向量中有3个元素
    /*
    第一行 1,0,0,0,0,0 表示测量结果中 x 方向上只包含 x 位置信息。
    第二行 0,1,0,0,0,0 表示测量结果中 y 方向上只包含 y 位置信息。
    第三行 0,0,1,0,0,0表示测量结果中 z 方向上只包含 z 位置信息。
    */
    
    //状态转移矩阵 描述了系统状态如何随时间变化的 
    //通常需要假设系统是线性的（过程中基本保持不变），并且在整个过程中保持不变
    MatrixXd A(6, 6);
    double delta_t = 1;  // 时间对速度变化的贡献 （对速度的预测是否提前）（也就是时间步长，假设在这段时间内速度没有变化）
    double location_rate = 1;  // 位置变化的速度
    double velocity_rate = 1;  // 速度变化的速度、
    
    A << location_rate, 0, 0, delta_t , 0, 0,
     0, location_rate, 0, 0, delta_t , 0,
     0, 0, location_rate, 0, 0, delta_t ,
     0, 0, 0, velocity_rate, 0, 0,
     0, 0, 0, 0, velocity_rate, 0,
     0, 0, 0, 0, 0, velocity_rate;;
   
    /*
    其中：

    对角线上的元素 1 表示位置坐标（x,y,z）和速度（x˙,y˙,z˙）在一个时间步长内保持不变，因为它们不受速度影响。
    如果将 A 矩阵中的 1 改成 2，那么这意味着在一个时间步长内，系统状态向量中对应位置的变化系数变为 2 倍。
    具体来说，这将导致系统在一个时间步长内的状态变化更加迅速。
    
    对角线上的元素 delta_t​ 表示速度分量（x˙,y˙,z˙）在一个时间步长内的变化
    对角线上的元素 dvelocity_to_position​ 表示位置分量（x,y,z）在一个速度下的变化
    其他为0的地方表示其他参数之间是相互独立的
    */

    // 过程噪声协方差 这个矩阵描述了系统模型中的过程噪声
    //即在状态转移过程中的不确定性
    //也是一个常量不会改变
    
    MatrixXd Q(6, 3);
    double sigma_a = 0.1;  // 加速度的标准差 （准确度加强）
    Q << sigma_a * sigma_a * delta_t * delta_t, 0, 0, 0, 0, 0,
        0, sigma_a * sigma_a * delta_t * delta_t, 0, 0, 0, 0,
        0, 0, sigma_a * sigma_a * delta_t * delta_t, 0, 0, 0;

    
    // 测量噪声协方差（灵敏性加强）   
    MatrixXd R(3, 3);
    double sigma_m = 0.01;  // 测量噪声的标准差
    R << sigma_m, 0, 0,
         0, sigma_m, 0,
         0, 0, sigma_m;
    
    /*
    在卡尔曼滤波器中，我们通常假设测量噪声是独立同分布（iid）的，因此协方差矩阵是对角矩阵，
    对角线上的元素表示测量噪声在各个维度上的方差。

    具体来说，这个矩阵是一个 3×3 的矩阵，对角线上的元素是 σm​，其余元素为零。这里的 σm​ 是测量噪声的标准差，
    它描述了测量值在各个维度上的离散程度。

    简单地说，测量噪声的协方差矩阵描述了我们对于测量值的不确定性，
    它在卡尔曼滤波中用于权衡预测和测量两者的信息。
    */

    // 卡尔曼滤波器   
    KalmanFilter kf_ball(A, H_measure, Q, R);//创建的滤波器对象在这里！！！

    while (1) {
        capture.read(img);
        findcolor(img, kf_ball);//核心封装函数怪，先识别颜色，然后再进行卡尔曼滤波
        cv::imshow("image", img);
        cv::waitKey(1);
    }
}

int main() {
    test01();
}

//一些补充知识
/*

卡尔曼滤波器是一种递归的状态估计算法，最初由Rudolf E. Kálmán于1960年提出。它是一种线性、高斯的滤波器，用于估计一个动态系统的状态，通过融合系统的动态模型和来自传感器的测量数据，从而提供对系统状态的最优估计。

卡尔曼滤波器的设计基于以下假设和模型：

    线性系统模型： 系统的动态行为可以用线性方程描述。这意味着系统状态的变化是线性的，可以通过矩阵相乘来表示。

    高斯噪声： 系统的状态变化和测量过程中的噪声都是高斯分布的。这使得卡尔曼滤波器在处理噪声时非常高效。

    马尔可夫性质： 系统的未来状态仅依赖于当前状态和控制输入，而不依赖于先前的状态。这意味着系统是马尔可夫的。

卡尔曼滤波器通过两个主要步骤来更新状态估计：

    预测（Prediction）： 利用系统的动态模型，预测当前时刻的状态。这一步产生的是对当前状态的预测值和相应的不确定性。

    更新（Update）： 利用传感器提供的测量值，将预测的状态值与测量值进行比较，并结合两者，产生一个更准确的状态估计。这一步的结果是对系统状态的最优估计和相应的不确定性。

*/

//关于测量矩阵H的一些理解
/*
系统状态向量中有6个元素，是因为这个卡尔曼滤波器设计用于跟踪三维空间中的物体
其中包括物体的三个空间坐标（x,y,z）和三个速度分量（x˙,y˙,z˙）
因此，系统状态向量是一个6维向量，表示了物体在空间中的位置和速度。


将测量矩阵中的1改为2，会改变测量矩阵的结构，
具体而言，会增加测量矩阵中每个状态的权重。
在卡尔曼滤波中，测量矩阵 H 表示状态向量和测量之间的映射关系。
每个元素表示对应状态对测量的影响权重。

在这个特定的测量矩阵 H_measure 中，
1表示每个状态对应的测量权重为1。
如果将其中的1改为2，意味着增加了每个状态的影响权重，使得测量在状态估计中更具影响力。
这可能会导致对测量更强烈地依赖，而不太考虑之前状态的影响。


具体来说，系统状态向量可以表示为：

x=[x,y,z,x˙,y˙,z˙]T

其中：

    x,y,z是物体在空间中的位置坐标。
    x˙,y˙,z˙ 是物体在空间中的速度分量。
*/

//关于状态转移矩阵A的一些理解
/*
这个矩阵 A 是状态转移矩阵，描述了系统状态如何随时间演变。
在这个具体的应用中，
A 用于描述目标在三维空间中的位置和速度是如何在时间步长 δt​ 内演变的。

具体而言，这个矩阵可以解释为：

其中：

    对角线上的元素 1 表示位置坐标（x,y,z）在一个时间步长内保持不变，因为它们不受速度影响。
    对角线上的元素 δt​ 表示速度分量（x˙,y˙,z˙）在一个时间步长内的变化，即速度乘以时间步长得到位置的变化。
    非对角线上的元素都是零，表示位置和速度之间是相互独立的。

因此，这个矩阵描述了一个简化的匀速运动模型，其中物体在 x,y,z 三个方向上以恒定的速度运动，而在速度方面则保持不变。
*/

//关于过程噪声协方差矩阵Q的一些理解
/*
    在卡尔曼滤波中，Q 代表系统模型中的过程噪声，即在状态转移过程中的不确定性。具体来说，Q 矩阵描述了在一个时间步长内加速度的不确定性。

    这里的 sigma_a 是加速度的标准差，表示加速度在一个时间步长内的变化幅度。delta_t 是时间步长，表示两个连续状态之间的时间间隔。

    矩阵 Q 的对角线元素描述了加速度的方差，非对角线元素为零表示各个状态之间是独立的。因为加速度是速度的变化率，所以这个过程噪声矩阵描述了在一个时间步长内速度变化的不确定性。

    在卡尔曼滤波的预测步骤中，该过程噪声协方差矩阵与状态转移矩阵 A 相乘，用于模拟状态转移过程中的不确定性。
    
    对角线元素（1, 1）、（2, 2）、（3, 3）表示位置（x、y、z）的方差。
    这里 sigma_a * sigma_a * delta_t * delta_t 是通过加速度计算位置变化的方差。
    因为这是对角线元素，它们描述了每个位置分量的不确定性。

    
    对角线元素（4, 4）、（5, 5）、（6, 6）表示速度（vx、vy、vz）的方差。同样，通过加速度计算速度变化，因此使用了相同的方差计算。

    非对角线元素为零，表示各个状态之间是独立的，即位置和速度之间的变化不相关。
*/

//卡尔曼滤波的流程
/*
卡尔曼滤波是一种用于估计动态系统状态的递归算法。以下是卡尔曼滤波的基本流程：

    初始化状态（Initialization）：
        初始化状态估计向量 x^ 和误差协方差矩阵 P。
        定义状态转移矩阵 A、测量矩阵 H、过程噪声协方差矩阵 Q 和测量噪声协方差矩阵 R。

    预测（Prediction）：
        使用状态转移矩阵 A 预测系统的下一个状态： x^priori=Ax^
        预测误差协方差： Ppriori=APAT+Q
        这一步表示对系统状态的预测，不考虑测量。

    更新（Update）：
        获取测量值 z。
        计算残差（测量与预测之差）： y=z−Hx^priori
        计算残差的协方差： S=HPprioriHT+R
        计算卡尔曼增益： K=PprioriHTS^−1
        更新状态估计： x^=x^priori+Ky
        更新误差协方差： P=(I−KH)Ppriori

这个过程会递归进行：每次获取新的测量值后，就进行预测和更新步骤，以不断优化对系统状态的估计。
*/
