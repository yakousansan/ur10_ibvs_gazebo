”但是，根据你的描述，你可能需要持续地发布雅可比矩阵（例如，在视觉伺服循环中），那么使用话题可能更合适“
这样那按照你推荐的使用话题。然后关于消息类型，你看看我定义的这个行不行：
GetJacobian.srv
# Request: 关节角度
# 关节角度是一个包含所有关节角度的数组
float64[6] joint_angles

---
# Response: 雅可比矩阵
# 雅可比矩阵是一个6xN的矩阵，这里使用二维数组表示
std_msgs/Float64MultiArray jacobian_matrix
bool success
如果不可以的话就使用你说的std_msgs::msg::Float64MultiArray