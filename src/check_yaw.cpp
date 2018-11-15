#include <ros/ros.h>
#include <ros/callback_queue.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <kobuki_msgs/MotorPower.h>

class CheckYaw
{
private:
/*サブスクライバ用*/
  ros::NodeHandle sO;
  ros::Subscriber subO;

/*パブリッシャ用*/
  ros::NodeHandle pV;
  ros::Publisher pubV;

  ros::NodeHandle pM;
  ros::Publisher pubM;

  //計算したyaw角を格納する変数
  double yaw;

  //速度命令のメッセージ定義
  geometry_msgs::Twist vw;

  kobuki_msgs::MotorPower motor;

public:
  //サブスクライバに必要なやつ
  ros::CallbackQueue queueO;

  /*コンストラクタとデストラクタ*/
  CheckYaw();
	~CheckYaw(){};

  //コールバック用の関数
  void OdomToYaw(const nav_msgs::Odometry::ConstPtr& sOMsg);
  //速度を送る関数
  void pubVelocity(void);

  bool isMotor(void);

  void motorReset(void);

};

CheckYaw::CheckYaw()
{
/*サブスクライバの設定*/
  sO.setCallbackQueue(&queueO);
  subO = sO.subscribe("/odom",1,&CheckYaw::OdomToYaw,this);

/*速度を送るトピックを設定*/
  pubV = pV.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);

  pubM = pM.advertise<kobuki_msgs::MotorPower>("/mobile_base/commands/motor_power", 1);

/*速度初期化*/
  vw.linear.x = 0;
  vw.linear.y = 0;
  vw.linear.z = 0;
  vw.angular.x = 0;
  vw.angular.y = 0;
  vw.angular.z = 0.5;

  motor.state = 1;

}

void CheckYaw::OdomToYaw(const nav_msgs::Odometry::ConstPtr& sOMsg)
{
  //クオータニオンのyaw角の部分を取り出す
  double yawMsg = sOMsg -> pose.pose.orientation.z;

  //クオータニオン→オイラー角への変換
  yaw = 2*asin(yawMsg);

  std::cout << "yaw << " << yaw << " [rad] << " << yaw*180/M_PI << "[deg]" << '\n';
  std::cout << "90[deg]との差 << " << yaw - M_PI/2 << "[rad] << " << (yaw - M_PI/2)*180/M_PI << "[deg]" << '\n';
}

void CheckYaw::pubVelocity(void)
{
  //オドメトリが90度より小さければ速度を送る
  //低かったら
  if(yaw < M_PI/2)
  {
    pubV.publish(vw);
    std::cout << "publish!!" << '\n' << '\n';
  }
  else
  {
    motor.state = 0;
    pubM.publish(motor);
    std::cout << "************motor off************" << '\n';
  }
}

bool CheckYaw::isMotor(void)
{
  if(motor.state == 1)
  {
    return true;
  }
  else
  {
    return false;
  }

}

void CheckYaw::motorReset(void)
{
  motor.state = 1;
  pubM.publish(motor);
}

int main (int argc, char** argv)
{
  ros::init(argc, argv, "check_yaw");

  CheckYaw cy;

/*モータリセット用のsleep*/
  sleep(1);
  cy.motorReset();

  while(ros::ok())
  {
    //オドメトリをサブスクライブしてコールバック関数を呼び出す
    cy.queueO.callOne(ros::WallDuration(1));//数値はトピックの更新を待つ最大時間[s]
    //速度を送る関数
    cy.pubVelocity();
    if(!cy.isMotor())
    {
      break;
    }
  }

  std::cout << "finish program" << '\n';

  ros::shutdown();//ノードを正常に終了する

  return 0;
}
