import rclpy
from std_msgs.msg import String
import serial
import socket

global wifi_config

def callback_string(msg):
    global wifi_config 
    wifi_config.send(msg.data.encode("utf-8"))

def wifi_setup(ip= '10.190.101.128', port=8080):

    global wifi_config
    wifi_config = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    wifi_config.connect((ip, port))
    print("WiFi setup complete")

def main():

    rclpy.init()

    node = rclpy.create_node('ras_subscriber')
    node.declare_parameter("ip", "10.190.101.128")
    node.declare_parameter('port', 8080)

    ip = node.get_parameter('ip').get_parameter_value().string_value
    port = node.get_parameter('port').get_parameter_value().integer_value

    wifi_setup(ip, port)

    sub = node.create_subscription(String, 'cmd_led', callback_string, 10)

    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()